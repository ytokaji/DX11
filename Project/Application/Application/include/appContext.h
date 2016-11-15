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
class AppContext
{
public:
	typedef std::function<void(ID3D11Device*, IDXGISwapChain*, const DXGI_SURFACE_DESC*)>	ResizedSwapChainArg;
	typedef std::function<void()>															ReleasingSwapChainArg;
	typedef std::function<void(HWND, UINT, WPARAM, LPARAM, bool*)>							MsgProcChainArg;

public:
	/**
		@brief AppContextの作成
	*/
	static AppContext* CreateInstance();

	/**
		@brief AppContextの取得
	*/
	static AppContext* GetInstance();

	/**
		@brief AppContextの破棄
	*/
	static void DisposeInstance();
	
	/**
		@brief 初期化処理
	*/
	void Init(ID3D11Device* device);

	/**
		@brief 更新処理
	*/
	void Update(float elapsd);

	/**
		@brief 描画処理
	*/
	void Render();
		
	/**
		@brief DirectXデバイスの取得
	*/
	ID3D11Device* GetD3D11Device() const { return _device; }

	/**
		@briefイミディエートコンテキストの取得
	*/
	ID3D11DeviceContext* GetImmediateContext() { return _immediateContext; }

	/**
		@brief カメラのマトリックス操作
	*/
    const D3DXMATRIX*  GetWorldMatrix() const { return &_worldMatrix; }
    const D3DXMATRIX*  GetViewMatrix() const { return &_viewMatrix; }
    const D3DXMATRIX*  GetProjMatrix() const { return &_projMatrix; }
	void SetWorldMatrix(const D3DXMATRIX* mat) { _worldMatrix = *mat; }
	void SetViewMatrix(const D3DXMATRIX* mat) { _viewMatrix = *mat; }
	void SetProjMatrix(const D3DXMATRIX* mat) { _projMatrix = *mat; }
	
	/**
		@brief ディレクショナルライトの方向の操作
	*/
	const D3DXVECTOR3* GetDirectionalLightDir() const { return &_directionalLightDir; }
	void GetDirectionalLightDir(const D3DXVECTOR3* dir);

	/**
		@brief カメラの取得
	*/
	const CModelViewerCamera* GetCamera() const { return &_camera; }
	CModelViewerCamera* GetCamera() { return &_camera; }

	/**
		@brief 更新タイムの取得
	*/
	inline float GetElapsdTime() const { return _elapsd; }
	
	/**
		@brief シェーダパラメータの取得
	*/
	const SShaderParam* GetShaderParam() const { return &_shaderParam; }
	SShaderParam* GetShaderParam() { return &_shaderParam; }
	
	/**
		@brief シェーダパラメータの設定
	*/
	void SetShaderParam( const SShaderParam* param );
	
	/**
		@brief ジョブ管理クラスの取得
	*/
	CJobManager* GetJobManager() { return _job; }
	
	/**
		@brief 描画管理クラスの取得
	*/
	CRenderManager* GetRenderManager() { return _render; }
	
	/**
		@brief スレッドの中継管理クラスの取得
	*/
	CThreadChannel* GetThreadChannel() { return _threadChannel; }

	/**
		@brief リサイズ時に呼ぶ
	*/
	void OnResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc );

	/**
		@brief リリース時に呼ぶ
	*/
	void OnReleasingSwapChain();
	
	/**
		@brief メッセージ処理時時に呼ぶ
	*/
	void OnMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing );

	/**
		@brief リサイズ時に呼ばれるCB登録
	*/
	size_t AddResizedSwapChainCB(ResizedSwapChainArg);
	void DeleteResizedSwapChainCB(size_t handle);
	
	/**
		@brief リリース時に呼ばれるCB登録
	*/
	size_t AddReleasingSwapChainCB(ReleasingSwapChainArg);
	void DeleteReleasingSwapChainCB(size_t handle);
	
	/**
		@brief メッセージ処理時に呼ばれるCB登録
	*/
	size_t AddMsgProcCB(MsgProcChainArg);
	void DeleteMsgProcCB(size_t handle);
	
	/**
		@brief cpu数の取得
	*/
	unsigned int GetCpuCoreNum() const { return _cpuCoreNum; }

private:
	/**
		@brief コンストラクタ
	*/
	AppContext();
		
	/**
		@brief デストラクタ
	*/
	~AppContext();

private:
	static AppContext*					_instance;			//!< 自身へのインスタンスポインタ 
	
	// システムからのコールバック関数配列
	std::vector<ResizedSwapChainArg>	_resizedSwapChain;
	std::vector<ReleasingSwapChainArg>	_releasingSwapChain;
	std::vector<MsgProcChainArg>		_msgProc;

	CJobManager*						_job;					//!< ジョブ管理
	CRenderManager*						_render;				//!< 描画管理
	
	ID3D11Device*						_device;				//!< DirectXデバイス
	ID3D11DeviceContext*				_immediateContext;		//!< イミディエートのコンテキスト

	ShaderManager						_shaderManager;			//!< シェーダーマネージャ
	SShaderParam						_shaderParam;			//!< シェーダーパラメータ
	CModelViewerCamera					_camera;				//!< カメラ
	D3DXMATRIX							_worldMatrix;			//!< ワールドマトリックス
	D3DXMATRIX							_viewMatrix;			//!< ビューマトリックス
	D3DXMATRIX							_projMatrix;			//!< プロジェクションマトリックス
	D3DXVECTOR3							_directionalLightDir;	//!< ディレクショナルライト方向
	
    IDirect3DVertexBuffer9*				_vb;					//!< 頂点情報
    IDirect3DVertexDeclaration9*		_vertexDecl;			//!< 頂点データ要素

	CThreadChannel*						_threadChannel;			//!< スレッドの中継管理
	CStartJob*							_startJob;				//!< 開始ジョブ

	unsigned int						_cpuCoreNum;			//!< cpuのコア数
	float								_elapsd;				//!< １F間の時間
	bool								_isInit;				//!< 初期化フラグ
};

#endif // _APPLICATION_H_

