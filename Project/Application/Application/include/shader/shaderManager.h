/**
	@file shaderManager.h
	@brief �V�F�[�_�t�@�C���̊Ǘ�
*/

#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

class CShader;

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
	enum class eSHADER
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
	void init();

	/**
		@brief �V�F�[�_�̎擾
	*/
	CShader* getShader(eSHADER i_eShader);

	/**
		@brief �V�F�[�_�[�����[�h�v��
	*/
	void shaderReLoadReq();

private:
	/// �V�F�[�_�[���[�h
	void shaderLoad();

	/// �폜����
	void destroy();

	/// �V�F�[�_�[�o�b�t�@�̎擾
	CShader* createShader(eSHADER i_eShader);

private:
	/// �f���Q�[�g�o�^�֐�
	void _registDelegate_Grid(CShader* i_pShader);
	/*
	void _registDelegate_Bump();
	void _registDelegate_Fur();
	void _registDelegate_2D();
	void _registDelegate_WATER();
	void _registDelegate_GAUSSIAN();
	void _registDelegate_BRIGHTNESS();
	void _registDelegate_DOF();
	*/
private:
	typedef void (ShaderManager::*RegistDelegateFunc)(CShader*);
	static const RegistDelegateFunc	m_pRegistDelegate[];			//!< �f���Q�[�g�o�^�֐��|�C���^�z��

	std::array<CShader*, (int)eSHADER::MAX>	m_apShader;
};


#endif		// _SHADER_MANAGER_H_