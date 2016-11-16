/**
	@file shaderValue.h
	@brief �V�F�[�_�p�����[�^�̐ݒ�
*/

#ifndef _SHADER_VALUE_H_
#define _SHADER_VALUE_H_

class CMaterial;
class Shader;

/**
	@brief �V�F�[�_�p�����[�^�̐ݒ�̋K��N���X
	@note �C���^�t�F�[�X
*/
class ShaderValue
{
public:
	ShaderValue();
	virtual ~ShaderValue(){};

	/**
		@brief �p�����[�^�̍쐬
	*/
	size_t Create(Shader* shader, ID3D11ShaderReflectionVariable* variable);

	/**
		@brief �V�F�[�_�p�����[�^�̓K�p
	*/
	void Apply();

public:
	// �Z�}���e�B�b�N���Ƃ̏���
	static void Projection(ShaderValue* val);
	static void World(ShaderValue* val);

protected:
	std::function<void(ShaderValue*)>	_applyFunc;		//!< �K�p�֐�
	Shader*								_shader;		//!< �V�F�[�_
	uint32_t							_offset;		//!< �I�t�Z�b�g�l
	uint32_t							_textureSlot;	//!< �e�N�X�`���p�X���b�g
};

#if 0
/**
	@brief �V�F�[�_�p�����[�^�̐ݒ�N���X
	@note �Z�}���e�B�N�X�̃p�����[�^�̐ݒ�
*/
class CShaderValue_Semantic : public IShaderValue
{
public:
	CShaderValue_Semantic();
	virtual ~CShaderValue_Semantic();

	/**
		@brief �V�F�[�_�S�̂ŋ��ʂ̃p�����[�^�Z�b�g
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief �p�����[�^�̐ݒ�
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
	@brief �f�B�t���[�Y�e�N�X�`���̐ݒ�N���X
	@note �V�F�[�_�p�����[�^�̐ݒ�
*/
class CShaderValue_DiffuseTexture : public IShaderValue
{
public:
	CShaderValue_DiffuseTexture();
	virtual ~CShaderValue_DiffuseTexture();

	/**
		@brief �V�F�[�_�S�̂ŋ��ʂ̃p�����[�^�Z�b�g
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat){};

	/**
		@brief �p�����[�^�̐ݒ�
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_hDiffuseTexture;
};

/**
	@brief �t���[���o�b�t�@�e�N�X�`���̐ݒ�N���X
	@note �V�F�[�_�p�����[�^�̐ݒ�
*/
class CShaderValue_FrameBufferTexture : public IShaderValue
{
public:
	CShaderValue_FrameBufferTexture();
	virtual ~CShaderValue_FrameBufferTexture();

	/**
		@brief �V�F�[�_�S�̂ŋ��ʂ̃p�����[�^�Z�b�g
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief �p�����[�^�̐ݒ�
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_hFrameBufferTexture;
	D3DXHANDLE				m_hFrameBufferDepthTexture;
};

/**
	@brief ���ʂ̐ݒ�N���X
	@note �V�F�[�_�p�����[�^�̐ݒ�
*/
class CShaderValue_WaterParam : public IShaderValue
{
public:
	CShaderValue_WaterParam();
	virtual ~CShaderValue_WaterParam();

	/**
		@brief �V�F�[�_�S�̂ŋ��ʂ̃p�����[�^�Z�b�g
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief �p�����[�^�̐ݒ�
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
	@brief bump�̐ݒ�N���X
	@note �V�F�[�_�p�����[�^�̐ݒ�
*/
class CShaderValue_Bump : public IShaderValue
{
public:
	CShaderValue_Bump();
	virtual ~CShaderValue_Bump();

	/**
		@brief �V�F�[�_�S�̂ŋ��ʂ̃p�����[�^�Z�b�g
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief �p�����[�^�̐ݒ�
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_h2NormalMap;	
	D3DXHANDLE				m_hSpecularPower;	//!< �X�y�L�����͈̔�
	D3DXHANDLE				m_hSpecularRange;	//!< �X�y�L�����̋���
	IDirect3DTexture9*		m_pBumpTex;			//!< �m�[�}���}�b�v
};

/**
	@brief fur�̐ݒ�N���X
	@note �V�F�[�_�p�����[�^�̐ݒ�
*/
class CShaderValue_Fur : public IShaderValue
{
public:
	CShaderValue_Fur();
	virtual ~CShaderValue_Fur();

	/**
		@brief �V�F�[�_�S�̂ŋ��ʂ̃p�����[�^�Z�b�g
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief �p�����[�^�̐ݒ�
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_h3furColor;
	D3DXHANDLE				m_hFurDistance;
	D3DXHANDLE				m_h2FurMap;	
	D3DXHANDLE				m_hCount;			//!< �J�E���g�n���h��
	IDirect3DTexture9*		m_pFurTex;			//!< �m�[�}���}�b�v
	unsigned int			m_nCount;
};

/**
	@brief gaussian�̐ݒ�N���X
	@note �V�F�[�_�p�����[�^�̐ݒ�
*/
class CShaderValue_Gaussian : public IShaderValue
{
public:
	CShaderValue_Gaussian();
	virtual ~CShaderValue_Gaussian();

	/**
		@brief �V�F�[�_�S�̂ŋ��ʂ̃p�����[�^�Z�b�g
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief �p�����[�^�̐ݒ�
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
	@brief brightness�̐ݒ�N���X
	@note �V�F�[�_�p�����[�^�̐ݒ�
*/
class CShaderValue_Brightness : public IShaderValue
{
public:
	CShaderValue_Brightness();
	virtual ~CShaderValue_Brightness();

	/**
		@brief �V�F�[�_�S�̂ŋ��ʂ̃p�����[�^�Z�b�g
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat);

	/**
		@brief �p�����[�^�̐ݒ�
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_hfBrighness;
	D3DXHANDLE				m_hfWindowRatio;
};

/**
	@brief ��ʊE�[�x�̐ݒ�N���X
	@note �V�F�[�_�p�����[�^�̐ݒ�
*/
class CShaderValue_Dof : public IShaderValue
{
public:
	CShaderValue_Dof();
	virtual ~CShaderValue_Dof();

	/**
		@brief �V�F�[�_�S�̂ŋ��ʂ̃p�����[�^�Z�b�g
	*/
	virtual void SetValue(D3DXMATRIX& i_rMat, CMaterial* mate);

	/**
		@brief �p�����[�^�̐ݒ�
	*/
	virtual void attach(Shader* i_pParam);

private:
	D3DXHANDLE				m_hfFocusDistance;
	D3DXHANDLE				m_hfFocusRange;
};
#endif

#endif		// _SHADER_VALUE_H_