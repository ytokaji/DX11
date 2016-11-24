/**
	@file renderManager.cpp
	@brief 描画処理規定クラス
*/

#include "stdafx.h"
#include "framework/renderManager.h"
#include "appContext.h"

using namespace cpplinq;

//---------------------------------------------------------------------
RenderManager::ProcThread::ProcThread(Render* process)
	: ThreadRequestBase()
	, _command(nullptr)
	, _process(process)
{
}

//---------------------------------------------------------------------
RenderManager::ProcThread::~ProcThread()
{
	SAFE_RELEASE(_command);
}

//---------------------------------------------------------------------
void RenderManager::ProcThread::Execute(void)
{
	_ASSERT(_command == nullptr);

	HRESULT hr = DXUTSetupD3D11Views(_process->GetDeviceContext());
	_ASSERT(SUCCEEDED(hr));

	_process->RenderAsync();

	_process->GetDeviceContext()->FinishCommandList(false, &_command);
}

//---------------------------------------------------------------------
void RenderManager::ProcThread::ExecuteCommandList(ID3D11DeviceContext* immediateContext)
{
	if (_command == nullptr) { return; }
	immediateContext->ExecuteCommandList(_command, false);
	SAFE_RELEASE(_command);
}

//---------------------------------------------------------------------
RenderManager::RenderManager()
	: ProcessManagerBase()
	, _root("root render")
{
	UpdateProcessList(_threadList, &_root);
}

//---------------------------------------------------------------------
RenderManager::~RenderManager()
{
	for (auto& i : _threadList){ SAFE_DELETE(i); }
}

//---------------------------------------------------------------------
void RenderManager::Proc(void)
{
	// 削除フラグ立ってるものを削除
	const bool bRet = Erase(&_root);
	if (bRet){ UpdateProcessList(_threadList, &_root); }

	// 事前処理
	_root.ProcessImpl([this](Render* p) { p->Pre(); });

	// スレッドへの登録と同期
	for (auto&& i : _threadList) { AppContext::GetInstance()->GetThreadChannel()->PushRequest(i); }
	for (const auto& i : _threadList) { i->Wait(); }

	// デファードコンテキストを結合
	for (auto&& i : _threadList) { i->ExecuteCommandList(AppContext::GetInstance()->GetImmediateContext()); }

	// 事後処理
	_root.ProcessImpl([this](Render* p) { p->Post(); });
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


