/**
	@file shaderValue.h
	@brief シェーダパラメータの設定
*/

#ifndef _SHADER_VALUE_H_
#define _SHADER_VALUE_H_

class CMaterial;
class Shader;

/**
	@brief シェーダパラメータの設定の規定クラス
	@note インタフェース
*/
class ShaderValue
{
public:
	ShaderValue();
	virtual ~ShaderValue(){};

	/**
		@brief パラメータの作成
	*/
	size_t Create(Shader* shader, ID3D11ShaderReflectionVariable* variable);

	/**
		@brief シェーダパラメータの適用
	*/
	void Apply();

public:
	// セマンティックごとの処理
	static void Projection(ShaderValue* val);
	static void World(ShaderValue* val);

protected:
	std::function<void(ShaderValue*)>	_applyFunc;		//!< 適用関数
	Shader*								_shader;		//!< シェーダ
	uint32_t							_offset;		//!< オフセット値
	uint32_t							_textureSlot;	//!< テクスチャ用スロット
};

#if 0
/**
	@brief シェーダパラメータの設定クラス
	@note セマンティクスのパラメータの設定
*/
class CShaderValue_Semantic : public IShaderValue
{
public:
	CShaderValue_Semantic();
	virtual ~CShaderValue_Semantic();

	/**
		@brief シェーダ全体で共通のパラメータセット
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief パラメータの設定
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_hPorj;
	D3DXHANDLE				m_hWorld;
	D3DXHANDLE				m_hWorldView;
	D3DXHANDLE				m_hWorldViewPorj;
	D3DXHANDLE				m_hCameraPosition;
	D3DXHANDLE				m_hDirectionalLightDir;
	D3DXHANDLE				m_hTime;
	D3DXHANDLE				m_hAmbient;
	D3DXHANDLE				m_hDiffuse;
	D3DXHANDLE				m_hSpecular;
};

/**
	@brief ディフューズテクスチャの設定クラス
	@note シェーダパラメータの設定
*/
class CShaderValue_DiffuseTexture : public IShaderValue
{
public:
	CShaderValue_DiffuseTexture();
	virtual ~CShaderValue_DiffuseTexture();

	/**
		@brief シェーダ全体で共通のパラメータセット
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat){};

	/**
		@brief パラメータの設定
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_hDiffuseTexture;
};

/**
	@brief フレームバッファテクスチャの設定クラス
	@note シェーダパラメータの設定
*/
class CShaderValue_FrameBufferTexture : public IShaderValue
{
public:
	CShaderValue_FrameBufferTexture();
	virtual ~CShaderValue_FrameBufferTexture();

	/**
		@brief シェーダ全体で共通のパラメータセット
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief パラメータの設定
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_hFrameBufferTexture;
	D3DXHANDLE				m_hFrameBufferDepthTexture;
};

/**
	@brief 水面の設定クラス
	@note シェーダパラメータの設定
*/
class CShaderValue_WaterParam : public IShaderValue
{
public:
	CShaderValue_WaterParam();
	virtual ~CShaderValue_WaterParam();

	/**
		@brief シェーダ全体で共通のパラメータセット
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief パラメータの設定
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_h4Color;
	D3DXHANDLE				m_h3SpecularColor;
	D3DXHANDLE				m_h2RefrParams;
	D3DXHANDLE				m_h2ReflParams;
	D3DXHANDLE				m_h2SpecularPower;
	D3DXHANDLE				m_hReflBias;
	D3DXHANDLE				m_hFresnelPower;
	D3DXHANDLE				m_h2WaveOffset;
	D3DXHANDLE				m_h2FrameBufferSize;
	D3DXHANDLE				m_f3Light;

	float		m_pBumpOffsetUV[2];
};

/**
	@brief bumpの設定クラス
	@note シェーダパラメータの設定
*/
class CShaderValue_Bump : public IShaderValue
{
public:
	CShaderValue_Bump();
	virtual ~CShaderValue_Bump();

	/**
		@brief シェーダ全体で共通のパラメータセット
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief パラメータの設定
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_h2NormalMap;	
	D3DXHANDLE				m_hSpecularPower;	//!< スペキュラの範囲
	D3DXHANDLE				m_hSpecularRange;	//!< スペキュラの距離
	IDirect3DTexture9*		m_pBumpTex;			//!< ノーマルマップ
};

/**
	@brief furの設定クラス
	@note シェーダパラメータの設定
*/
class CShaderValue_Fur : public IShaderValue
{
public:
	CShaderValue_Fur();
	virtual ~CShaderValue_Fur();

	/**
		@brief シェーダ全体で共通のパラメータセット
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief パラメータの設定
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_h3furColor;
	D3DXHANDLE				m_hFurDistance;
	D3DXHANDLE				m_h2FurMap;	
	D3DXHANDLE				m_hCount;			//!< カウントハンドル
	IDirect3DTexture9*		m_pFurTex;			//!< ノーマルマップ
	unsigned int			m_nCount;
};

/**
	@brief gaussianの設定クラス
	@note シェーダパラメータの設定
*/
class CShaderValue_Gaussian : public IShaderValue
{
public:
	CShaderValue_Gaussian();
	virtual ~CShaderValue_Gaussian();

	/**
		@brief シェーダ全体で共通のパラメータセット
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief パラメータの設定
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_hfUvOffset;
	D3DXHANDLE				m_hfOffset;
	D3DXHANDLE				m_hfWindowRatio;
	D3DXHANDLE				m_hfWeight;

	float					m_fWeight[4];
};

/**
	@brief brightnessの設定クラス
	@note シェーダパラメータの設定
*/
class CShaderValue_Brightness : public IShaderValue
{
public:
	CShaderValue_Brightness();
	virtual ~CShaderValue_Brightness();

	/**
		@brief シェーダ全体で共通のパラメータセット
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief パラメータの設定
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_hfBrighness;
	D3DXHANDLE				m_hfWindowRatio;
};

/**
	@brief 被写界深度の設定クラス
	@note シェーダパラメータの設定
*/
class CShaderValue_Dof : public IShaderValue
{
public:
	CShaderValue_Dof();
	virtual ~CShaderValue_Dof();

	/**
		@brief シェーダ全体で共通のパラメータセット
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat, CMaterial* mate);

	/**
		@brief パラメータの設定
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_hfFocusDistance;
	D3DXHANDLE				m_hfFocusRange;
};
#endif

#endif		// _SHADER_VALUE_H_