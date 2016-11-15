/**
	@file processManager.cpp
	@brief 処理規定クラス
*/

#include "stdafx.h"
#include "framework/processManager.h"
#include "appContext.h"

//---------------------------------------------------------------------
template<class TClass>
void IProcessManager::addProcess(TClass* i_pChild, TClass* i_pParent) const
{
	_ASSERT(i_pChild && i_pParent);
	_ASSERT(i_pParent->m_apChild.capacity() > i_pParent->m_apChild.size() + 1);

	i_pChild->m_pParent = i_pParent;
	i_pParent->m_apChild.push_back(i_pChild);

	std::sort(i_pParent->m_apChild.begin(), i_pParent->m_apChild.end(), [](TClass* a, TClass* b){ return a->m_ePriority < b->m_ePriority; });
}

//---------------------------------------------------------------------
template<class TClass>
TClass* IProcessManager::findProcess(TClass* i_pProcess, const char* i_pIdentifier) const
{ 
	return i_pProcess->findChild(i_pIdentifier);
}

//---------------------------------------------------------------------
template<class TClass>
bool IProcessManager::erase(TClass* i_pProcess) const
{
	auto begin = i_pProcess->m_apChild.begin();
	auto end = i_pProcess->m_apChild.cend();
	bool bRetVal = false;

	while (begin != end)
	{
		if ((*begin)->isErase())
		{
			SAFE_DELETE(*begin);
			begin = i_pProcess->m_apChild.erase(begin);
			bRetVal = true;
			continue;
		}

		bRetVal |= erase(*begin);
		++begin;
	}

	return bRetVal;
}

//---------------------------------------------------------------------
template<class TArrayClass, class TClass> void IProcessManager::updateProcessList(std::vector<TArrayClass>& i_apList, TClass* i_pRoot) const
{
	i_apList = std::vector<TArrayClass>();
	i_apList.reserve(PROCESS_ARRAY_MAX);
	i_pRoot->process([&](TClass* p)
	{
		_ASSERT(i_apList.capacity() > i_apList.size() + 1);
		i_apList.push_back(TArrayClass(p));
	});
}

//---------------------------------------------------------------------
CJobManager::CJobManager()
	: IProcessManager()
	, m_Root("root job")
{
}

//---------------------------------------------------------------------
CJobManager::~CJobManager()
{
}

//---------------------------------------------------------------------
void CJobManager::proc(void)
{
	// 削除フラグ立ってるものを削除
	const bool bRet = erase(&m_Root);
	if (bRet) updateProcessList(m_aThreadList, &m_Root);
	
	// スレッドへの登録
	for (unsigned int i = 0; i < m_aThreadList.size(); ++i)
		CAppContext::getInstance()->getThreadChannel()->pushRequest(&m_aThreadList[i]);
		
	// 更新処理
	m_Root.process([](CJob* p){ p->update(); });
	
	// スレッドの同期
	for (unsigned int i = 0; i < m_aThreadList.size(); ++i)
		m_aThreadList[i].wait();
}

//---------------------------------------------------------------------
void CJobManager::addJob(CJob* i_pChild, CJob* i_pParent)
{
	addProcess(i_pChild, i_pParent == nullptr ? &m_Root : i_pParent);
	updateProcessList(m_aThreadList, &m_Root);
}

//---------------------------------------------------------------------
CJob* CJobManager::findJob(const char* i_pIdentifier)
{
	return findProcess(&m_Root, i_pIdentifier);
}

//---------------------------------------------------------------------
CRenderManager::CProcThread::CProcThread(CRender* i_pProcess)
	: IThreadRequest()
	, m_pContext(nullptr)
	, m_pCommand(nullptr)
	, m_pProcess(i_pProcess)
{
	ID3D11Device* pDevice = CAppContext::getInstance()->getD3D11Device();
	HRESULT hr = pDevice->CreateDeferredContext(0, &m_pContext);
	_ASSERT(SUCCEEDED(hr));
}

//---------------------------------------------------------------------
CRenderManager::CProcThread::~CProcThread()
{
	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pCommand);
}

//---------------------------------------------------------------------
void CRenderManager::CProcThread::execute(void)
{
	_ASSERT(m_pCommand == nullptr);

	HRESULT hr = DXUTSetupD3D11Views(m_pContext);
	_ASSERT(SUCCEEDED(hr));

	m_pProcess->setActiveDeviceContext(m_pContext);
	m_pProcess->render();
	m_pProcess->setActiveDeviceContext(nullptr);

	m_pContext->FinishCommandList(false, &m_pCommand);
}

//---------------------------------------------------------------------
void CRenderManager::CProcThread::executeCommandList(ID3D11DeviceContext* i_pImmediateContext)
{
	i_pImmediateContext->ExecuteCommandList(m_pCommand, false);
	SAFE_RELEASE(m_pCommand);
}

//---------------------------------------------------------------------
CRenderManager::CProcThread& CRenderManager::CProcThread::operator =(const CRenderManager::CProcThread& src)
{
	this->m_pProcess = src.m_pProcess;
	this->m_pCommand = nullptr;
	ID3D11Device* pDevice = CAppContext::getInstance()->getD3D11Device();
	HRESULT hr = pDevice->CreateDeferredContext(0, &this->m_pContext);
	_ASSERT(SUCCEEDED(hr));

	return *this;
}

//---------------------------------------------------------------------
CRenderManager::CRenderManager()
	:	IProcessManager			()
	,	m_Root					("root render")
{
	updateProcessList(m_aThreadList, &m_Root);
}

//---------------------------------------------------------------------
CRenderManager::~CRenderManager()
{
}

//---------------------------------------------------------------------
void CRenderManager::proc(void)
{
	// 削除フラグ立ってるものを削除
	const bool bRet = erase(&m_Root);
	if (bRet) updateProcessList(m_aThreadList, &m_Root);

	// 事前処理
	m_Root.process([this](CRender* p) { p->pre(); });

	// スレッドへの登録と同期
	CThreadChannel* pChannel = CAppContext::getInstance()->getThreadChannel();
	util::for_each(m_aThreadList, [&](CProcThread& r){ pChannel->pushRequest(&r); });
	util::for_each(m_aThreadList, [](CProcThread& r){ r.wait(); });

	// 事後処理
	m_Root.process([this](CRender* p) { p->post(); });

	// デファードコンテキストを結合
	ID3D11DeviceContext* pContext = CAppContext::getInstance()->getImmediateContext();
	util::for_each(m_aThreadList, [&](CProcThread& r){ r.executeCommandList(pContext); });
}

//---------------------------------------------------------------------
void CRenderManager::addRender(CRender* i_pChild, CRender* i_pParent)
{
	addProcess(i_pChild, i_pParent == nullptr ? &m_Root : i_pParent);
	updateProcessList(m_aThreadList, &m_Root);
}

//---------------------------------------------------------------------
CRender* CRenderManager::findRender(const char* i_pIdentifier)
{
	return findProcess(&m_Root, i_pIdentifier);
}



