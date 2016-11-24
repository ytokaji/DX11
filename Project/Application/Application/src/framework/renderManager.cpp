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
	, _context(nullptr)
	, _command(nullptr)
	, _process(process)
{
	ID3D11Device* device = AppContext::GetInstance()->GetD3D11Device();
	HRESULT hr = device->CreateDeferredContext(0, &_context);
	_ASSERT(SUCCEEDED(hr));

	process->SetActiveDeviceContext(_context);
	process->Init();
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

	_process->RenderAsync();
	_context->FinishCommandList(false, &_command);
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
	if (bRet) UpdateProcessList(_threadList, &_root);

	// ���O����
	_root.ProcessImpl([this](Render* p) { p->Pre(); });

	// �X���b�h�ւ̓o�^�Ɠ���
	for (auto&& i : _threadList) { AppContext::GetInstance()->GetThreadChannel()->PushRequest(i); }
	for (const auto& i : _threadList) { i->Wait(); }

	// ���㏈��
	_root.ProcessImpl([this](Render* p) { p->Post(); });

	// �f�t�@�[�h�R���e�L�X�g������
	for (auto&& i : _threadList) { i->ExecuteCommandList(AppContext::GetInstance()->GetImmediateContext()); }
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


