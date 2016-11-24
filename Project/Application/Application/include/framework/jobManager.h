/**
@file jobManager.h
@brief 実行処理規定クラス
*/
#pragma once
#ifndef __JOB_MANAGER_H__
#define __JOB_MANAGER_H__

#include "framework/processManager.h"
#include "framework/process.h"
#include "framework/thread.h"
#include "framework/job.h"

/**
@brief	ジョブ管理
*/
class JobManager : public ProcessManagerBase
{
public:
	/**
	@brief コンストラクタ
	*/
	JobManager();

	/**
	@brief デストラクタ
	*/
	virtual ~JobManager();

	/**
	@brief 実行
	*/
	virtual void Proc(void);

	/**
	@brief 追加
	@param child [in] 追加するプロセス
	@param parent [in] 親。nullptrならルートの下
	*/
	void AddJob(Job* child, Job* parent = nullptr);

	/**
	@brief 検索
	@param identifier [in] 識別子
	*/
	Job* FindJob(const char* identifier);

private:
	/**
	@brief 更新用スレッド
	*/
	class ProcThread : public ThreadRequestBase
	{
	public:
		ProcThread(Job* process) : ThreadRequestBase(), _process(process) {}
		virtual ~ProcThread(){};
		virtual void Execute(void) { _process->UpdateASync(); }

	private:
		Job*		_process;		//!< プロセスポインタ
	};

private:
	std::vector<ProcThread*>	_threadList;	//!< 更新用スレッド配列
	Job							_root;			//!< ルートプロセス
};

#endif		//__JOB_MANAGER_H__

