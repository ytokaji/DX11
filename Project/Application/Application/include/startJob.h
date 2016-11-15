/**
	@file startJob.h
	@brief �J�n���̏����W���u
*/

#pragma once
#ifndef _START_JOB_H_
#define _START_JOB_H_

#include "framework/job.h"

class CHud;

/**
	@brief �J�n���̏����W���u
*/
class CStartJob	: public CJob
{
public:
	CStartJob();
	~CStartJob();
	
	/**
		@brief	�X�V����
		@note	�e�q�K�w�ƃv���C�I���e�B���l�����������Ŏ��s
	*/
	virtual void update(void);

private:
	enum
	{
		STATE_INIT		= 0
	,	STATE_RUN
	};

private:
	CHud*			m_pHub;
	unsigned int	m_nState;
};


#endif		// _START_JOB_H_