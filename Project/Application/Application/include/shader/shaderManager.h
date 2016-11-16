/**
	@file shaderManager.h
	@brief シェーダファイルの管理
*/

#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

class Shader;

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
	enum class SHADER_TYPE : uint8_t
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
	void Init();

	/**
		@brief シェーダの取得
	*/
	Shader* GetShader(SHADER_TYPE shader);

	/**
		@brief シェーダーリロード要求
	*/
	void ShaderReLoadReq();

private:
	/// シェーダーロード
	void ShaderLoad();

	/// 削除処理
	void Destroy();

	/// シェーダーバッファの取得
	Shader* CreateShader(SHADER_TYPE shader);

private:
	/// デリゲート登録関数
	static void RegistDelegate_Grid(Shader* shader);
	/*
	void RegistDelegate_Bump();
	void RegistDelegate_Fur();
	void RegistDelegate_2D();
	void RegistDelegate_WATER();
	void RegistDelegate_GAUSSIAN();
	void RegistDelegate_BRIGHTNESS();
	void RegistDelegate_DOF();
	*/
private:
	static const std::function<void(Shader*)>		_registDelegate[];			//!< デリゲート登録関数ポインタ配列
	std::array<Shader*, (uint8_t)SHADER_TYPE::MAX>	_shader;
};


#endif		// _SHADER_MANAGER_H_