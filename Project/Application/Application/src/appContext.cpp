/**
	@file appContext.cpp
	@brief アプリケーション管理
*/

#include "stdafx.h"
#include "appContext.h"
#include "framework/processManager.h"
#include "framework/renderManager.h"
#include "framework/jobManager.h"
#include "framework/thread.h"
#include "framework/render.h"
#include "startJob.h"

using namespace cpplinq;

namespace
{
	// 頂点設定
	struct VERTEX_2D
	{
		VERTEX_2D(DirectX::SimpleMath::Vector4 pos, DirectX::SimpleMath::Vector3 tex)
			:	_pos	(pos)
			,	_tex	(tex)
		{
		};

		DirectX::SimpleMath::Vector4 _pos;
		DirectX::SimpleMath::Vector3 _tex;
	};

	//２D板頂点
	static const VERTEX_2D VERTEX_LIST[] =
	{
		VERTEX_2D( DirectX::SimpleMath::Vector4( 1.0f, 1.0f, 1.0f, 1.0f ),	DirectX::SimpleMath::Vector3( 1.0f, 0.0f, 1.0f ) ),
		VERTEX_2D( DirectX::SimpleMath::Vector4( 1.0f, -1.0f, 1.0f, 1.0f ),	DirectX::SimpleMath::Vector3( 1.0f, 1.0f, 1.0f ) ),
		VERTEX_2D( DirectX::SimpleMath::Vector4( -1.0f, 1.0f, 1.0f, 1.0f ),	DirectX::SimpleMath::Vector3( 0.0f, 0.0f, 1.0f ) ),
		VERTEX_2D( DirectX::SimpleMath::Vector4( -1.0f, -1.0f, 1.0f, 1.0f ),	DirectX::SimpleMath::Vector3( 0.0f, 1.0f, 1.0f ) ),
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
	,	_worldMatrix			( DirectX::SimpleMath::Matrix::Identity )
	,	_viewMatrix				( DirectX::SimpleMath::Matrix::Identity )
	,	_projMatrix				( DirectX::SimpleMath::Matrix::Identity )
	,	_directionalLightDir	(0.5f, 0.5f, 0.5f)
	,	_threadChannel			( nullptr )
	,	_startJob				( nullptr )
	,	_cpuCoreNum				( 0 )
	,	_elapsd					( 0.f )
	,	_isInit					( false )
{
	memset( &_shaderParam, 0, sizeof(_shaderParam) );
	_directionalLightDir.Normalize();
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
	DirectX::SimpleMath::Vector3 vEye(-5.f,3.f,-5.f), vAt(0.f,0.f,0.f);
	_camera.SetViewParams( vEye, vAt );
 
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
	_job = new JobManager();
	_render = new RenderManager();
	_job->AddJob( _startJob = new StartJob() );
	_threadChannel = new ThreadChannel(_cpuCoreNum);

	// シェーダー作成
	_shaderManager.Init();
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

	_job->Proc();
}

//---------------------------------------------------------------------
void AppContext::Render()
{
	// バッファのクリア
    float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 0.0f };
    ID3D11RenderTargetView* pRTV = DXUTGetD3D11RenderTargetView();
	_immediateContext->ClearRenderTargetView(pRTV, ClearColor);
    ID3D11DepthStencilView* pDSV = DXUTGetD3D11DepthStencilView();
	_immediateContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0, 0);

	_render->Proc();
}

//---------------------------------------------------------------------
void AppContext::SetDirectionalLightDir(const DirectX::SimpleMath::Vector3& dir)
{
	_directionalLightDir = dir;
	_directionalLightDir.Normalize();
}

//---------------------------------------------------------------------
void AppContext::SetShaderParam( const SShaderParam* param )
{
	_ASSERT( param );
	memcpy(&_shaderParam, param, sizeof(_shaderParam));

	_directionalLightDir.x = _shaderParam.m_Others._lightDir[0];
	_directionalLightDir.y = _shaderParam.m_Others._lightDir[1];
	_directionalLightDir.z = _shaderParam.m_Others._lightDir[2];
	_directionalLightDir.Normalize();
}

//---------------------------------------------------------------------
void AppContext::OnResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc )
{
	for (const auto& i : _resizedSwapChain) { i(pd3dDevice, pSwapChain, pBackBufferSurfaceDesc); }
}

//---------------------------------------------------------------------
void AppContext::OnReleasingSwapChain()
{
	for (const auto& i : _releasingSwapChain) { i(); }
}

//---------------------------------------------------------------------
void AppContext::OnMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing )
{
	for each (auto& i in _msgProc)
	{
		if (*pbNoFurtherProcessing) return;
		i(hWnd, uMsg, wParam, lParam, pbNoFurtherProcessing);
	}
}

//---------------------------------------------------------------------
uintptr_t AppContext::AddResizedSwapChainCB(ResizedSwapChainArg f)
{
	_resizedSwapChain.push_back( f );
	return (uintptr_t)(&_resizedSwapChain.back());
}

//---------------------------------------------------------------------
void AppContext::DeleteResizedSwapChainCB(uintptr_t handle)
{
	auto val = std::find_if(_resizedSwapChain.begin(), _resizedSwapChain.end(), 
		[&](ResizedSwapChainArg& f){ return ((uintptr_t)&f == handle); });
	if( val == _resizedSwapChain.end() ) return;

	_resizedSwapChain.erase(val);
}
	
//---------------------------------------------------------------------
uintptr_t AppContext::AddReleasingSwapChainCB(ReleasingSwapChainArg f)
{
	_releasingSwapChain.push_back( f );
	return (uintptr_t)(&_releasingSwapChain.back());
}

//---------------------------------------------------------------------
void AppContext::DeleteReleasingSwapChainCB(uintptr_t handle)
{
	auto val = std::find_if(_releasingSwapChain.begin(), _releasingSwapChain.end(), 
		[&](ReleasingSwapChainArg& f){ return  (uintptr_t)(&f) == handle; });
	if( val == _releasingSwapChain.end() ) return;

	_releasingSwapChain.erase(val);
}

//---------------------------------------------------------------------
uintptr_t AppContext::AddMsgProcCB(MsgProcChainArg f)
{
	_msgProc.push_back( f );
	return (uintptr_t)(&_msgProc.back());
}

//---------------------------------------------------------------------
void AppContext::DeleteMsgProcCB(uintptr_t handle)
{
	auto val = std::find_if(_msgProc.begin(), _msgProc.end(), 
		[&](MsgProcChainArg& f){ return  (uintptr_t)(&f) == handle; });
	if( val == _msgProc.end() ) return;

	_msgProc.erase(val);
}


