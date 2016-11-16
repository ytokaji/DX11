/**
	@file post_effect_task.cpp
	@brief ポストエフェクトの処理、表示
*/

#include "stdafx.h"
#include "post_effect_task.h"
#include "application.h"
#include "shader_set_value.h"

namespace
{
	// 頂点情報の宣言
	static const D3DVERTEXELEMENT9 g_aDecl[] =
	{
		 { 0, 0,	D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	// ポジション
		 { 0, 16,	D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// UV
		 D3DDECL_END()
	};

	// 頂点設定
	struct VERTEX_2D
	{
		VERTEX_2D(DirectX::SimpleMath::Vector4 pos, DirectX::SimpleMath::Vector3 tex)
			:	m_vPos	(pos)
			,	m_vTex	(tex)
		{
		};

		DirectX::SimpleMath::Vector4 m_vPos;
		DirectX::SimpleMath::Vector3 m_vTex;
	};

	//２D板頂点
	static const VERTEX_2D s_VertexList[] =
	{
		VERTEX_2D( DirectX::SimpleMath::Vector4( 1.0f, 1.0f, 1.0f, 1.0f ),	DirectX::SimpleMath::Vector3( 1.0f, 0.0f, 1.0f ) ),
		VERTEX_2D( DirectX::SimpleMath::Vector4( 1.0f, -1.0f, 1.0f, 1.0f ),	DirectX::SimpleMath::Vector3( 1.0f, 1.0f, 1.0f ) ),
		VERTEX_2D( DirectX::SimpleMath::Vector4( -1.0f, 1.0f, 1.0f, 1.0f ),	DirectX::SimpleMath::Vector3( 0.0f, 0.0f, 1.0f ) ),
		VERTEX_2D( DirectX::SimpleMath::Vector4( -1.0f, -1.0f, 1.0f, 1.0f ),	DirectX::SimpleMath::Vector3( 0.0f, 1.0f, 1.0f ) ),
	};
	static const int s_nVertexNum = NUM_OF(s_VertexList);
}

const CPostEffectTask::ProcFunc	CPostEffectTask::m_pRunFunc[] =
{
	&CPostEffectTask::_runInit,
	&CPostEffectTask::_runMain,
};

const CPostEffectTask::ProcFunc	CPostEffectTask::m_pDrawFunc[] =
{
	&CPostEffectTask::_dummy,
	&CPostEffectTask::_drawMain,
};

const unsigned int CPostEffectTask::m_nBufferSize[BufferIndex_Max][2] =
{
	{ 32, 32 },
	{ 64, 64 },
	{ 96, 96 },
	{ 256, 256 },
	{ AppContext::WINDOW_W, AppContext::WINDOW_H },
};

//---------------------------------------------------------------------
CPostEffectTask::CPostEffectTask()
	:	CTask					( "CPostEffectTask" )
    ,	m_pVB					( nullptr )
    ,	m_pVertexDecl			( nullptr )
{
	STATIC_ASSERT(NUM_OF(m_pRunFunc)==STATE_MAX);
	STATIC_ASSERT(NUM_OF(m_pDrawFunc)==STATE_MAX);

	memset( m_pFilterTex, nullptr, sizeof( m_pFilterTex ) );
	memset( m_pFilterSurf, nullptr, sizeof( m_pFilterSurf ) );
	
	// 頂点情報の設定
	AppContext::GetInstance()->getD3D9Device()->CreateVertexDeclaration( g_aDecl, &m_pVertexDecl );

	setSubTask(STATE_INIT);
}

//---------------------------------------------------------------------
CPostEffectTask::~CPostEffectTask()
{
	deviceLost();

	SAFE_RELEASE( m_pVB );
	SAFE_RELEASE( m_pVertexDecl );
}

//---------------------------------------------------------------------
void CPostEffectTask::_runInit()
{
	deviceReset();

	setSubTask(STATE_MAIN);
}

//---------------------------------------------------------------------
void CPostEffectTask::_runMain()
{
}

//---------------------------------------------------------------------
void CPostEffectTask::_drawMain()
{
	IDirect3DDevice9* pDevice = AppContext::GetInstance()->getD3D9Device();
	HRESULT hr = S_OK;
	
	const SPostParam* pParam = &AppContext::GetInstance()->getShaderParam()->m_Post;
	const CShaderTask* pShaderTask = (CShaderTask*)CTaskMan::getInstance()->findTask("CShaderTask");
	_ASSERT( pShaderTask );
	CShaderSetValueDelegate* pDele = nullptr;
	ID3DXEffect* pEffect = nullptr;

	IDirect3DSurface9*		pFrameBuffrerSurf( nullptr ), *pOldDepthBufferSurf(nullptr);;
	pDevice->GetRenderTarget( 0, &pFrameBuffrerSurf );
	pDevice->GetRenderTarget( 1, &pOldDepthBufferSurf );
	pDevice->SetRenderTarget( 1, nullptr );


	// ブルーム
	if( pParam->m_bBloomUse )
	{
		// 輝度抽出;
		{
			pDele = pShaderTask->getShaderDelegate( CShaderTask::S_I_BRIGHTNESS );
			pEffect = pDele->getEffect();
			CPostEffectTask::drawSurface(m_pFilterSurf[BufferIndex_FrameBuffer],
				m_nBufferSize[BufferIndex_FrameBuffer][0], m_nBufferSize[BufferIndex_FrameBuffer][1], CShaderTask::S_I_BRIGHTNESS, true, "render" );
		}

		// ガウスフィルタ
		{
			pDele = pShaderTask->getShaderDelegate( CShaderTask::S_I_GAUSSIAN );
			pEffect = pDele->getEffect();
			_RET_CHECK( pEffect->SetTexture( "tex", m_pFilterTex[BufferIndex_FrameBuffer] ) );
			CPostEffectTask::drawSurface(m_pFilterSurf[BufferIndex_32x32],
						m_nBufferSize[BufferIndex_32x32][0], m_nBufferSize[BufferIndex_32x32][1], CShaderTask::S_I_GAUSSIAN, true, "render" );
			CPostEffectTask::drawSurface(m_pFilterSurf[BufferIndex_64x64],
						m_nBufferSize[BufferIndex_64x64][0], m_nBufferSize[BufferIndex_64x64][1], CShaderTask::S_I_GAUSSIAN, true, "render" );
			CPostEffectTask::drawSurface(m_pFilterSurf[BufferIndex_96x96],
						m_nBufferSize[BufferIndex_96x96][0], m_nBufferSize[BufferIndex_96x96][1], CShaderTask::S_I_GAUSSIAN, true, "render" );
		}

		// 高輝度加算
		{
			pDele = pShaderTask->getShaderDelegate( CShaderTask::S_I_2D );
			pEffect = pDele->getEffect();
			_RET_CHECK( pEffect->SetTexture( "tex", m_pFilterTex[BufferIndex_32x32] ) );	
			CPostEffectTask::drawSurface(pFrameBuffrerSurf,
					m_nBufferSize[BufferIndex_FrameBuffer][0], m_nBufferSize[BufferIndex_FrameBuffer][1], CShaderTask::S_I_2D, false,"add" );

			_RET_CHECK( pEffect->SetTexture( "tex", m_pFilterTex[BufferIndex_64x64] ) );
			CPostEffectTask::drawSurface(pFrameBuffrerSurf,
					m_nBufferSize[BufferIndex_FrameBuffer][0], m_nBufferSize[BufferIndex_FrameBuffer][1], CShaderTask::S_I_2D, false, "add" );
		
			_RET_CHECK( pEffect->SetTexture( "tex", m_pFilterTex[BufferIndex_96x96] ) );
			CPostEffectTask::drawSurface(pFrameBuffrerSurf,
					m_nBufferSize[BufferIndex_FrameBuffer][0], m_nBufferSize[BufferIndex_FrameBuffer][1], CShaderTask::S_I_2D, false, "add" );
		}
	}

	//Dof
	if( pParam->m_bDofUse )
	{
		// ガウスフィルタ
		{
			pDele = pShaderTask->getShaderDelegate( CShaderTask::S_I_GAUSSIAN );
			pEffect = pDele->getEffect();
			_RET_CHECK( pEffect->SetTexture( "tex", AppContext::GetInstance()->getFrameBuffer() ) );
			CPostEffectTask::drawSurface(m_pFilterSurf[BufferIndex_256x256],
						m_nBufferSize[BufferIndex_256x256][0], m_nBufferSize[BufferIndex_256x256][1], CShaderTask::S_I_GAUSSIAN, true, "render" );
		}

		//dof
		{
			pDele = pShaderTask->getShaderDelegate( CShaderTask::S_I_DOF );
			pEffect = pDele->getEffect();
			_RET_CHECK( pEffect->SetTexture( "blurTex", m_pFilterTex[BufferIndex_256x256] ) );
			CPostEffectTask::drawSurface(pFrameBuffrerSurf,
						m_nBufferSize[BufferIndex_FrameBuffer][0], m_nBufferSize[BufferIndex_FrameBuffer][1], CShaderTask::S_I_DOF, false, "render" );
		}
	}

// テスト用
#if 0
	BufferIndex eBuffIndex = BufferIndex_256x256;
	{
		_RET_CHECK( pEffect->SetTexture( "tex", m_pFilterTex[BufferIndex_256x256] ) );
		CPostEffectTask::drawSurface(pFrameBuffrerSurf,
				m_nBufferSize[eBuffIndex][0], m_nBufferSize[eBuffIndex][1], CShaderTask::S_I_2D, true, "normal" );

	}
#endif
	
	pDevice->SetRenderTarget( 0, pFrameBuffrerSurf );
	pDevice->SetRenderTarget( 1, pOldDepthBufferSurf );
	SAFE_RELEASE( pFrameBuffrerSurf );
	SAFE_RELEASE( pOldDepthBufferSurf );
}

//---------------------------------------------------------------------
void CPostEffectTask::deviceReset()
{
	HRESULT hr = S_OK;
	IDirect3DDevice9* pDevice = AppContext::GetInstance()->getD3D9Device();

	// レンダーターゲット
	for( unsigned int i=0; i<BufferIndex_Max; ++i )
	{
		_RET_CHECK(pDevice->CreateTexture( m_nBufferSize[i][0], m_nBufferSize[i][1], 1,
											D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
											D3DPOOL_DEFAULT, &m_pFilterTex[i], nullptr ));
		_RET_CHECK(m_pFilterTex[i]->GetSurfaceLevel(0, &m_pFilterSurf[i]));
	}

	// 板
	_RET_CHECK(pDevice->CreateVertexBuffer( sizeof(s_VertexList),
										D3DUSAGE_WRITEONLY, 0,
										D3DPOOL_DEFAULT, &m_pVB, nullptr ) );

	 VERTEX_2D* pVertex = nullptr;
	 _RET_CHECK( m_pVB->Lock( 0, 0, ( void** )&pVertex, 0 ) );
	 memcpy( pVertex, &s_VertexList, sizeof(s_VertexList) );
	 m_pVB->Unlock();

}
	
//---------------------------------------------------------------------
void CPostEffectTask::deviceLost()
{
	for( unsigned int i=0; i<BufferIndex_Max; ++i )
	{	
		SAFE_RELEASE( m_pFilterTex[i] );
		SAFE_RELEASE( m_pFilterSurf[i] );
	}

	SAFE_RELEASE( m_pVB );
}

//---------------------------------------------------------------------
void CPostEffectTask::drawSurface(IDirect3DSurface9* i_pRenderSurf, unsigned int i_nWindwW, unsigned int i_nWindwH, 
									CShaderTask::SHADER_INDEX i_eS_I, bool i_bClear, const char* i_pchTechnique )
{
	IDirect3DDevice9* pDevice = AppContext::GetInstance()->getD3D9Device();
	HRESULT hr = S_OK;

	IDirect3DSurface9*		pOldFrameBuffrerSurf( nullptr );
	pDevice->GetRenderTarget( 0, &pOldFrameBuffrerSurf );

	// ビューポート
	D3DVIEWPORT9 oldViewport, newViewport;
	pDevice->GetViewport( &oldViewport );
	memcpy( &newViewport, &oldViewport, sizeof( D3DVIEWPORT9 ) );
	newViewport.Width  = i_nWindwW;
	newViewport.Height = i_nWindwH;
	pDevice->SetViewport( &newViewport );

	//フレームバッファ入れ替え
	pDevice->SetRenderTarget( 0, i_pRenderSurf );
	if( i_bClear ) pDevice->Clear( 0, nullptr, D3DCLEAR_TARGET, 0x00000000, 1.0f, 0 );

	// ステート
	pDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, D3DZB_FALSE );

	//描画
	const CShaderTask* pShaderTask = (CShaderTask*)CTaskMan::getInstance()->findTask("CShaderTask");
	_ASSERT( pShaderTask );
	CShaderSetValueDelegate* pDele = pShaderTask->getShaderDelegate(i_eS_I);
	ID3DXEffect* pEffect = pDele->getEffect();

	UINT uiPass, uiNumPasses;
	_RET_CHECK( pEffect->SetTechnique( i_pchTechnique ) )

	pDevice->SetStreamSource( 0, m_pVB, 0, sizeof( VERTEX_2D ) );
	pDevice->SetVertexDeclaration( m_pVertexDecl );
	pDele->preRenderSetParam(nullptr);

	_RET_CHECK( pEffect->Begin( &uiNumPasses, 0 ) );
	for( uiPass = 0; uiPass < uiNumPasses; uiPass++ )
	{
		pDele->passRenderSetParam(nullptr);
		_RET_CHECK( pEffect->BeginPass( uiPass ) );
	 	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
		_RET_CHECK( pEffect->EndPass() );
	}
	_RET_CHECK( pEffect->End() );

	// 戻す
	pDevice->SetViewport( &oldViewport );
	pDevice->SetRenderTarget( 0, pOldFrameBuffrerSurf );
	SAFE_RELEASE( pOldFrameBuffrerSurf );
	pDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, D3DZB_TRUE );
}

