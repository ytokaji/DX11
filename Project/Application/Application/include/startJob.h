/**
	@file startJob.h
	@brief 開始時の初期ジョブ
*/

#pragma once
#ifndef _START_JOB_H_
#define _START_JOB_H_

#include "framework/job.h"

class Hud;
class Grid;

/**
	@brief 開始時の初期ジョブ
*/
class StartJob	: public Job
{
public:
	StartJob();
	~StartJob();
	
	/**
		@brief	更新処理
		@note	親子階層とプライオリティを考慮した同期で実行
	*/
	virtual void Update(void);

private:
	enum class STATE : uint8_t
	{
		INIT		= 0
	,	RUN
	};

private:
	STATE					_state;
	std::unique_ptr<Hud>	_hub;
	std::unique_ptr<Grid>	_grid;
};


#endif		// _START_JOB_H_