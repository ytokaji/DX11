/**
	@file main.cpp
	@brief メイン関数
*/

#include "stdafx.h"

#include "Core/DXUT.h"
#include "Optional/DXUTcamera.h"
#include "Optional/DXUTsettingsdlg.h"
#include "Optional/SDKmisc.h"
//#include "shader_task.h"
#include "appContext.h"
#include "hud.h"

//---------------------------------------------------------------------
// メッセージ処理
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
                          void* pUserContext )
{
    UNREFERENCED_PARAMETER( pbNoFurtherProcessing );
	
	AppContext* pApp = AppContext::GetInstance();
	if (pApp == nullptr) return 0;

	pApp->OnMsgProc(hWnd, uMsg, wParam, lParam, pbNoFurtherProcessing);

    // カメラにも投げる
	pApp->GetCamera()->HandleMessages( hWnd, uMsg, wParam, lParam );

	switch(uMsg) {  
		case WM_COPYDATA:
		{
			const COPYDATASTRUCT * const pData = reinterpret_cast<COPYDATASTRUCT *>(lParam);
			const char* pParam = reinterpret_cast<const char*>(pData->lpData);
#if 0
			// パラメータツールからの情報
			if(	pParam[0] == SHADER_PARAM_ID[0] && pParam[1] == SHADER_PARAM_ID[1] &&
				pParam[2] == SHADER_PARAM_ID[2] && pParam[3] == SHADER_PARAM_ID[3]  )
			{
				SShaderParam param;
				memcpy( &param, pParam, sizeof( param ) );

				CShaderTask* pShaderTask = (CShaderTask*)CTaskMan::getInstance()->findTask("CShaderTask");
				_ASSERT( pShaderTask );
				if( param.m_Others.m_bShaderReLoadReq == true )
				{
					pShaderTask->shaderReLoadReq();
					param.m_Others.m_bShaderReLoadReq = false;
				}
				AppContext::GetInstance()->setShaderParam( &param );
			}
#endif
		}  
	break;  
	}  

    return 0;
}

//---------------------------------------------------------------------
// キーボード入力処理
void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
    UNREFERENCED_PARAMETER( bAltDown );

    if( bKeyDown )
    {
        switch( nChar )
        {
            case VK_F1:
//                g_bShowHelp = !g_bShowHelp; break;
            case 'T':
//                g_bShowText = !g_bShowText; break;
			case 'P':
//				g_bPause = !g_bPause;
				break;
        }
    }
}

//---------------------------------------------------------------------
// フレーム毎のアップデート
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	UNREFERENCED_PARAMETER( fTime );

	AppContext* pApp = AppContext::GetInstance();
	if (pApp == nullptr) return;
	pApp->Update(fElapsedTime);
}

//--------------------------------------------------------------------------------------
// デバイス設定
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
	// DX11以外は未対応
    assert( DXUT_D3D11_DEVICE == pDeviceSettings->ver );
	
    static bool s_bFirstTime = true;
    if( s_bFirstTime )
    {
        s_bFirstTime = false;
        if( pDeviceSettings->d3d11.DriverType == D3D_DRIVER_TYPE_REFERENCE )
        {
            DXUTDisplaySwitchingToREFWarning( pDeviceSettings->ver );
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------
// デバイスチェック
bool CALLBACK IsDeviceAcceptable( const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo,
                                       DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
    return true;
}

//--------------------------------------------------------------------------------------
// デバイス作成時処理
HRESULT CALLBACK OnCreateDevice( ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	AppContext* pApp = AppContext::GetInstance();
	_ASSERT(pApp);
	pApp->Init(pd3dDevice);

    return S_OK;
}

//--------------------------------------------------------------------------------------
// リサイズされたときの処理
HRESULT CALLBACK OnD3D11ResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,
                                         const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	AppContext* pApp = AppContext::GetInstance();
	if (pApp == nullptr) return S_OK;
	pApp->OnResizedSwapChain(pd3dDevice, pSwapChain, pBackBufferSurfaceDesc);

    return S_OK;
}

//--------------------------------------------------------------------------------------
// 開放されたときの処理
void CALLBACK OnD3D11ReleasingSwapChain( void* pUserContext )
{
	AppContext* pApp = AppContext::GetInstance();
	if (pApp == nullptr) return;
	pApp->OnReleasingSwapChain();
}

//--------------------------------------------------------------------------------------
// 終了時
void CALLBACK OnDestroyDevice( void* pUserContext )
{
}

//---------------------------------------------------------------------
// フレーム毎の描画
void CALLBACK OnFrameRender( ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime,
                                 float fElapsedTime, void* pUserContext )
{
	UNREFERENCED_PARAMETER(fElapsedTime);
	AppContext* pApp = AppContext::GetInstance();
	if (pApp == nullptr) return;
	pApp->Render();
}

//---------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
{
#if defined(DEBUG) | defined(_DEBUG)
	// メモリチェック
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	// コンテキストの作成
	AppContext::CreateInstance();

	// DXUTコールバックの設定
	DXUTSetCallbackMsgProc(MsgProc);
	DXUTSetCallbackKeyboard(OnKeyboard);
	DXUTSetCallbackFrameMove(OnFrameMove);
	DXUTSetCallbackDeviceChanging(ModifyDeviceSettings);

	DXUTSetCallbackD3D11DeviceAcceptable(IsDeviceAcceptable);
	DXUTSetCallbackD3D11DeviceCreated(OnCreateDevice);
	DXUTSetCallbackD3D11SwapChainResized(OnD3D11ResizedSwapChain);
	DXUTSetCallbackD3D11SwapChainReleasing(OnD3D11ReleasingSwapChain);
	DXUTSetCallbackD3D11DeviceDestroyed(OnDestroyDevice);
	DXUTSetCallbackD3D11FrameRender(OnFrameRender);

	// DXUT初期化
    DXUTInit( true, true, nullptr );
	DXUTSetMultimonSettings(false);
    DXUTSetCursorSettings( true, true );
    DXUTCreateWindow( L"application" );
	DXUTCreateDevice( D3D_FEATURE_LEVEL_11_0, true, WINDOW_W, WINDOW_H );

	// メインループ
	DXUTMainLoop();

	// コンテキストの破棄
	AppContext::DisposeInstance();

    return DXUTGetExitCode();
}

