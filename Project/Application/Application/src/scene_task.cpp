/**
	@file scene_task.h
	@brief シーンの処理、表示
*/

#include "stdafx.h"
#include "scene_task.h"
#include "application.h"
#include "object.h"
#include "water_surface.h"

const CSceneTask::ProcFunc	CSceneTask::m_pRunFunc[] =
{
	&CSceneTask::_runInit,
	&CSceneTask::_runMain,
};

const CSceneTask::ProcFunc	CSceneTask::m_pDrawFunc[] =
{
	&CSceneTask::_dummy,
	&CSceneTask::_drawMain,
};

//---------------------------------------------------------------------
CSceneTask::CSceneTask()
	:	CTask				( "CSceneTask" )
	,	m_pReflectMap		( nullptr )
	,	m_pReflectSurf		( nullptr )
	,	m_pFurObject		( nullptr )
	,	m_pBG				( nullptr )
	,	m_pWater			( new CWaterSurFace )
{
	STATIC_ASSERT(NUM_OF(m_pRunFunc)==STATE_MAX);
	STATIC_ASSERT(NUM_OF(m_pDrawFunc)==STATE_MAX);

	setSubTask(STATE_INIT);
}

//---------------------------------------------------------------------
CSceneTask::~CSceneTask()
{
	deviceLost();

	for_each( m_pObject, SDeleteObject() );
	m_pObject.clear();
	SAFE_DELETE( m_pFurObject );
	SAFE_DELETE( m_pBG );
	SAFE_DELETE( m_pWater );
}

//---------------------------------------------------------------------
void CSceneTask::_runInit()
{
	CObject* pObj = nullptr;

	pObj = new CObject(L"model/teapot.x", CShaderTask::S_I_BUMP );
	m_pObject.push_back( pObj );
	
	pObj = new CObject(L"model/teapot.x", CShaderTask::S_I_DEFAULT_MATE );
	pObj->getTrn()->x = 10.f;
	pObj->getTrn()->z = 10.f;;
	m_pObject.push_back( pObj );

	m_pBG = new CObject(L"model/droidroom.x", CShaderTask::S_I_DEFAULT_MATE );
	m_pBG->getScl()->x = 0.01f;
	m_pBG->getScl()->y = 0.01f;
	m_pBG->getScl()->z = 0.01f;

	m_pFurObject = new CObject(L"model/teapot.x", CShaderTask::S_I_FUR );
	m_pFurObject->getTrn()->x = 10.f;
	m_pFurObject->getTrn()->z = 10.f;;

	m_pWater->init();

	deviceReset();

	setSubTask(STATE_MAIN);
}

//---------------------------------------------------------------------
void CSceneTask::_runMain()
{
	float fElapsd = AppContext::GetInstance()->getElapsdTime();
	util::for_each( m_pObject, std::bind2nd(std::mem_fun(&CObject::update), fElapsd ));
	m_pFurObject->update(fElapsd);
	m_pBG->update( fElapsd );
	m_pWater->update(fElapsd );

	const unsigned int nMax = m_pObject.size();
	for ( unsigned int i=0; i<nMax; ++i )
	{
		D3DXVECTOR3* vVec = m_pObject[i]->getRot();
		vVec->x += 1.f*fElapsd;
	}

	{
		D3DXVECTOR3* vVec = m_pFurObject->getRot();
		vVec->x += 1.f*fElapsd;
	}
}

//---------------------------------------------------------------------
void CSceneTask::_drawMain()
{
	IDirect3DDevice9* pDevice = AppContext::GetInstance()->getD3D9Device();
	
	IDirect3DSurface9*		pOldFrameBuffrerSurf( nullptr ), *pOldDepthBufferSurf(nullptr);
    pDevice->GetRenderTarget( 0, &pOldFrameBuffrerSurf );
	pDevice->GetRenderTarget( 1, &pOldDepthBufferSurf );

	// ビューポート
	D3DVIEWPORT9 OldViewport, NewViewport;
	pDevice->GetViewport( &OldViewport );

	// 反射テクスチャ作成
	{
		CopyMemory( &NewViewport, &OldViewport, sizeof( D3DVIEWPORT9 ) );
		NewViewport.Width  = AppContext::WINDOW_W>>1;
		NewViewport.Height = AppContext::WINDOW_H>>1;
		pDevice->SetViewport( &NewViewport );

		pDevice->SetRenderTarget( 0, m_pReflectSurf );
		pDevice->SetRenderTarget( 1, nullptr );
		pDevice->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00808080, 1.0f, 0 );
		pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
		
		const D3DXMATRIX mTmpWorld = *AppContext::GetInstance()->getWorldMatrix();
		D3DXMATRIX mSclMat;
		D3DXMatrixScaling( &mSclMat, 1.f, -1.f, 1.f );
		D3DXMatrixMultiply( &mSclMat, &mTmpWorld, &mSclMat );
		AppContext::GetInstance()->setWorldMatrix(&mSclMat);
		
		m_pBG->draw();
		util::for_each( m_pObject, std::mem_fun(&CObject::draw));
		
		AppContext::GetInstance()->setWorldMatrix(&mTmpWorld );
		pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
		pDevice->SetViewport( &OldViewport );
	}

	pDevice->SetRenderTarget( 0, pOldFrameBuffrerSurf );
	pDevice->SetRenderTarget( 1, pOldDepthBufferSurf );
	pDevice->Clear( 0, nullptr, D3DCLEAR_ZBUFFER, 0x00808080, 1.0f, 0 );
	pDevice->Clear( 1, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0 );
	pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

	// obj draw
	m_pBG->draw();
	util::for_each( m_pObject, std::mem_fun(&CObject::draw));

	m_pWater->draw();
	
	// ファー
	const SFurParam* pParam = &AppContext::GetInstance()->getShaderParam()->m_Fur;
	m_pFurObject->setPassDrawCount((unsigned int)pParam->m_fNum);
	m_pFurObject->draw();

    SAFE_RELEASE( pOldFrameBuffrerSurf );
	SAFE_RELEASE( pOldDepthBufferSurf );
}

//---------------------------------------------------------------------
void CSceneTask::deviceReset()
{
	HRESULT hr = S_OK;
	IDirect3DDevice9* pDevice = AppContext::GetInstance()->getD3D9Device();

	// レンダーターゲット
	_RET_CHECK(pDevice->CreateTexture( AppContext::WINDOW_W>>1,	AppContext::WINDOW_H>>1, 1,
											D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
											D3DPOOL_DEFAULT, &m_pReflectMap, nullptr ));
	_RET_CHECK(m_pReflectMap->GetSurfaceLevel(0, &m_pReflectSurf));

	m_pWater->setReflectTex( m_pReflectMap );

	util::for_each( m_pObject, std::mem_fun(&CObject::deviceReset) );
	m_pFurObject->deviceReset();
	m_pBG->deviceReset();
	m_pWater->deviceReset();
}
	
//---------------------------------------------------------------------
void CSceneTask::deviceLost()
{
	SAFE_RELEASE( m_pReflectMap );
	SAFE_RELEASE( m_pReflectSurf );

	util::for_each( m_pObject, std::mem_fun(&CObject::deviceLost) );
	m_pFurObject->deviceLost();
	m_pBG->deviceLost();
	m_pWater->deviceLost();
}

