/**
	@file appContext.cpp
	@brief アプリケーション管理
*/

#include "stdafx.h"
#include "appContext.h"
//#include "shader_task.h"
//#include "shader_set_value.h"
#include "Core/DXUT.h"
#include "framework/processManager.h"
#include "framework/thread.h"
#include "startJob.h"

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
		VERTEX_2D(D3DXVECTOR4 pos, D3DXVECTOR3 tex)
			:	m_vPos	(pos)
			,	m_vTex	(tex)
		{
		};

		D3DXVECTOR4 m_vPos;
		D3DXVECTOR3 m_vTex;
	};

	//２D板頂点
	static const VERTEX_2D s_VertexList[] =
	{
		VERTEX_2D( D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ),	D3DXVECTOR3( 1.0f, 0.0f, 1.0f ) ),
		VERTEX_2D( D3DXVECTOR4( 1.0f, -1.0f, 1.0f, 1.0f ),	D3DXVECTOR3( 1.0f, 1.0f, 1.0f ) ),
		VERTEX_2D( D3DXVECTOR4( -1.0f, 1.0f, 1.0f, 1.0f ),	D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) ),
		VERTEX_2D( D3DXVECTOR4( -1.0f, -1.0f, 1.0f, 1.0f ),	D3DXVECTOR3( 0.0f, 1.0f, 1.0f ) ),
	};
	static const int s_nVertexNum = NUM_OF(s_VertexList);
	
	static const char* s_chShaderParamFileName = "param.sdpt";
}

CAppContext*	CAppContext::m_pInstance = nullptr;

//---------------------------------------------------------------------
CAppContext::CAppContext()
	:	m_pJob					( nullptr )
	,	m_pRender				( nullptr )
	,	m_pd3dDevice			( nullptr )
	,	m_pImmediateContext		( nullptr )
	,	m_vDirectionalLightDir	(0.5f, 0.5f, 0.5f)
    ,	m_pVB					( nullptr )
    ,	m_pVertexDecl			( nullptr )
	,	m_pFrameBuffrerTex		( nullptr )
	,	m_pFrameBuffrerSurf		( nullptr )
	,	m_pDepthBufferTex		( nullptr )
	,	m_pDepthBufferSurf		( nullptr )
	,	m_pThreadChannel		( nullptr )
	,	m_pStartJob				( nullptr )
	,	m_nCpuCoreNum			( 0 )
	,	m_fElapsd				( 0.f )
	,	m_bIsInit				( false )
{
	memset( &m_ShaderParam, 0, sizeof(m_ShaderParam) );
	D3DXMatrixIdentity( &m_mWorld );
	D3DXMatrixIdentity( &m_mView );
	D3DXMatrixIdentity( &m_mProj );
	D3DXVec3Normalize( &m_vDirectionalLightDir, &m_vDirectionalLightDir );
}

//---------------------------------------------------------------------
CAppContext::~CAppContext()
{
	SAFE_TERMINATE(m_pStartJob);
	
	SAFE_DELETE(m_pThreadChannel);
	SAFE_DELETE(m_pJob);
	SAFE_DELETE(m_pRender);

	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pVertexDecl);
	SAFE_RELEASE(m_pImmediateContext);

	m_pd3dDevice = nullptr;
	m_bIsInit = false;
}

//---------------------------------------------------------------------
CAppContext* CAppContext::createInstance()
{
	_ASSERT( m_pInstance == nullptr );

	m_pInstance = new CAppContext();
	return m_pInstance;
}

//---------------------------------------------------------------------
CAppContext* CAppContext::getInstance()
{
	return m_pInstance;
}

//---------------------------------------------------------------------
void CAppContext::disposeInstance()
{
	SAFE_DELETE(m_pInstance);
}

//---------------------------------------------------------------------
void CAppContext::init(ID3D11Device* i_pDevice)
{
	HRESULT hr;
	if (m_bIsInit == true) return;

	m_pd3dDevice = i_pDevice;
	m_pd3dDevice->GetImmediateContext(&m_pImmediateContext);
	m_bIsInit = true;
	
	// cpuのコア数取得
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	m_nCpuCoreNum = SysInfo.dwNumberOfProcessors;

	// カメラ
	m_Camera.SetButtonMasks(0, MOUSE_WHEEL, MOUSE_LEFT_BUTTON);
	D3DXVECTOR3 vEye(-5.f,3.f,-5.f), vAt(0.f,0.f,0.f);
	m_Camera.SetViewParams( &vEye, &vAt );
 
	// 頂点情報の設定
//	_RET_CHECK( m_pd3dDevice->CreateVertexDeclaration( g_aDecl, &m_pVertexDecl ) );
	
	// パラメータファイルのロード
	FILE *fp;
	fopen_s(&fp, s_chShaderParamFileName, "rb");
	if( fp == nullptr )
	{
		_ASSERT( fp );
		MessageBox( DXUTGetHWND(), L"File Load Error!", L"Error", MB_ICONERROR | MB_OK );
		DXUTShutdown();
	}
	if(fp != nullptr)
	{
		fread(&m_ShaderParam, sizeof(m_ShaderParam), 1, fp);
		fclose(fp);
	}

	// リサイズ時のコールバック
	addResizedSwapChainCB([this](ID3D11Device* i_pDeveice, IDXGISwapChain*, const DXGI_SURFACE_DESC*)
	{
		m_pd3dDevice = i_pDeveice;
	});

	// プロセス関連
	m_pJob = new CJobManager();
	m_pRender = new CRenderManager();
	m_pJob->addJob( m_pStartJob = new CStartJob() );
	m_pThreadChannel = new CThreadChannel(m_nCpuCoreNum);

	// シェーダー作成
	m_ShaderManager.init();
}

//---------------------------------------------------------------------
void CAppContext::update(float i_fElapsd)
{
	m_fElapsd = i_fElapsd;

	// カメラ
	m_Camera.FrameMove( i_fElapsd );
	setWorldMatrix( m_Camera.GetWorldMatrix() );
	setViewMatrix( m_Camera.GetViewMatrix() );
	setProjMatrix( m_Camera.GetProjMatrix() );

	m_pJob->proc();
}

//---------------------------------------------------------------------
void CAppContext::render()
{
#if 0
	HRESULT hr = S_OK;
	IDirect3DSurface9*		pOldFrameBuffrerSurf( nullptr );
	IDirect3DSurface9*		pOldDepthBufferSurf( nullptr );

	//フレームバッファ入れ替え
    m_pd3dDevice->GetRenderTarget( 0, &pOldFrameBuffrerSurf );
    m_pd3dDevice->GetDepthStencilSurface( &pOldDepthBufferSurf );
	_RET_CHECK(m_pd3dDevice->SetRenderTarget( 0, m_pFrameBuffrerSurf ) );
	_RET_CHECK(m_pd3dDevice->SetRenderTarget( 1, m_pDepthBufferSurf ) );
	m_pd3dDevice->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00808080, 1.0f, 0 );
	m_pd3dDevice->Clear( 1, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0 );

	CTaskMan::getInstance()->draw();
	
	//フレームバッファ戻す
	m_pd3dDevice->SetRenderTarget( 0, pOldFrameBuffrerSurf );
    m_pd3dDevice->SetDepthStencilSurface( pOldDepthBufferSurf );
	m_pd3dDevice->Clear( 0L, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00808080, 1.0f, 0L );

	//最終描画
	const CShaderTask* pShaderTask = (CShaderTask*)CTaskMan::getInstance()->findTask("CShaderTask");
	_ASSERT( pShaderTask );
	CShaderSetValueDelegate* pDele = pShaderTask->getShaderDelegate(CShaderTask::S_I_2D);
	ID3DXEffect* pEffect = pDele->getEffect();

	UINT uiPass, uiNumPasses;
	_RET_CHECK( pEffect->SetTechnique( "normal" ) );
	_RET_CHECK( pEffect->SetTexture( "tex", getFrameBuffer() ) );

	m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof( VERTEX_2D ) );
	m_pd3dDevice->SetVertexDeclaration( m_pVertexDecl );
	
	pDele->preRenderSetParam(nullptr);

	_RET_CHECK( pEffect->Begin( &uiNumPasses, 0 ) );
	for( uiPass = 0; uiPass < uiNumPasses; uiPass++ )
	{
			pDele->passRenderSetParam(nullptr);
		_RET_CHECK( pEffect->BeginPass( uiPass ) );
	 	m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
		_RET_CHECK( pEffect->EndPass() );
	}

	_RET_CHECK( pEffect->End() );

    SAFE_RELEASE( pOldFrameBuffrerSurf );
    SAFE_RELEASE( pOldDepthBufferSurf );
#endif
    float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 0.0f };
    ID3D11RenderTargetView* pRTV = DXUTGetD3D11RenderTargetView();
	m_pImmediateContext->ClearRenderTargetView(pRTV, ClearColor);

    // Clear the depth stencil
    ID3D11DepthStencilView* pDSV = DXUTGetD3D11DepthStencilView();
	m_pImmediateContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0, 0);

	m_pRender->proc();
}

//---------------------------------------------------------------------
void CAppContext::getDirectionalLightDir(const D3DXVECTOR3* i_pDir)
{
	_ASSERT( i_pDir );
	m_vDirectionalLightDir = *i_pDir;
	D3DXVec3Normalize( &m_vDirectionalLightDir, &m_vDirectionalLightDir );
}

//---------------------------------------------------------------------
void CAppContext::setShaderParam( const SShaderParam* i_pParam )
{
	_ASSERT( i_pParam );
	memcpy(&m_ShaderParam, i_pParam, sizeof(m_ShaderParam));

	m_vDirectionalLightDir.x = m_ShaderParam.m_Others.m_f3LightDir[0];
	m_vDirectionalLightDir.y = m_ShaderParam.m_Others.m_f3LightDir[1];
	m_vDirectionalLightDir.z = m_ShaderParam.m_Others.m_f3LightDir[2];
	D3DXVec3Normalize( &m_vDirectionalLightDir, &m_vDirectionalLightDir );
}

//---------------------------------------------------------------------
void CAppContext::onResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc )
{
	util::for_each(m_fResizedSwapChain, [&](ResizedSwapChainArg& f)
	{
		f(pd3dDevice, pSwapChain, pBackBufferSurfaceDesc);
	});
}

//---------------------------------------------------------------------
void CAppContext::onReleasingSwapChain()
{
	util::for_each(m_fReleasingSwapChain, [](ReleasingSwapChainArg& f)
	{
		f();
	});
}

//---------------------------------------------------------------------
void CAppContext::onMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing )
{
	util::for_each(m_fMsgProc, [&](MsgProcChainArg& f)
	{
		if( *pbNoFurtherProcessing ) return;
		f(hWnd, uMsg, wParam, lParam, pbNoFurtherProcessing);
	});
}

//---------------------------------------------------------------------
size_t CAppContext::addResizedSwapChainCB(ResizedSwapChainArg f)
{
	m_fResizedSwapChain.push_back( f );
	return (size_t)(&m_fResizedSwapChain.back());
}

//---------------------------------------------------------------------
void CAppContext::deleteResizedSwapChainCB(size_t i_nHandle)
{
	auto val = std::find_if(m_fResizedSwapChain.begin(), m_fResizedSwapChain.end(), 
		[&](ResizedSwapChainArg& f){ return ((size_t)&f == i_nHandle); } );
	if( val == m_fResizedSwapChain.end() ) return;

	m_fResizedSwapChain.erase(val);
}
	
//---------------------------------------------------------------------
size_t CAppContext::addReleasingSwapChainCB(ReleasingSwapChainArg f)
{
	m_fReleasingSwapChain.push_back( f );
	return (size_t)(&m_fReleasingSwapChain.back());
}

//---------------------------------------------------------------------
void CAppContext::deleteReleasingSwapChainCB(size_t i_nHandle)
{
	auto val = std::find_if(m_fReleasingSwapChain.begin(), m_fReleasingSwapChain.end(), 
		[&](ReleasingSwapChainArg& f){ return  (size_t)(&f) == i_nHandle; } );
	if( val == m_fReleasingSwapChain.end() ) return;

	m_fReleasingSwapChain.erase(val);
}

//---------------------------------------------------------------------
size_t CAppContext::addMsgProcCB(MsgProcChainArg f)
{
	m_fMsgProc.push_back( f );
	return (size_t)(&m_fMsgProc.back());
}

//---------------------------------------------------------------------
void CAppContext::deleteMsgProcCB(size_t i_nHandle)
{
	auto val = std::find_if(m_fMsgProc.begin(), m_fMsgProc.end(), 
		[&](MsgProcChainArg& f){ return  (size_t)(&f) == i_nHandle; } );
	if( val == m_fMsgProc.end() ) return;

	m_fMsgProc.erase(val);
}


