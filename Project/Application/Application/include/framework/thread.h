/**
	@file thread.h
	@brief スレッド
*/
#pragma once
#ifndef __THREAD_H__
#define __THREAD_H__


class IThreadRequest;

/**
	@brief	プロセス管理
*/
class CThreadChannel
{
public:
	/**
		@brief コンストラクタ
	*/
	CThreadChannel(unsigned int i_nThreadNum);

	/**
		@brief デストラクタ
	*/
	~CThreadChannel();

	/**
		@brief リクエストのプッシュ
	*/
	void pushRequest(IThreadRequest* i_pThread);
	
	/**
		@brief リクエストのポップ
	*/
	IThreadRequest* popRequest();

private:
	/**
		@brief	仕事を実行するクラス
	*/
	class CWorkerThread
	{
	public:
		CWorkerThread(CThreadChannel* i_pChannel);
		~CWorkerThread();

	private:
		void run();

	private:
		CThreadChannel*	m_pChannel;			//!< CThreadChannelポインタ
		std::thread		m_Thread;			//!< スレッド
		bool			m_bEndFlg;			//!< 終了フラグ
	};

	std::vector<CWorkerThread*>			m_apWorkerThread;	//!< CWorkerThread配列
	std::queue<IThreadRequest*>			m_Queue;			//!< キュー
	std::mutex							m_Mutex;			//!< ミューテックス
};

/**
	@brief	ジョブ管理
*/
class IThreadRequest
{
public:
	/**
		@brief コンストラクタ
	*/
	IThreadRequest() : m_bIsEnd(true){}
	
	/**
		@brief デストラクタ
	*/
	virtual ~IThreadRequest(){}
	
	/**
		@brief 処理
	*/
	virtual void execute(void) = 0;
		
	/**
		@brief 終了するまで待機
	*/
	void wait(void);

	/**
		@brief 終了したか
	*/
	bool isEnd(void) { return m_bIsEnd; }

	virtual IThreadRequest& operator =(const IThreadRequest& r) { this->m_bIsEnd = r.m_bIsEnd; return *this; }

private:
	bool	m_bIsEnd;		//!< 処理終了したかフラグ

	friend class CThreadChannel;
};

#endif		//__THREAD_H__


