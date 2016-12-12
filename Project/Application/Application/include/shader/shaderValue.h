/**
	@file shaderValue.h
	@brief シェーダパラメータの設定
*/

#ifndef _SHADER_VALUE_H_
#define _SHADER_VALUE_H_

class Shader;

/**
@brief シェーダパラメータクラス
*/
class ShaderValueBase
{
public:
	ShaderValueBase(Shader* shader);
	virtual ~ShaderValueBase(){};

	/**
	@brief シェーダパラメータの適用
	*/
	inline void Apply(){ if (_applyFunc) { _applyFunc(this); } }

	/**
	@brief 名前の取得
	*/
	inline const std::string& GetName() const { return _name; }

	/**
	@brief 適用関数の設定
	*/
	inline void SetApplyFunc(std::function<void(ShaderValueBase*)>& func) { _applyFunc = func; }

protected:
	std::function<void(ShaderValueBase*)>	_applyFunc;		//!< 適用関数
	std::string								_name;			//!< 名前
	Shader*									_shader;		//!< シェーダー
};

/**
	@brief コンスタントバッファのシェーダパラメータクラス
*/
class ShaderValueConstantBuffer : public ShaderValueBase
{
public:
	ShaderValueConstantBuffer(Shader* shader);
	virtual ~ShaderValueConstantBuffer(){};

	/**
		@brief パラメータの作成
		@param shader [in] Shaderデータ
		@param name [in] セマンティック名
		@param buff [in] パラメータ適用先バッファ
	*/
	void Create(const char* name, char* buff);

	/**
	@brief バッファへの適用
	*/
	template<class T>
	inline void SetBuffer(T& val){ memcpy_s(_buffer, sizeof(T), &val, sizeof(T)); }

public:
	// セマンティックごとの処理
	static void Projection(const ShaderValueBase* val);
	static void World(const ShaderValueBase* val);

protected:
	char*			_buffer;		//!< バッファ
};

/**
	@brief リソースのシェーダパラメータクラス
*/
class ShaderValueResources : public ShaderValueBase
{
public:
	ShaderValueResources(Shader* shader);
	virtual ~ShaderValueResources(){};

	/**
		@brief パラメータの作成
		@param shader [in] Shaderデータ
		@param name [in] セマンティック名
		@param bindPoint [in] バインドポイント
	*/
	void Create(const char* name, uint32_t bindPoint);

public:
	// セマンティックごとの処理

protected:
	uint32_t							_bindPoint;		//!< バインドポイント
};

#endif		// _SHADER_VALUE_H_