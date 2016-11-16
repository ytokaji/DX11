/**
	@file processManager.cpp
	@brief 処理規定クラス
*/

#include "stdafx.h"
#include "framework/processManager.h"
#include "appContext.h"

//---------------------------------------------------------------------
template<class TClass>
void ProcessManagerBase::AddProcess(TClass* child, TClass* parent) const
{
	_ASSERT(child && parent);
	_ASSERT(parent->_child.capacity() > parent->_child.size() + 1);

	child->_parent = parent;
	parent->_child.push_back(child);

	std::sort(parent->_child.begin(), parent->_child.end(), [](TClass* a, TClass* b){ return a->_priority < b->_priority; });
}

//---------------------------------------------------------------------
template<class TClass>
TClass* ProcessManagerBase::FindProcess(TClass* process, const char* identifier) const
{ 
	return process->FindChild(identifier);
}

//---------------------------------------------------------------------
template<class TClass>
bool ProcessManagerBase::Erase(TClass* process) const
{
	auto begin = process->_child.begin();
	auto end = process->_child.cend();
	bool bRetVal = false;

	while (begin != end)
	{
		if ((*begin)->IsErase())
		{
			SAFE_DELETE(*begin);
			begin = process->_child.erase(begin);
			bRetVal = true;
			continue;
		}

		bRetVal |= Erase(*begin);
		++begin;
	}

	return bRetVal;
}

//---------------------------------------------------------------------
template<class TArrayClass, class TClass> void ProcessManagerBase::UpdateProcessList(std::vector<TArrayClass>& list, TClass* root) const
{
	list = std::vector<TArrayClass>();
	list.reserve(PROCESS_ARRAY_MAX);
	root->ProcessImpl([&](TClass* p)
	{
		_ASSERT(list.capacity() > list.size() + 1);
		list.push_back(TArrayClass(p));
	});
}

//---------------------------------------------------------------------
JobManager::JobManager()
	: ProcessManagerBase()
	, _root("root job")
{
}

//---------------------------------------------------------------------
JobManager::~JobManager()
{
}

//---------------------------------------------------------------------
void JobManager::Proc(void)
{
	// 削除フラグ立ってるものを削除
	const bool bRet = Erase(&_root);
	if (bRet) UpdateProcessList(_threadList, &_root);
	
	// スレッドへの登録
	for (unsigned int i = 0; i < _threadList.size(); ++i)
		AppContext::GetInstance()->GetThreadChannel()->PushRequest(&_threadList[i]);
		
	// 更新処理
	_root.ProcessImpl([](Job* p){ p->Update(); });
	
	// スレッドの同期
	for (unsigned int i = 0; i < _threadList.size(); ++i)
		_threadList[i].Wait();
}

//---------------------------------------------------------------------
void JobManager::AddJob(Job* child, Job* parent)
{
	AddProcess(child, parent == nullptr ? &_root : parent);
	UpdateProcessList(_threadList, &_root);
}

//---------------------------------------------------------------------
Job* JobManager::FindJob(const char* identifier)
{
	return FindProcess(&_root, identifier);
}

//---------------------------------------------------------------------
RenderManager::ProcThread::ProcThread(Render* process)
	: ThreadRequestBase()
	, _context(nullptr)
	, _command(nullptr)
	, _process(process)
{
	ID3D11Device* pDevice = AppContext::GetInstance()->GetD3D11Device();
	HRESULT hr = pDevice->CreateDeferredContext(0, &_context);
	_ASSERT(SUCCEEDED(hr));
}

//---------------------------------------------------------------------
RenderManager::ProcThread::~ProcThread()
{
	SAFE_RELEASE(_context);
	SAFE_RELEASE(_command);
}

//---------------------------------------------------------------------
void RenderManager::ProcThread::Execute(void)
{
	_ASSERT(_command == nullptr);

	HRESULT hr = DXUTSetupD3D11Views(_context);
	_ASSERT(SUCCEEDED(hr));

	_process->SetActiveDeviceContext(_context);
	_process->RenderAsync();
	_process->SetActiveDeviceContext(nullptr);

	_context->FinishCommandList(false, &_command);
}

//---------------------------------------------------------------------
void RenderManager::ProcThread::ExecuteCommandList(ID3D11DeviceContext* immediateContext)
{
	immediateContext->ExecuteCommandList(_command, false);
	SAFE_RELEASE(_command);
}

//---------------------------------------------------------------------
RenderManager::ProcThread& RenderManager::ProcThread::operator =(const RenderManager::ProcThread& src)
{
	this->_process = src._process;
	this->_command = nullptr;
	ID3D11Device* pDevice = AppContext::GetInstance()->GetD3D11Device();
	HRESULT hr = pDevice->CreateDeferredContext(0, &this->_context);
	_ASSERT(SUCCEEDED(hr));

	return *this;
}

//---------------------------------------------------------------------
RenderManager::RenderManager()
	:	ProcessManagerBase			()
	,	_root					("root render")
{
	UpdateProcessList(_threadList, &_root);
}

//---------------------------------------------------------------------
RenderManager::~RenderManager()
{
}

//---------------------------------------------------------------------
void RenderManager::Proc(void)
{
	// 削除フラグ立ってるものを削除
	const bool bRet = Erase(&_root);
	if (bRet) UpdateProcessList(_threadList, &_root);

	// 事前処理
	_root.ProcessImpl([this](Render* p) { p->Pre(); });

	// スレッドへの登録と同期
	ThreadChannel* pChannel = AppContext::GetInstance()->GetThreadChannel();
	util::for_each(_threadList, [&](ProcThread& r){ pChannel->PushRequest(&r); });
	util::for_each(_threadList, [](ProcThread& r){ r.Wait(); });

	// 事後処理
	_root.ProcessImpl([this](Render* p) { p->Post(); });

	// デファードコンテキストを結合
	ID3D11DeviceContext* pContext = AppContext::GetInstance()->GetImmediateContext();
	util::for_each(_threadList, [&](ProcThread& r){ r.ExecuteCommandList(pContext); });
}

//---------------------------------------------------------------------
void RenderManager::AddRender(Render* child, Render* parent)
{
	AddProcess(child, parent == nullptr ? &_root : parent);
	UpdateProcessList(_threadList, &_root);
}

//---------------------------------------------------------------------
Render* RenderManager::FindRender(const char* identifier)
{
	return FindProcess(&_root, identifier);
}



