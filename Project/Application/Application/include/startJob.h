/**
	@file startJob.h
	@brief 開始時の初期ジョブ
*/

#pragma once
#ifndef _START_JOB_H_
#define _START_JOB_H_

#include "framework/job.h"

class CHud;

/**
	@brief 開始時の初期ジョブ
*/
class CStartJob	: public CJob
{
public:
	CStartJob();
	~CStartJob();
	
	/**
		@brief	更新処理
		@note	親子階層とプライオリティを考慮した同期で実行
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