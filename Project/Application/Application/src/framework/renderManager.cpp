/**
	@file renderManager.cpp
	@brief �`�揈���K��N���X
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
	// �폜�t���O�����Ă���̂��폜
	const bool bRet = Erase(&_root);
	if (bRet){ UpdateProcessList(_threadList, &_root); }

	// ���O����
	_root.ProcessImpl([this](Render* p) { p->Pre(); });

	// �X���b�h�ւ̓o�^�Ɠ���
	for (auto&& i : _threadList) { AppContext::GetInstance()->GetThreadChannel()->PushRequest(i); }
	for (const auto& i : _threadList) { i->Wait(); }

	// �f�t�@�[�h�R���e�L�X�g������
	for (auto&& i : _threadList) { i->ExecuteCommandList(AppContext::GetInstance()->GetImmediateContext()); }

	// ���㏈��
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


