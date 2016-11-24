/**
@file job.h
@brief ���s�����K��N���X
*/
#pragma once
#ifndef __JOB_H__
#define __JOB_H__

#include "framework/processManager.h"
#include "framework/process.h"
#include "framework/thread.h"

/**
@class Job
@brief �������s
*/
class Job : public Process < Job, JOB_PRIORITY >
{
public:
	/**
	@brief �R���X�g���N�^�[
	@param pszid [in] ���ʎq
	@param i_fPre [in] ���O�����t�@���N�^
	@param i_fMain [in] �����t�@���N�^
	@param post [in] ���㏈���t�@���N�^
	@param nPriority [in] �v���C�I���e�B�[
	*/
	Job(const char* id, JOB_PRIORITY priority = JOB_PRIORITY::DEFAULT)
		: Job(id, []{}, []{}, priority)
	{
	}
	Job(const char* id
		, std::function<void()> update
		, std::function<void()> updateASync
		, JOB_PRIORITY priority = JOB_PRIORITY::DEFAULT)
		: Process<Job, JOB_PRIORITY>(id, priority)
		, update(update)
		, updateASync(updateASync)
	{
	}

	/**
	@brief �f�X�g���N�^�[
	*/
	virtual ~Job(){}

	/**
	@brief	�X�V����
	@note	�e�q�K�w�ƃv���C�I���e�B���l�����������Ŏ��s
	*/
	virtual void Update(void)	{ update(); }

	/**
	@brief	�񓯊��X�V����
	@note	���s���A�񓯊��Ŏ��s
	Job�S�Ă�Update�J�n����I���܂ł̊ԂɎ��s�����̂ŃX���b�h�Z�[�t�ɂ���K�v������
	*/
	virtual void UpdateASync(void)	{ updateASync(); }

private:
	const std::function<void()>		update;				//!< �X�V����
	const std::function<void()>		updateASync;		//!< �񓯊��X�V����
};

#endif		//__JOB_H__

