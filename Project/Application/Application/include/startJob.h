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
class StartJob	: public Job
{
public:
	StartJob();
	~StartJob();
	
	/**
		@brief	�X�V����
		@note	�e�q�K�w�ƃv���C�I���e�B���l�����������Ŏ��s
	*/
	virtual void Update(void);

private:
	enum class STATE : uint8_t
	{
		STATE_INIT		= 0
	,	STATE_RUN
	};

private:
	CHud*		_hub;
	STATE		_state;
};


#endif		// _START_JOB_H_