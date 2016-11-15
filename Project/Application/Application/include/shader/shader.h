/**
	@file shader.h
	@brief シェーダファイル
*/

#ifndef _SHADER_H_
#define _SHADER_H_

#include "shader/shaderValue.h"

class CMaterial;

/**
	@brief シェーダ
*/
class CShader
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
	CShader();
	
	/**
		@brief デストラクタ
	*/
	virtual ~CShader();

#if !_PRECOMPILE_SHADER_USE
	/**
	@brief	シェーダーのコンパイルと初期化
	@note	コンパイル前のものをロードして初期化
	@param i_pFileName [in] ファイル名
	@param i_pShaderProfile [in] プロファイル
	@param i_pFunctionName [in] エントリポイント
	*/
	bool CompileInitShader(wchar_t* i_pFileName, char*	i_pShaderProfile, char*	i_pFunctionName, eTYPE i_eType);
#endif

	/**
		@brief	シェーダーの初期化
		@note	コンパイル済みバッファからの初期化
		@param i_pBuff [in] コンパイル済みシェーダーバッファ
		@param i_nSize [in] バッファのサイズ
	*/
	bool InitShader(const void* i_pBuff, size_t i_nSize, eTYPE i_eType);

	/**
		@brief シェーダ全体で共通のパラメータセット
	*/
	void PreRenderSetParam(D3DXMATRIX* i_pMat);
	
	/**
		@brief マテリアルごとに設定するパラメータ
	*/
	void RenderSetParam(CMaterial* i_pMate);

protected:	
	/**
		@brief シェーダの作成
	*/
	bool InitShaderVertex(const void* i_pBuff, size_t i_nSize);
	bool InitShaderPixel(const void* i_pBuff, size_t i_nSize);
	bool InitShaderHull(const void* i_pBuff, size_t i_nSize){ return false; };
	bool InitShaderDomain(const void* i_pBuff, size_t i_nSize){ return false; };
	bool InitShaderGeometry(const void* i_pBuff, size_t i_nSize){ return false; };
	bool InitShaderCompute(const void* i_pBuff, size_t i_nSize){ return false; };

	/**
		@brief シェーダーパラメータの設定
	*/
	void setupParameter(eTYPE i_eType);

protected:
	/**
		@brief シェーダのデータ
	*/
	struct SShaderData
	{
		/// シェーダー
		union D3DShader {
			D3DShader() : vertex(nullptr){}
			ID3D11VertexShader*		vertex;
			ID3D11PixelShader*		pixel;
			ID3D11HullShader*		hull;
			ID3D11DomainShader*		domain;
			ID3D11GeometryShader*	geometry;
			ID3D11ComputeShader*	compute;
		}	shader;
		
		/**
			@brief 変数パラメータ
		*/
		struct SVariableParam
		{
			std::string				str;				//!< 名前
			std::function<void()>	func;				//!< 適用関数
			char*					pBuff;				//!< 書き換え先
		};

		/**
			@brief リソースパラメータ
		*/
		struct SResourceParam
		{
			std::string				str;				//!< 名前
			std::function<void()>	func;				//!< 適用関数
			unsigned int			bindPoint;			//!< バインドポイント
		};

		std::vector<SVariableParam>	aVariableParam;		//!< 変数パラメータ配列
		std::vector<SResourceParam>	aResourceParam;		//!< リソースパラメータ配列
		ID3D11ShaderReflection*		reflection;			//!< リフレクション
		ID3D11Buffer*				d3dBuffer;			//!< 定数バッファ
		char*						pBuffer;			//!< バッファ
		unsigned int				nBufferSize;		//!< バッファサイズ

		SShaderData()
			: shader()
			, reflection(nullptr)
			, d3dBuffer(nullptr)
			, pBuffer(nullptr)
			, nBufferSize(0)
		{
		}
		~SShaderData()
		{
			SAFE_RELEASE(shader.vertex);
			SAFE_RELEASE(reflection);
			SAFE_RELEASE(d3dBuffer);
			SAFE_DELETE_ARRAY(pBuffer);
		}
	};

private:
	std::vector<std::unique_ptr<ShaderValue>>	_shaderValue;		//!< シェーダーパラメータ適用郡
	SShaderData					_shadarData[(int)eTYPE::MAX];		//!< シェーダーデータ
	ID3D11InputLayout*          _layout;							//!< インプットレイアウト

};


#endif		// _SHADER_H_d