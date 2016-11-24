/**
@file job.h
@brief 実行処理規定クラス
*/
#pragma once
#ifndef __JOB_H__
#define __JOB_H__

#include "framework/processManager.h"
#include "framework/process.h"
#include "framework/thread.h"

/**
@class Job
@brief 処理実行
*/
class Job : public Process < Job, JOB_PRIORITY >
{
public:
	/**
	@brief コンストラクター
	@param pszid [in] 識別子
	@param i_fPre [in] 事前処理ファンクタ
	@param i_fMain [in] 処理ファンクタ
	@param post [in] 事後処理ファンクタ
	@param nPriority [in] プライオリティー
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
	@brief デストラクター
	*/
	virtual ~Job(){}

	/**
	@brief	更新処理
	@note	親子階層とプライオリティを考慮した同期で実行
	*/
	virtual void Update(void)	{ update(); }

	/**
	@brief	非同期更新処理
	@note	順不同、非同期で実行
	Job全てのUpdate開始から終了までの間に実行されるのでスレッドセーフにする必要がある
	*/
	virtual void UpdateASync(void)	{ updateASync(); }

private:
	const std::function<void()>		update;				//!< 更新処理
	const std::function<void()>		updateASync;		//!< 非同期更新処理
};

#endif		//__JOB_H__

