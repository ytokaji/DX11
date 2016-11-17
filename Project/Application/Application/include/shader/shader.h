/**
	@file shader.h
	@brief �V�F�[�_�t�@�C��
*/

#ifndef _SHADER_H_
#define _SHADER_H_

#include "shader/shaderValue.h"

/**
	@brief �V�F�[�_
*/
class Shader
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
	Shader();
	
	/**
		@brief �f�X�g���N�^
	*/
	virtual ~Shader();

#if !_PRECOMPILE_SHADER_USE
	/**
	@brief	�V�F�[�_�[�̃R���p�C���Ə�����
	@note	�R���p�C���O�̂��̂����[�h���ď�����
	@param fileName [in] �t�@�C����
	@param shaderProfile [in] �v���t�@�C��
	@param functionName [in] �G���g���|�C���g
	*/
	bool CompileInitShader(wchar_t* fileName, char*	shaderProfile, char* functionName, eTYPE type);
#endif

	/**
		@brief	�V�F�[�_�[�̏�����
		@note	�R���p�C���ς݃o�b�t�@����̏�����
		@param buff [in] �R���p�C���ς݃V�F�[�_�[�o�b�t�@
		@param size [in] �o�b�t�@�̃T�C�Y
	*/
	bool InitShader(const void* buff, size_t size, eTYPE type);

	/**
		@brief �V�F�[�_�S�̂ŋ��ʂ̃p�����[�^�Z�b�g
	*/
	void PreRenderSetParam(DirectX::SimpleMath::Matrix* mat);

protected:	
	/**
		@brief �V�F�[�_�̍쐬
	*/
	bool InitShaderVertex(const void* buff, size_t size);
	bool InitShaderPixel(const void* buff, size_t size);
	bool InitShaderHull(const void*, size_t){ return false; };
	bool InitShaderDomain(const void*, size_t){ return false; };
	bool InitShaderGeometry(const void*, size_t){ return false; };
	bool InitShaderCompute(const void*, size_t){ return false; };

	/**
		@brief �V�F�[�_�[�p�����[�^�̐ݒ�
	*/
	void setupParameter(eTYPE type);

protected:
	/**
		@brief �V�F�[�_�̃f�[�^
	*/
	struct ShaderData
	{
		/// �V�F�[�_�[
		union D3DShader {
			D3DShader() : _vertex(nullptr){}
			ID3D11VertexShader*		_vertex;
			ID3D11PixelShader*		_pixel;
			ID3D11HullShader*		_hull;
			ID3D11DomainShader*		_domain;
			ID3D11GeometryShader*	_geometry;
			ID3D11ComputeShader*	_compute;
		}	_shader;

		std::vector<ShaderValueConstantBuffer>	_constantValue;		//!< �R���X�^���g�o�b�t�@�̃V�F�[�_�p�����[�^�N���X
		std::vector<ShaderValueResources>		_resourcesValue;	//!< ���\�[�X�̃V�F�[�_�p�����[�^�N���X
		ID3D11ShaderReflection*					_reflection;		//!< ���t���N�V����
		ID3D11Buffer*							_d3dBuffer;			//!< �萔�o�b�t�@
		char*									_buffer;			//!< �o�b�t�@
		unsigned int							_bufferSize;		//!< �o�b�t�@�T�C�Y

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
	ShaderData					_shadarData[(int)eTYPE::MAX];		//!< �V�F�[�_�[�f�[�^
	ID3D11InputLayout*          _layout;							//!< �C���v�b�g���C�A�E�g
};


#endif		// _SHADER_H_d