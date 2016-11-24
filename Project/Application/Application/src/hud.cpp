/**
	@file hud.cpp
	@brief hud�̊Ǘ��A�\��
*/

#include "stdafx.h"

#include "hud.h"
#include "appContext.h"
#include "framework/renderManager.h"

//---------------------------------------------------------------------
Hud::Hud()
	:	_dialogResourceManager	( nullptr )
	,	_txtHelper				( nullptr )
	,	_render					( "Hud", nullptr, std::bind(&Hud::RenderAsync,this), nullptr, RENDER_PRIORITY::HUD )
	,	_resizeHandle			( 0 )
	,	_releaseHandle			( 0 )
	,	_msgProcHandle			( 0 )
{
	Init();
}

//---------------------------------------------------------------------
Hud::~Hud()
{
	Destroy();
}

//---------------------------------------------------------------------
void Hud::Init()
{
	AppContext* app = AppContext::GetInstance();
	_dialogResourceManager = new CDXUTDialogResourceManager;
	
    HRESULT hr;

	// �f�o�C�X�̍쐬
	ID3D11DeviceContext* activeContext = _render.GetDeviceContext();
	_RET_CHECK_ASSERT(_dialogResourceManager->OnD3D11CreateDevice(AppContext::GetInstance()->GetD3D11Device(), activeContext));
	_dialogResourceManager->OnD3D11ResizedSwapChain(app->GetD3D11Device(), DXUTGetDXGIBackBufferSurfaceDesc());
	
	// �f�o�C�X���R�[���o�b�N�̓o�^
	_resizeHandle = app->AddResizedSwapChainCB([this](ID3D11Device* pd3dDevice, IDXGISwapChain* /*pSwapChain*/, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc)
	{
		 HRESULT hr;
		_RET_CHECK_ASSERT( _dialogResourceManager->OnD3D11ResizedSwapChain( pd3dDevice, pBackBufferSurfaceDesc ) );
	});

	_releaseHandle = app->AddReleasingSwapChainCB([this]()
	{
	   _dialogResourceManager->OnD3D11ReleasingSwapChain();
	});
	
	_msgProcHandle = app->AddMsgProcCB([this](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing)
	{
		*pbNoFurtherProcessing = _dialogResourceManager->MsgProc( hWnd, uMsg, wParam, lParam );
	});

	// �e�L�X�g
	_txtHelper = new CDXUTTextHelper(AppContext::GetInstance()->GetD3D11Device(), activeContext, _dialogResourceManager, 15);

	// �o�^
	AppContext::GetInstance()->GetRenderManager()->AddRender(&_render);
}

//---------------------------------------------------------------------
void Hud::Destroy()
{
	AppContext* app = AppContext::GetInstance();
	app->DeleteResizedSwapChainCB( _resizeHandle );
	app->DeleteResizedSwapChainCB( _releaseHandle );
	app->DeleteResizedSwapChainCB( _msgProcHandle );

	if (_dialogResourceManager){ _dialogResourceManager->OnD3D11DestroyDevice(); }
	SAFE_DELETE(_dialogResourceManager);
	SAFE_DELETE(_txtHelper);

	_render.Destroy();
}

//---------------------------------------------------------------------
void Hud::RenderAsync()
{
	_txtHelper->Begin();
	_txtHelper->SetInsertionPos( 20, 20 );
	_txtHelper->SetForegroundColor( DirectX::SimpleMath::Color( 1.0f, 1.0f, 0.0f, 1.0f ) );
	_txtHelper->DrawTextLine( DXUTGetFrameStats( DXUTIsVsyncEnabled() ) );
	_txtHelper->DrawTextLine( DXUTGetDeviceStats() );
	_txtHelper->End();
}



