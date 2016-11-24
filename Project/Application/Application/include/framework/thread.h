/**
	@file thread.h
	@brief スレッド
*/
#pragma once
#ifndef __THREAD_H__
#define __THREAD_H__


class ThreadRequestBase;

/**
	@brief	プロセス管理
*/
class ThreadChannel
{
public:
	/**
		@brief コンストラクタ
	*/
	ThreadChannel(unsigned int threadNum);

	/**
		@brief デストラクタ
	*/
	~ThreadChannel();

	/**
		@brief リクエストのプッシュ
	*/
	void PushRequest(ThreadRequestBase* thread);
	
	/**
		@brief リクエストのポップ
	*/
	ThreadRequestBase* PopRequest();

private:
	/**
		@brief	仕事を実行するクラス
	*/
	class WorkerThread
	{
	public:
		WorkerThread(ThreadChannel* channel);
		~WorkerThread();

	private:
		void Run();

	private:
		ThreadChannel*	_channel;			//!< ThreadChannelポインタ
		std::thread		_thread;			//!< スレッド
		bool			_endFlg;			//!< 終了フラグ
	};

	std::vector<WorkerThread*>			_workerThread;	//!< WorkerThread配列
	std::queue<ThreadRequestBase*>		_queue;			//!< キュー
	std::mutex							_mutex;			//!< ミューテックス
};

/**
	@brief	ジョブ管理
*/
class ThreadRequestBase
{
public:
	/**
		@brief コンストラクタ
	*/
	ThreadRequestBase() : _isEnd(true){}
	
	/**
		@brief デストラクタ
	*/
	virtual ~ThreadRequestBase(){}
	
	/**
		@brief 終了するまで待機
	*/
	void Wait() const;

	/**
		@brief 終了したか
	*/
	bool IsEnd() const { return _isEnd; }

	virtual ThreadRequestBase& operator =(const ThreadRequestBase& r) { this->_isEnd = r._isEnd; return *this; }

protected:
	/**
	@brief 処理
	*/
	virtual void Execute() = 0;

private:
	bool	_isEnd;		//!< 処理終了したかフラグ

	friend class ThreadChannel;
};

#endif		//__THREAD_H__


