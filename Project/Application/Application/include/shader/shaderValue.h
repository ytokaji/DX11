/**
	@file shaderValue.h
	@brief �V�F�[�_�p�����[�^�̐ݒ�
*/

#ifndef _SHADER_VALUE_H_
#define _SHADER_VALUE_H_

class Shader;

/**
	@brief �R���X�^���g�o�b�t�@�̃V�F�[�_�p�����[�^�N���X
*/
class ShaderValueConstantBuffer
{
public:
	ShaderValueConstantBuffer();
	virtual ~ShaderValueConstantBuffer(){};

	/**
		@brief �p�����[�^�̍쐬
		@param shader [in] Shader�f�[�^
		@param name [in] �Z�}���e�B�b�N��
		@param buff [in] �p�����[�^�K�p��o�b�t�@
	*/
	void Create(const Shader* shader, const char* name, char* buff);

	/**
		@brief �V�F�[�_�p�����[�^�̓K�p
	*/
	inline void Apply(){ _applyFunc(this); }

public:
	// �Z�}���e�B�b�N���Ƃ̏���
	static void Projection(ShaderValueConstantBuffer* val);
	static void World(ShaderValueConstantBuffer* val);

protected:
	std::function<void(ShaderValueConstantBuffer*)>	_applyFunc;		//!< �K�p�֐�
	std::string										_str;			//!< ���O
	const Shader*									_shader;		//!< �V�F�[�_
	char*											_buffer;		//!< �o�b�t�@
};

/**
	@brief ���\�[�X�̃V�F�[�_�p�����[�^�N���X
*/
class ShaderValueResources
{
public:
	ShaderValueResources();
	virtual ~ShaderValueResources(){};

	/**
		@brief �p�����[�^�̍쐬
		@param shader [in] Shader�f�[�^
		@param name [in] �Z�}���e�B�b�N��
		@param bindPoint [in] �o�C���h�|�C���g
	*/
	void Create(const Shader* shader, const char* name, uint32_t bindPoint);

	/**
		@brief �V�F�[�_�p�����[�^�̓K�p
	*/
	inline void Apply() { _applyFunc(this); }

public:
	// �Z�}���e�B�b�N���Ƃ̏���

protected:
	std::function<void(ShaderValueResources*)>	_applyFunc;		//!< �K�p�֐�
	std::string									_str;			//!< ���O
	const Shader*								_shader;		//!< �V�F�[�_
	uint32_t									_bindPoint;		//!< �o�C���h�|�C���g
};

#endif		// _SHADER_VALUE_H_