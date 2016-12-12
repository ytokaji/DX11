/**
	@file shaderValue.h
	@brief �V�F�[�_�p�����[�^�̐ݒ�
*/

#ifndef _SHADER_VALUE_H_
#define _SHADER_VALUE_H_

class Shader;

/**
@brief �V�F�[�_�p�����[�^�N���X
*/
class ShaderValueBase
{
public:
	ShaderValueBase(Shader* shader);
	virtual ~ShaderValueBase(){};

	/**
	@brief �V�F�[�_�p�����[�^�̓K�p
	*/
	inline void Apply(){ if (_applyFunc) { _applyFunc(this); } }

	/**
	@brief ���O�̎擾
	*/
	inline const std::string& GetName() const { return _name; }

	/**
	@brief �K�p�֐��̐ݒ�
	*/
	inline void SetApplyFunc(std::function<void(ShaderValueBase*)>& func) { _applyFunc = func; }

protected:
	std::function<void(ShaderValueBase*)>	_applyFunc;		//!< �K�p�֐�
	std::string								_name;			//!< ���O
	Shader*									_shader;		//!< �V�F�[�_�[
};

/**
	@brief �R���X�^���g�o�b�t�@�̃V�F�[�_�p�����[�^�N���X
*/
class ShaderValueConstantBuffer : public ShaderValueBase
{
public:
	ShaderValueConstantBuffer(Shader* shader);
	virtual ~ShaderValueConstantBuffer(){};

	/**
		@brief �p�����[�^�̍쐬
		@param shader [in] Shader�f�[�^
		@param name [in] �Z�}���e�B�b�N��
		@param buff [in] �p�����[�^�K�p��o�b�t�@
	*/
	void Create(const char* name, char* buff);

	/**
	@brief �o�b�t�@�ւ̓K�p
	*/
	template<class T>
	inline void SetBuffer(T& val){ memcpy_s(_buffer, sizeof(T), &val, sizeof(T)); }

public:
	// �Z�}���e�B�b�N���Ƃ̏���
	static void Projection(const ShaderValueBase* val);
	static void World(const ShaderValueBase* val);

protected:
	char*			_buffer;		//!< �o�b�t�@
};

/**
	@brief ���\�[�X�̃V�F�[�_�p�����[�^�N���X
*/
class ShaderValueResources : public ShaderValueBase
{
public:
	ShaderValueResources(Shader* shader);
	virtual ~ShaderValueResources(){};

	/**
		@brief �p�����[�^�̍쐬
		@param shader [in] Shader�f�[�^
		@param name [in] �Z�}���e�B�b�N��
		@param bindPoint [in] �o�C���h�|�C���g
	*/
	void Create(const char* name, uint32_t bindPoint);

public:
	// �Z�}���e�B�b�N���Ƃ̏���

protected:
	uint32_t							_bindPoint;		//!< �o�C���h�|�C���g
};

#endif		// _SHADER_VALUE_H_