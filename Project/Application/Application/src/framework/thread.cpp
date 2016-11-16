/**
	@file thread.cpp
	@brief ƒXƒŒƒbƒh
*/

#include "stdafx.h"
#include "framework/thread.h"

//---------------------------------------------------------------------
ThreadChannel::WorkerThread::WorkerThread(ThreadChannel* channel)
	: _channel(channel)
	, _endFlg(false)
{
	_thread = std::thread([this]{ this->Run(); });
}

//---------------------------------------------------------------------
ThreadChannel::WorkerThread::~WorkerThread()
{
	_endFlg = true;
	_thread.join();
}

//---------------------------------------------------------------------
void ThreadChannel::WorkerThread::Run()
{
	while (_endFlg == false)
	{
		ThreadRequestBase* pReq = _channel->PopRequest();
		
		if (pReq == nullptr)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(0));
			continue;
		}

		pReq->Execute();
		pReq->_isEnd = true;
	}
}

//---------------------------------------------------------------------
ThreadChannel::ThreadChannel(unsigned int threadNum)
{
	_workerThread.reserve(threadNum);
	for (unsigned int i = 0; i < threadNum; ++i )
	{
		_workerThread.push_back(new WorkerThread(this));
	}
}

//---------------------------------------------------------------------
ThreadChannel::~ThreadChannel()
{
	util::for_each(_workerThread, [](WorkerThread* p){SAFE_DELETE(p); });
}

//---------------------------------------------------------------------
void ThreadChannel::PushRequest(ThreadRequestBase* thread)
{
	std::lock_guard<std::mutex> lock(_mutex);
	thread->_isEnd = false;
	_queue.push(thread);
}

//---------------------------------------------------------------------
ThreadRequestBase* ThreadChannel::PopRequest()
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_queue.empty() ) return nullptr;

	ThreadRequestBase* p = _queue.front();
	_queue.pop();
	return p;
}

//---------------------------------------------------------------------
void ThreadRequestBase::Wait()
{
	while (_isEnd == false)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(0));
	}
}


