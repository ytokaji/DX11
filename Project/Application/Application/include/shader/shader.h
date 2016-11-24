/**
	@file shader.h
	@brief シェーダファイル
*/

#ifndef _SHADER_H_
#define _SHADER_H_

#include "shader/shaderValue.h"

/**
	@brief シェーダ
*/
class Shader
{
public:
	/**
		@brief シェーダーのタイプ
	*/
	enum class eTYPE : uint8_t
	{
		VS = 0,
		PS,
		HULL,
		DoMAIN,
		GEOMETRY,
		COMPUTE,
		MAX
	};
	
public:
	/**
		@brief コンストラクタ
	*/
	Shader();
	
	/**
		@brief デストラクタ
	*/
	virtual ~Shader();

#if !_PRECOMPILE_SHADER_USE
	/**
	@brief	シェーダーのコンパイルと初期化
	@note	コンパイル前のものをロードして初期化
	@param fileName [in] ファイル名
	@param shaderProfile [in] プロファイル
	@param functionName [in] エントリポイント
	*/
	bool CompileInitShader(wchar_t* fileName, char*	shaderProfile, char* functionName, eTYPE type);
#endif

	/**
		@brief	シェーダーの初期化
		@note	コンパイル済みバッファからの初期化
		@param buff [in] コンパイル済みシェーダーバッファ
		@param size [in] バッファのサイズ
	*/
	bool InitShader(const void* buff, size_t size, eTYPE type);

	/**
	@brief シェーダパラメータの適用
	*/
	void Apply(DirectX::SimpleMath::Matrix* mat);

protected:	
	/**
		@brief シェーダの作成
	*/
	bool InitShaderVertex(const void* buff, size_t size);
	bool InitShaderPixel(const void* buff, size_t size);
	bool InitShaderHull(const void*, size_t){ return false; };
	bool InitShaderDomain(const void*, size_t){ return false; };
	bool InitShaderGeometry(const void*, size_t){ return false; };
	bool InitShaderCompute(const void*, size_t){ return false; };

	/**
		@brief シェーダーパラメータの設定
	*/
	void setupParameter(eTYPE type);

protected:
	/**
		@brief シェーダのデータ
	*/
	struct ShaderData
	{
		/// シェーダー
		union D3DShader {
			D3DShader() : _vertex(nullptr){}
			ID3D11VertexShader*		_vertex;
			ID3D11PixelShader*		_pixel;
			ID3D11HullShader*		_hull;
			ID3D11DomainShader*		_domain;
			ID3D11GeometryShader*	_geometry;
			ID3D11ComputeShader*	_compute;
		}	_shader;

		std::vector<ShaderValueConstantBuffer>	_constantValue;		//!< コンスタントバッファのシェーダパラメータクラス
		std::vector<ShaderValueResources>		_resourcesValue;	//!< リソースのシェーダパラメータクラス
		ID3D11ShaderReflection*					_reflection;		//!< リフレクション
		ID3D11Buffer*							_d3dBuffer;			//!< 定数バッファ
		char*									_buffer;			//!< バッファ
		unsigned int							_bufferSize;		//!< バッファサイズ

		ShaderData()
			: _shader()
			, _reflection(nullptr)
			, _d3dBuffer(nullptr)
			, _buffer(nullptr)
			, _bufferSize(0)
		{
		}
		~ShaderData()
		{
			SAFE_RELEASE(_shader._vertex);
			SAFE_RELEASE(_reflection);
			SAFE_RELEASE(_d3dBuffer);
			SAFE_DELETE_ARRAY(_buffer);
		}
	};

private:
	ShaderData					_shadarData[(int)eTYPE::MAX];		//!< シェーダーデータ
	ID3D11InputLayout*          _layout;							//!< インプットレイアウト
};


#endif		// _SHADER_H_d