/**
@file jobManager.h
@brief ���s�����K��N���X
*/
#pragma once
#ifndef __JOB_MANAGER_H__
#define __JOB_MANAGER_H__

#include "framework/processManager.h"
#include "framework/process.h"
#include "framework/thread.h"
#include "framework/job.h"

/**
@brief	�W���u�Ǘ�
*/
class JobManager : public ProcessManagerBase
{
public:
	/**
	@brief �R���X�g���N�^
	*/
	JobManager();

	/**
	@brief �f�X�g���N�^
	*/
	virtual ~JobManager();

	/**
	@brief ���s
	*/
	virtual void Proc(void);

	/**
	@brief �ǉ�
	@param child [in] �ǉ�����v���Z�X
	@param parent [in] �e�Bnullptr�Ȃ烋�[�g�̉�
	*/
	void AddJob(Job* child, Job* parent = nullptr);

	/**
	@brief ����
	@param identifier [in] ���ʎq
	*/
	Job* FindJob(const char* identifier);

private:
	/**
	@brief �X�V�p�X���b�h
	*/
	class ProcThread : public ThreadRequestBase
	{
	public:
		ProcThread(Job* process) : ThreadRequestBase(), _process(process) {}
		virtual ~ProcThread(){};
		virtual void Execute(void) { _process->UpdateASync(); }

	private:
		Job*		_process;		//!< �v���Z�X�|�C���^
	};

private:
	std::vector<ProcThread*>	_threadList;	//!< �X�V�p�X���b�h�z��
	Job							_root;			//!< ���[�g�v���Z�X
};

#endif		//__JOB_MANAGER_H__

