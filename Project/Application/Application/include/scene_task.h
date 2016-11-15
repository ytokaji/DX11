/**
	@file scene_task.h
	@brief �V�[���̏����A�\��
*/

#ifndef _SCENE_TASK_H_
#define _SCENE_TASK_H_

#include "task.h"
#include <D3D9.h>

class CSkyBox;
class CObject;
class CWaterSurFace;

/**
	@brief �V�[���^�X�N
	@note �V�[���Ǘ�
*/
class CSceneTask	: public CTask
{
public:
	CSceneTask();
	virtual ~CSceneTask();

	/**
		@brief �o�^����Ă���^�X�N�̍X�V���������s����
	*/
	virtual void run(void)
	{
		unsigned int n=getSubTask();
		_ASSERT( n<STATE_MAX );
		(this->*m_pRunFunc[n])();
	}

	/**
		@brief �o�^����Ă���^�X�N�̕`�揈�������s����
	*/
	virtual void draw(void)
	{
		unsigned int n=getSubTask();
		_ASSERT( n<STATE_MAX );
		(this->*m_pDrawFunc[n])();
	}

	/**
		@brief �f�o�C�X���Z�b�g���Ɏ��s
	*/
	virtual void deviceReset();
	
	/**
		@brief �f�o�C�X���X�g���Ɏ��s
	*/
	virtual void deviceLost();


private:
	enum
	{
		STATE_INIT,
		STATE_MAIN,

		STATE_MAX
	};

private:
	/// �X�e�[�g���Ƃ̏����֐�
	void _dummy(){};
	void _runInit();
	void _runMain();
	void _drawMain();

private:
	/// �����֐���`
    typedef void (CSceneTask::*ProcFunc)();

	static const ProcFunc	m_pRunFunc[];			//!< �X�V�������s
	static const ProcFunc	m_pDrawFunc[];			//!< �X�V�������s
	
	IDirect3DTexture9*		m_pReflectMap;		//!< ���˃e�N�X�`��
	IDirect3DSurface9*		m_pReflectSurf;		//!< ���˃T�[�t�F�[�X

	std::vector<CObject*>	m_pObject;		//!< �I�u�W�F�N�g
	CObject*				m_pFurObject;	//!< �I�u�W�F�N�g
	CObject*				m_pBG;			//!< �w�i
	CWaterSurFace*			m_pWater;		//!< ����
};


#endif		// _SCENE_TASK_H_