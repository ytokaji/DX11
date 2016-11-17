/**
	@file shaderValue.h
	@brief シェーダパラメータの設定
*/

#ifndef _SHADER_VALUE_H_
#define _SHADER_VALUE_H_

class Shader;

/**
	@brief コンスタントバッファのシェーダパラメータクラス
*/
class ShaderValueConstantBuffer
{
public:
	ShaderValueConstantBuffer();
	virtual ~ShaderValueConstantBuffer(){};

	/**
		@brief パラメータの作成
		@param shader [in] Shaderデータ
		@param name [in] セマンティック名
		@param buff [in] パラメータ適用先バッファ
	*/
	void Create(const Shader* shader, const char* name, char* buff);

	/**
		@brief シェーダパラメータの適用
	*/
	inline void Apply(){ _applyFunc(this); }

public:
	// セマンティックごとの処理
	static void Projection(ShaderValueConstantBuffer* val);
	static void World(ShaderValueConstantBuffer* val);

protected:
	std::function<void(ShaderValueConstantBuffer*)>	_applyFunc;		//!< 適用関数
	std::string										_str;			//!< 名前
	const Shader*									_shader;		//!< シェーダ
	char*											_buffer;		//!< バッファ
};

/**
	@brief リソースのシェーダパラメータクラス
*/
class ShaderValueResources
{
public:
	ShaderValueResources();
	virtual ~ShaderValueResources(){};

	/**
		@brief パラメータの作成
		@param shader [in] Shaderデータ
		@param name [in] セマンティック名
		@param bindPoint [in] バインドポイント
	*/
	void Create(const Shader* shader, const char* name, uint32_t bindPoint);

	/**
		@brief シェーダパラメータの適用
	*/
	inline void Apply() { _applyFunc(this); }

public:
	// セマンティックごとの処理

protected:
	std::function<void(ShaderValueResources*)>	_applyFunc;		//!< 適用関数
	std::string									_str;			//!< 名前
	const Shader*								_shader;		//!< シェーダ
	uint32_t									_bindPoint;		//!< バインドポイント
};

#endif		// _SHADER_VALUE_H_