/**
	@file shader.h
	@brief �V�F�[�_�t�@�C��
*/

#ifndef _SHADER_H_
#define _SHADER_H_

#include "shader/shaderValue.h"

class CMaterial;

/**
	@brief �V�F�[�_
*/
class CShader
{
public:
	/**
		@brief �V�F�[�_�[�̃^�C�v
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
		@brief �R���X�g���N�^
	*/
	CShader();
	
	/**
		@brief �f�X�g���N�^
	*/
	virtual ~CShader();

#if !_PRECOMPILE_SHADER_USE
	/**
	@brief	�V�F�[�_�[�̃R���p�C���Ə�����
	@note	�R���p�C���O�̂��̂����[�h���ď�����
	@param i_pFileName [in] �t�@�C����
	@param i_pShaderProfile [in] �v���t�@�C��
	@param i_pFunctionName [in] �G���g���|�C���g
	*/
	bool CompileInitShader(wchar_t* i_pFileName, char*	i_pShaderProfile, char*	i_pFunctionName, eTYPE i_eType);
#endif

	/**
		@brief	�V�F�[�_�[�̏�����
		@note	�R���p�C���ς݃o�b�t�@����̏�����
		@param i_pBuff [in] �R���p�C���ς݃V�F�[�_�[�o�b�t�@
		@param i_nSize [in] �o�b�t�@�̃T�C�Y
	*/
	bool InitShader(const void* i_pBuff, size_t i_nSize, eTYPE i_eType);

	/**
		@brief �V�F�[�_�S�̂ŋ��ʂ̃p�����[�^�Z�b�g
	*/
	void PreRenderSetParam(D3DXMATRIX* i_pMat);
	
	/**
		@brief �}�e���A�����Ƃɐݒ肷��p�����[�^
	*/
	void RenderSetParam(CMaterial* i_pMate);

protected:	
	/**
		@brief �V�F�[�_�̍쐬
	*/
	bool InitShaderVertex(const void* i_pBuff, size_t i_nSize);
	bool InitShaderPixel(const void* i_pBuff, size_t i_nSize);
	bool InitShaderHull(const void* i_pBuff, size_t i_nSize){ return false; };
	bool InitShaderDomain(const void* i_pBuff, size_t i_nSize){ return false; };
	bool InitShaderGeometry(const void* i_pBuff, size_t i_nSize){ return false; };
	bool InitShaderCompute(const void* i_pBuff, size_t i_nSize){ return false; };

	/**
		@brief �V�F�[�_�[�p�����[�^�̐ݒ�
	*/
	void setupParameter(eTYPE i_eType);

protected:
	/**
		@brief �V�F�[�_�̃f�[�^
	*/
	struct SShaderData
	{
		/// �V�F�[�_�[
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
			@brief �ϐ��p�����[�^
		*/
		struct SVariableParam
		{
			std::string				str;				//!< ���O
			std::function<void()>	func;				//!< �K�p�֐�
			char*					pBuff;				//!< ����������
		};

		/**
			@brief ���\�[�X�p�����[�^
		*/
		struct SResourceParam
		{
			std::string				str;				//!< ���O
			std::function<void()>	func;				//!< �K�p�֐�
			unsigned int			bindPoint;			//!< �o�C���h�|�C���g
		};

		std::vector<SVariableParam>	aVariableParam;		//!< �ϐ��p�����[�^�z��
		std::vector<SResourceParam>	aResourceParam;		//!< ���\�[�X�p�����[�^�z��
		ID3D11ShaderReflection*		reflection;			//!< ���t���N�V����
		ID3D11Buffer*				d3dBuffer;			//!< �萔�o�b�t�@
		char*						pBuffer;			//!< �o�b�t�@
		unsigned int				nBufferSize;		//!< �o�b�t�@�T�C�Y

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
	std::vector<std::unique_ptr<ShaderValue>>	_shaderValue;		//!< �V�F�[�_�[�p�����[�^�K�p�S
	SShaderData					_shadarData[(int)eTYPE::MAX];		//!< �V�F�[�_�[�f�[�^
	ID3D11InputLayout*          _layout;							//!< �C���v�b�g���C�A�E�g

};


#endif		// _SHADER_H_d