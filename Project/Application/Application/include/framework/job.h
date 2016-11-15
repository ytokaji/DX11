/**
	@file job.h
	@brief 実行処理規定クラス
*/
#pragma once
#ifndef __JOB_H__
#define __JOB_H__

#include "framework/process.h"

/**
	@class CJob
	@brief 処理実行
*/
class CJob : public CProcess < CJob, JOB_PRIORITY >
{
public:
	/**
		@brief コンストラクター
		@param pszid [in] 識別子
		@param i_fPre [in] 事前処理ファンクタ
		@param i_fMain [in] 処理ファンクタ
		@param i_fPost [in] 事後処理ファンクタ
		@param nPriority [in] プライオリティー
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
		@brief デストラクター
		*/
	virtual ~CJob()
	{
	}
	
	/**
		@brief	更新処理
		@note	親子階層とプライオリティを考慮した同期で実行
	*/
	virtual void update(void)	{m_fUpdate();}

	/**
		@brief	非同期更新処理
		@note	順不同、非同期で実行
				CJob全てのupdate開始から終了までの間に実行されるのでスレッドセーフにする必要がある
	*/
	virtual void updateASync(void)	{ m_fUpdateASync(); }

private:
	const std::function<void()>		m_fUpdate;				//!< 更新処理
	const std::function<void()>		m_fUpdateASync;			//!< 非同期更新処理
};

#endif		//__JOB_H__

