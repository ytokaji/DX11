/**
	@file shaderManager.h
	@brief �V�F�[�_�t�@�C���̊Ǘ�
*/

#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

class Shader;

/**
	@brief �V�F�[�_�t�@�C���̊Ǘ��^�X�N
	@note �g�p����V�F�[�_���܂Ƃ߂ď�����
*/
class ShaderManager
{
public:
	/**
		@brief �Ǘ�����Ă���V�F�[�_�[�̃C���f�b�N�X
	*/
	enum class SHADER_TYPE : uint8_t
	{
		GRID = 0,		// �O���b�h�\��

		MAX,			//�V�F�[�_�ő吔
	};

public:
	/**
		@brief �R���X�g���N�^�[
	*/
	ShaderManager();

	/**
		@brief �f�X�g���N�^�[
	*/
	virtual ~ShaderManager();
	
	/**
		@brief ����������
	*/
	void Init();

	/**
		@brief �V�F�[�_�̎擾
	*/
	Shader* GetShader(SHADER_TYPE shader);

	/**
		@brief �V�F�[�_�[�����[�h�v��
	*/
	void ShaderReLoadReq();

private:
	/// �V�F�[�_�[���[�h
	void ShaderLoad();

	/// �폜����
	void Destroy();

	/// �V�F�[�_�[�o�b�t�@�̎擾
	Shader* CreateShader(SHADER_TYPE shader);

private:
	/// �f���Q�[�g�o�^�֐�
	static void RegistDelegate_Grid(Shader* shader);
	/*
	void RegistDelegate_Bump();
	void RegistDelegate_Fur();
	void RegistDelegate_2D();
	void RegistDelegate_WATER();
	void RegistDelegate_GAUSSIAN();
	void RegistDelegate_BRIGHTNESS();
	void RegistDelegate_DOF();
	*/
private:
	static const std::function<void(Shader*)>		_registDelegate[];			//!< �f���Q�[�g�o�^�֐��|�C���^�z��
	std::array<Shader*, (uint8_t)SHADER_TYPE::MAX>	_shader;
};


#endif		// _SHADER_MANAGER_H_