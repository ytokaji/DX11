/**
	@file thread.cpp
	@brief ƒXƒŒƒbƒh
*/

#include "stdafx.h"
#include "framework/thread.h"

//---------------------------------------------------------------------
CThreadChannel::CWorkerThread::CWorkerThread(CThreadChannel* i_pChannel)
	: m_pChannel(i_pChannel)
	, m_bEndFlg(false)
{
	m_Thread = std::thread([this]{ this->run(); });
}

//---------------------------------------------------------------------
CThreadChannel::CWorkerThread::~CWorkerThread()
{
	m_bEndFlg = true;
	m_Thread.join();
}

//---------------------------------------------------------------------
void CThreadChannel::CWorkerThread::run()
{
	while (m_bEndFlg == false)
	{
		IThreadRequest* pReq = m_pChannel->popRequest();
		
		if (pReq == nullptr)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(0));
			continue;
		}

		pReq->execute();
		pReq->m_bIsEnd = true;
	}
}

//---------------------------------------------------------------------
CThreadChannel::CThreadChannel(unsigned int i_nThreadNum)
{
	m_apWorkerThread.reserve(i_nThreadNum);
	for (unsigned int i = 0; i < i_nThreadNum; ++i )
	{
		m_apWorkerThread.push_back(new CWorkerThread(this));
	}
}

//---------------------------------------------------------------------
CThreadChannel::~CThreadChannel()
{
	util::for_each(m_apWorkerThread, [](CWorkerThread* p){SAFE_DELETE(p); });
}

//---------------------------------------------------------------------
void CThreadChannel::pushRequest(IThreadRequest* i_pThread)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	i_pThread->m_bIsEnd = false;
	m_Queue.push(i_pThread);
}

//---------------------------------------------------------------------
IThreadRequest* CThreadChannel::popRequest()
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	if (m_Queue.empty() ) return nullptr;

	IThreadRequest* p = m_Queue.front();
	m_Queue.pop();
	return p;
}

//---------------------------------------------------------------------
void IThreadRequest::wait()
{
	while (m_bIsEnd == false)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(0));
	}
}


