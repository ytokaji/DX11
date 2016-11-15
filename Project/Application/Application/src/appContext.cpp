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
	static const D3DVERTEXELEMENT9 DECL[] =
	{
		 { 0, 0,	D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	// ポジション
		 { 0, 16,	D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// UV
		 D3DDECL_END()
	};

	// 頂点設定
	struct VERTEX_2D
	{
		VERTEX_2D(D3DXVECTOR4 pos, D3DXVECTOR3 tex)
			:	_pos	(pos)
			,	_tex	(tex)
		{
		};

		D3DXVECTOR4 _pos;
		D3DXVECTOR3 _tex;
	};

	//２D板頂点
	static const VERTEX_2D VERTEX_LIST[] =
	{
		VERTEX_2D( D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ),	D3DXVECTOR3( 1.0f, 0.0f, 1.0f ) ),
		VERTEX_2D( D3DXVECTOR4( 1.0f, -1.0f, 1.0f, 1.0f ),	D3DXVECTOR3( 1.0f, 1.0f, 1.0f ) ),
		VERTEX_2D( D3DXVECTOR4( -1.0f, 1.0f, 1.0f, 1.0f ),	D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) ),
		VERTEX_2D( D3DXVECTOR4( -1.0f, -1.0f, 1.0f, 1.0f ),	D3DXVECTOR3( 0.0f, 1.0f, 1.0f ) ),
	};
	static const int VERTEX_LIST_NUM = NUM_OF(VERTEX_LIST);
	
	static const char* SHADER_PARA_FILE_NAME = "param.sdpt";
}

AppContext*	AppContext::_instance = nullptr;

//---------------------------------------------------------------------
AppContext::AppContext()
	:	_job					( nullptr )
	,	_render					( nullptr )
	,	_device					( nullptr )
	,	_immediateContext		( nullptr )
	,	_directionalLightDir	(0.5f, 0.5f, 0.5f)
	,	_threadChannel			( nullptr )
	,	_startJob				( nullptr )
	,	_cpuCoreNum				( 0 )
	,	_elapsd					( 0.f )
	,	_isInit					( false )
{
	memset( &_shaderParam, 0, sizeof(_shaderParam) );
	D3DXMatrixIdentity( &_worldMatrix );
	D3DXMatrixIdentity( &_viewMatrix );
	D3DXMatrixIdentity( &_projMatrix );
	D3DXVec3Normalize( &_directionalLightDir, &_directionalLightDir );
}

//---------------------------------------------------------------------
AppContext::~AppContext()
{
	SAFE_TERMINATE(_startJob);
	
	SAFE_DELETE(_threadChannel);
	SAFE_DELETE(_job);
	SAFE_DELETE(_render);

	SAFE_RELEASE(_immediateContext);

	_device = nullptr;
	_isInit = false;
}

//---------------------------------------------------------------------
AppContext* AppContext::CreateInstance()
{
	_ASSERT( _instance == nullptr );

	_instance = new AppContext();
	return _instance;
}

//---------------------------------------------------------------------
AppContext* AppContext::GetInstance()
{
	return _instance;
}

//---------------------------------------------------------------------
void AppContext::DisposeInstance()
{
	SAFE_DELETE(_instance);
}

//---------------------------------------------------------------------
void AppContext::Init(ID3D11Device* device)
{
	if (_isInit == true) return;

	_device = device;
	_device->GetImmediateContext(&_immediateContext);
	_isInit = true;
	
	// cpuのコア数取得
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	_cpuCoreNum = SysInfo.dwNumberOfProcessors;

	// カメラ
	_camera.SetButtonMasks(0, MOUSE_WHEEL, MOUSE_LEFT_BUTTON);
	D3DXVECTOR3 vEye(-5.f,3.f,-5.f), vAt(0.f,0.f,0.f);
	_camera.SetViewParams( &vEye, &vAt );
 
	// 頂点情報の設定
//	_RET_CHECK( m_pd3dDevice->CreateVertexDeclaration( g_aDecl, &m_pVertexDecl ) );
	
	// パラメータファイルのロード
	FILE *fp;
	fopen_s(&fp, SHADER_PARA_FILE_NAME, "rb");
	if( fp == nullptr )
	{
		_ASSERT( fp );
		MessageBox( DXUTGetHWND(), L"File Load Error!", L"Error", MB_ICONERROR | MB_OK );
		DXUTShutdown();
	}
	if(fp != nullptr)
	{
		fread(&_shaderParam, sizeof(_shaderParam), 1, fp);
		fclose(fp);
	}

	// リサイズ時のコールバック
	AddResizedSwapChainCB([this](ID3D11Device* i_pDeveice, IDXGISwapChain*, const DXGI_SURFACE_DESC*)
	{
		_device = i_pDeveice;
	});

	// プロセス関連
	_job = new CJobManager();
	_render = new CRenderManager();
	_job->addJob( _startJob = new CStartJob() );
	_threadChannel = new CThreadChannel(_cpuCoreNum);

	// シェーダー作成
	_shaderManager.init();
}

//---------------------------------------------------------------------
void AppContext::Update(float elapsd)
{
	_elapsd = elapsd;

	// カメラ
	_camera.FrameMove( elapsd );
	SetWorldMatrix( _camera.GetWorldMatrix() );
	SetViewMatrix( _camera.GetViewMatrix() );
	SetProjMatrix( _camera.GetProjMatrix() );

	_job->proc();
}

//---------------------------------------------------------------------
void AppContext::Render()
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
	_immediateContext->ClearRenderTargetView(pRTV, ClearColor);

    // Clear the depth stencil
    ID3D11DepthStencilView* pDSV = DXUTGetD3D11DepthStencilView();
	_immediateContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0, 0);

	_render->proc();
}

//---------------------------------------------------------------------
void AppContext::GetDirectionalLightDir(const D3DXVECTOR3* dir)
{
	_ASSERT( dir );
	_directionalLightDir = *dir;
	D3DXVec3Normalize( &_directionalLightDir, &_directionalLightDir );
}

//---------------------------------------------------------------------
void AppContext::SetShaderParam( const SShaderParam* param )
{
	_ASSERT( param );
	memcpy(&_shaderParam, param, sizeof(_shaderParam));

	_directionalLightDir.x = _shaderParam.m_Others.m_f3LightDir[0];
	_directionalLightDir.y = _shaderParam.m_Others.m_f3LightDir[1];
	_directionalLightDir.z = _shaderParam.m_Others.m_f3LightDir[2];
	D3DXVec3Normalize( &_directionalLightDir, &_directionalLightDir );
}

//---------------------------------------------------------------------
void AppContext::OnResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc )
{
	util::for_each(_resizedSwapChain, [&](ResizedSwapChainArg& f)
	{
		f(pd3dDevice, pSwapChain, pBackBufferSurfaceDesc);
	});
}

//---------------------------------------------------------------------
void AppContext::OnReleasingSwapChain()
{
	util::for_each(_releasingSwapChain, [](ReleasingSwapChainArg& f)
	{
		f();
	});
}

//---------------------------------------------------------------------
void AppContext::OnMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing )
{
	util::for_each(_msgProc, [&](MsgProcChainArg& f)
	{
		if( *pbNoFurtherProcessing ) return;
		f(hWnd, uMsg, wParam, lParam, pbNoFurtherProcessing);
	});
}

//---------------------------------------------------------------------
size_t AppContext::AddResizedSwapChainCB(ResizedSwapChainArg f)
{
	_resizedSwapChain.push_back( f );
	return (size_t)(&_resizedSwapChain.back());
}

//---------------------------------------------------------------------
void AppContext::DeleteResizedSwapChainCB(size_t handle)
{
	auto val = std::find_if(_resizedSwapChain.begin(), _resizedSwapChain.end(), 
		[&](ResizedSwapChainArg& f){ return ((size_t)&f == handle); } );
	if( val == _resizedSwapChain.end() ) return;

	_resizedSwapChain.erase(val);
}
	
//---------------------------------------------------------------------
size_t AppContext::AddReleasingSwapChainCB(ReleasingSwapChainArg f)
{
	_releasingSwapChain.push_back( f );
	return (size_t)(&_releasingSwapChain.back());
}

//---------------------------------------------------------------------
void AppContext::DeleteReleasingSwapChainCB(size_t handle)
{
	auto val = std::find_if(_releasingSwapChain.begin(), _releasingSwapChain.end(), 
		[&](ReleasingSwapChainArg& f){ return  (size_t)(&f) == handle; } );
	if( val == _releasingSwapChain.end() ) return;

	_releasingSwapChain.erase(val);
}

//---------------------------------------------------------------------
size_t AppContext::AddMsgProcCB(MsgProcChainArg f)
{
	_msgProc.push_back( f );
	return (size_t)(&_msgProc.back());
}

//---------------------------------------------------------------------
void AppContext::DeleteMsgProcCB(size_t handle)
{
	auto val = std::find_if(_msgProc.begin(), _msgProc.end(), 
		[&](MsgProcChainArg& f){ return  (size_t)(&f) == handle; } );
	if( val == _msgProc.end() ) return;

	_msgProc.erase(val);
}


