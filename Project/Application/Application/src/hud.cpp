/**
	@file hud.cpp
	@brief hudの管理、表示
*/

#include "stdafx.h"

#include "hud.h"
#include "appContext.h"
#include "framework/job.h"
#include "framework/render.h"
#include "Optional/DXUTgui.h"
#include "Optional/SDKmisc.h"

//---------------------------------------------------------------------
CHud::CHud()
	:	CRender						("CHud", RENDER_PRIORITY::HUD)
	,	m_pDialogResourceManager	( nullptr )
	,	m_pTxtHelper				( nullptr )
	,	m_nResizeHandle				( 0 )
	,	m_nReleaseHandle			( 0 )
	,	m_nMsgProcHandle			( 0 )
{
	init();
}

//---------------------------------------------------------------------
CHud::~CHud()
{
	destroy();
}

//---------------------------------------------------------------------
void CHud::init()
{
	CAppContext* pApp = CAppContext::getInstance();
	m_pDialogResourceManager = new CDXUTDialogResourceManager;
	
    HRESULT hr;

	// デバイスの作成
    ID3D11DeviceContext* pd3dImmediateContext = pApp->getImmediateContext();
	_RET_CHECK_ASSERT( m_pDialogResourceManager->OnD3D11CreateDevice( CAppContext::getInstance()->getD3D11Device(), pd3dImmediateContext ) );
	m_pDialogResourceManager->OnD3D11ResizedSwapChain(pApp->getD3D11Device(), DXUTGetDXGIBackBufferSurfaceDesc());
	
	// デバイス側コールバックの登録
	m_nResizeHandle = pApp->addResizedSwapChainCB([this](ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc)
	{
		 HRESULT hr;
		_RET_CHECK_ASSERT( m_pDialogResourceManager->OnD3D11ResizedSwapChain( pd3dDevice, pBackBufferSurfaceDesc ) );
	});

	m_nReleaseHandle = pApp->addReleasingSwapChainCB([this]()
	{
	   m_pDialogResourceManager->OnD3D11ReleasingSwapChain();
	});
	
	m_nMsgProcHandle = pApp->addMsgProcCB([this](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing)
	{
		*pbNoFurtherProcessing = m_pDialogResourceManager->MsgProc( hWnd, uMsg, wParam, lParam );
	});

	// テキスト
	m_pTxtHelper = new CDXUTTextHelper( CAppContext::getInstance()->getD3D11Device(), pd3dImmediateContext, m_pDialogResourceManager, 15 );
}

//---------------------------------------------------------------------
void CHud::destroy()
{
	CAppContext* pApp = CAppContext::getInstance();
	pApp->deleteResizedSwapChainCB( m_nResizeHandle );
	pApp->deleteResizedSwapChainCB( m_nReleaseHandle );
	pApp->deleteResizedSwapChainCB( m_nMsgProcHandle );
	
	if (m_pDialogResourceManager) m_pDialogResourceManager->OnD3D11DestroyDevice();
	SAFE_DELETE(m_pDialogResourceManager);
	SAFE_DELETE(m_pTxtHelper);
}

//---------------------------------------------------------------------
void CHud::render()
{
	m_pTxtHelper->Begin();
	m_pTxtHelper->SetInsertionPos( 5, 5 );
	m_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
	m_pTxtHelper->DrawTextLine( DXUTGetFrameStats( DXUTIsVsyncEnabled() ) );
	m_pTxtHelper->DrawTextLine( DXUTGetDeviceStats() );
	m_pTxtHelper->End();
}



