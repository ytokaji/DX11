/**
	@file object.h
	@brief �I�u�W�F�N�g���f���̊Ǘ��A�\��
*/

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "shader_task.h"
#include "shader_set_value.h"


/**
	@brief �I�u�W�F�N�g�N���X
	@note �I�u�W�F�N�g���f���̊Ǘ��A�\��
*/
class CObject
{
public:
	CObject(const wchar_t* i_pchFileName, CShaderTask::SHADER_INDEX shader);
	virtual ~CObject();

	/**
		@brief �X�V
	*/
	void Update( float i_fElapsd );

	/**
		@brief �`��
	*/
	void draw();

	/**
		@brief �f�o�C�X���Z�b�g���Ɏ��s
	*/
	void deviceReset();
	
	/**
		@brief �f�o�C�X���X�g���Ɏ��s
	*/
	void deviceLost();

	/**
		@brief �e��擾
	*/
	D3DXVECTOR3* getScl() { return &m_vScl; }
	D3DXVECTOR3* getRot() { return &m_vRot; }
	D3DXVECTOR3* getTrn() { return &m_vTrn; }

	/*
		@brief ���p�X�𕡐���т傤��
	*/
	void setPassDrawCount( unsigned int i_nCount ) { m_nPassDrawCount = i_nCount; }

private:
	void createMesh(const wchar_t* i_pchFileName);
	
private:
	std::vector< CShaderSetValueDelegate::CMaterialData >	m_aMaterial;	//!< �}�e���A��

	ID3DXMesh*					m_pMesh;			//!< ���f���f�[�^

	D3DXVECTOR3					m_vScl;				//!< �X�P�[��
	D3DXVECTOR3					m_vRot;				//!< ���[�e�[�V����
	D3DXVECTOR3					m_vTrn;				//!< �g�����X
	unsigned int				m_nPassDrawCount;	//!< ���p�X�𕡐���т傤��
	CShaderTask::SHADER_INDEX	m_eShader;			//!< �g�p�V�F�[�_�[
};


#endif		// _OBJECT_H_