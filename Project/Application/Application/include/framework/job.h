/**
	@file job.h
	@brief ���s�����K��N���X
*/
#pragma once
#ifndef __JOB_H__
#define __JOB_H__

#include "framework/process.h"

/**
	@class CJob
	@brief �������s
*/
class CJob : public CProcess < CJob, JOB_PRIORITY >
{
public:
	/**
		@brief �R���X�g���N�^�[
		@param pszid [in] ���ʎq
		@param i_fPre [in] ���O�����t�@���N�^
		@param i_fMain [in] �����t�@���N�^
		@param i_fPost [in] ���㏈���t�@���N�^
		@param nPriority [in] �v���C�I���e�B�[
	*/
	CJob(const char* i_pszid, JOB_PRIORITY i_ePriority = JOB_PRIORITY::DEFAULT)
		: CJob(i_pszid, []{}, []{}, i_ePriority)
	{
	}
	CJob(const char* i_pszid,
			std::function<void()> i_fUpdate, std::function<void()> i_fUpdateASync
			, JOB_PRIORITY i_ePriority = JOB_PRIORITY::DEFAULT)
		: CProcess<CJob, JOB_PRIORITY>(i_pszid, i_ePriority)
		, m_fUpdate(i_fUpdate)
		, m_fUpdateASync(i_fUpdateASync)
	{
	}

	/**
		@brief �f�X�g���N�^�[
		*/
	virtual ~CJob()
	{
	}
	
	/**
		@brief	�X�V����
		@note	�e�q�K�w�ƃv���C�I���e�B���l�����������Ŏ��s
	*/
	virtual void update(void)	{m_fUpdate();}

	/**
		@brief	�񓯊��X�V����
		@note	���s���A�񓯊��Ŏ��s
				CJob�S�Ă�update�J�n����I���܂ł̊ԂɎ��s�����̂ŃX���b�h�Z�[�t�ɂ���K�v������
	*/
	virtual void updateASync(void)	{ m_fUpdateASync(); }

private:
	const std::function<void()>		m_fUpdate;				//!< �X�V����
	const std::function<void()>		m_fUpdateASync;			//!< �񓯊��X�V����
};

#endif		//__JOB_H__

