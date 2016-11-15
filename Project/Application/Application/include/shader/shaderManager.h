/**
	@file shaderManager.h
	@brief シェーダファイルの管理
*/

#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

class CShader;

/**
	@brief シェーダファイルの管理タスク
	@note 使用するシェーダをまとめて初期化
*/
class ShaderManager
{
public:
	/**
		@brief 管理されているシェーダーのインデックス
	*/
	enum class eSHADER
	{
		GRID = 0,		// グリッド表示

		MAX,			//シェーダ最大数
	};

public:
	/**
		@brief コンストラクター
	*/
	ShaderManager();

	/**
		@brief デストラクター
	*/
	virtual ~ShaderManager();
	
	/**
		@brief 初期化処理
	*/
	void init();

	/**
		@brief シェーダの取得
	*/
	CShader* getShader(eSHADER i_eShader);

	/**
		@brief シェーダーリロード要求
	*/
	void shaderReLoadReq();

private:
	/// シェーダーロード
	void shaderLoad();

	/// 削除処理
	void destroy();

	/// シェーダーバッファの取得
	CShader* createShader(eSHADER i_eShader);

private:
	/// デリゲート登録関数
	void _registDelegate_Grid(CShader* i_pShader);
	/*
	void _registDelegate_Bump();
	void _registDelegate_Fur();
	void _registDelegate_2D();
	void _registDelegate_WATER();
	void _registDelegate_GAUSSIAN();
	void _registDelegate_BRIGHTNESS();
	void _registDelegate_DOF();
	*/
private:
	typedef void (ShaderManager::*RegistDelegateFunc)(CShader*);
	static const RegistDelegateFunc	m_pRegistDelegate[];			//!< デリゲート登録関数ポインタ配列

	std::array<CShader*, (int)eSHADER::MAX>	m_apShader;
};


#endif		// _SHADER_MANAGER_H_