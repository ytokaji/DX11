/**
	@file appContext.h
	@brief アプリケーション管理
*/
#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Core/DXUT.h"
#include "Optional/DXUTcamera.h"
#include "shader_param.h"
#include "shader/shaderManager.h"


class CJobManager;
class CRenderManager;
class CStartJob;
class CThreadChannel;

/**
	@brief アプリケーション管理クラス
	@note シングルトンにて管理
*/
class CAppContext
{
public:
	typedef std::function<void(ID3D11Device*, IDXGISwapChain*, const DXGI_SURFACE_DESC*)>	ResizedSwapChainArg;
	typedef std::function<void()>															ReleasingSwapChainArg;
	typedef std::function<void(HWND, UINT, WPARAM, LPARAM, bool*)>							MsgProcChainArg;

public:
	/**
		@brief CAppContextの作成
	*/
	static CAppContext* createInstance();

	/**
		@brief CAppContextの取得
	*/
	static CAppContext* getInstance();

	/**
		@brief CAppContextの破棄
	*/
	static void disposeInstance();
	
	/**
		@brief 初期化処理
	*/
	void init(ID3D11Device* i_pDevice);

	/**
		@brief 更新処理
	*/
	void update(float i_fElapsd);

	/**
		@brief 描画処理
	*/
	void render();
		
	/**
		@brief DirectXデバイスの取得
	*/
	ID3D11Device* getD3D11Device() const { return m_pd3dDevice; }

	/**
		@briefイミディエートコンテキストの取得
	*/
	ID3D11DeviceContext* getImmediateContext() { return m_pImmediateContext; }

#if 0
	/**
		@brief フレームバッファの取得
		@note draw()間のみ有効な値が帰る
	*/
	IDirect3DTexture9* getFrameBuffer() { return m_pFrameBuffrerTex; }
	IDirect3DTexture9* getDepthBuffer() { return m_pDepthBufferTex; }
#endif
	/**
		@brief カメラのマトリックス操作
	*/
    const D3DXMATRIX*  getWorldMatrix() const { return &m_mWorld; }
    const D3DXMATRIX*  getViewMatrix() const { return &m_mView; }
    const D3DXMATRIX*  getProjMatrix() const { return &m_mProj; }
	void setWorldMatrix(const D3DXMATRIX* i_pMat) { m_mWorld = *i_pMat; }
	void setViewMatrix(const D3DXMATRIX* i_pMat) { m_mView = *i_pMat; }
    void setProjMatrix(const D3DXMATRIX* i_pMat) { m_mProj = *i_pMat; }
	
	/**
		@brief ディレクショナルライトの方向の操作
	*/
	const D3DXVECTOR3* getDirectionalLightDir() const { return &m_vDirectionalLightDir; }
	void getDirectionalLightDir(const D3DXVECTOR3* i_pDir);

	/**
		@brief カメラの取得
	*/
	const CModelViewerCamera* getCamera() const { return &m_Camera; }
	CModelViewerCamera* getCamera() { return &m_Camera; }

	/**
		@brief 更新タイムの取得
	*/
	inline float getElapsdTime() const { return m_fElapsd; }
	
	/**
		@brief シェーダパラメータの取得
	*/
	const SShaderParam* getShaderParam() const { return &m_ShaderParam; }
	SShaderParam* getShaderParam() { return &m_ShaderParam; }
	
	/**
		@brief シェーダパラメータの設定
	*/
	void setShaderParam( const SShaderParam* i_pParam );
	
	/**
		@brief ジョブ管理クラスの取得
	*/
	CJobManager* getJobManager() { return m_pJob; }
	
	/**
		@brief 描画管理クラスの取得
	*/
	CRenderManager* getRenderManager() { return m_pRender; }
	
	/**
		@brief スレッドの中継管理クラスの取得
	*/
	CThreadChannel* getThreadChannel() { return m_pThreadChannel; }

	/**
		@brief リサイズ時に呼ぶ
	*/
	void onResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc );

	/**
		@brief リリース時に呼ぶ
	*/
	void onReleasingSwapChain();
	
	/**
		@brief メッセージ処理時時に呼ぶ
	*/
	void onMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing );

	/**
		@brief リサイズ時に呼ばれるCB登録
	*/
	size_t addResizedSwapChainCB(ResizedSwapChainArg);
	void deleteResizedSwapChainCB(size_t i_nHandle);
	
	/**
		@brief リリース時に呼ばれるCB登録
	*/
	size_t addReleasingSwapChainCB(ReleasingSwapChainArg);
	void deleteReleasingSwapChainCB(size_t i_nHandle);
	
	/**
		@brief メッセージ処理時に呼ばれるCB登録
	*/
	size_t addMsgProcCB(MsgProcChainArg);
	void deleteMsgProcCB(size_t i_nHandle);
	
	/**
		@brief メッセージ処理時に呼ばれるCB登録
	*/
	unsigned int getCpuCoreNum() const { return m_nCpuCoreNum; }

private:
	/**
		@brief コンストラクタ
	*/
	CAppContext();
		
	/**
		@brief デストラクタ
	*/
	~CAppContext();

private:
	static CAppContext*					m_pInstance;			//!< 自身へのインスタンスポインタ 
	
	// システムからのコールバック関数配列
	std::vector<ResizedSwapChainArg>	m_fResizedSwapChain;
	std::vector<ReleasingSwapChainArg>	m_fReleasingSwapChain;
	std::vector<MsgProcChainArg>		m_fMsgProc;

	CJobManager*						m_pJob;					//!< ジョブ管理
	CRenderManager*						m_pRender;				//!< 描画管理
	
	ID3D11Device*						m_pd3dDevice;			//!< DirectXデバイス
	ID3D11DeviceContext*				m_pImmediateContext;	//!< イミディエートのコンテキスト

	ShaderManager						m_ShaderManager;
	SShaderParam						m_ShaderParam;
	CModelViewerCamera					m_Camera;
	D3DXMATRIX							m_mWorld;
	D3DXMATRIX							m_mView;
	D3DXMATRIX							m_mProj;
	D3DXVECTOR3							m_vDirectionalLightDir;
	
    IDirect3DVertexBuffer9*				m_pVB;					//!< 頂点情報
    IDirect3DVertexDeclaration9*		m_pVertexDecl;			//!< 頂点データ要素
	
	IDirect3DTexture9*					m_pFrameBuffrerTex;		//!< フレームバッファテクスチャ
	IDirect3DSurface9*					m_pFrameBuffrerSurf;	//!< フレームバッファサーフェース
	IDirect3DTexture9*					m_pDepthBufferTex;		//!< 深度バッファテクスチャ
	IDirect3DSurface9*					m_pDepthBufferSurf;		//!< 深度バッファサーフェース

	CThreadChannel*						m_pThreadChannel;		//!< スレッドの中継管理
	CStartJob*							m_pStartJob;			//!< 開始ジョブ

	unsigned int						m_nCpuCoreNum;			//!< cpuのコア数
	float								m_fElapsd;				//!< １F間の時間
	bool								m_bIsInit;				//!< 初期化フラグ
};

#endif // _APPLICATION_H_

