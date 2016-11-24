/**
	@file jobManager.cpp
	@brief ���s�����K��N���X
*/

#include "stdafx.h"
#include "framework/jobManager.h"
#include "appContext.h"

using namespace cpplinq;

//---------------------------------------------------------------------
JobManager::JobManager()
	: ProcessManagerBase()
	, _root("root job")
{
	UpdateProcessList(_threadList, &_root);
}

//---------------------------------------------------------------------
JobManager::~JobManager()
{
	for (auto& i : _threadList){ SAFE_DELETE(i); }
}

//---------------------------------------------------------------------
void JobManager::Proc(void)
{
	// �폜�t���O�����Ă���̂��폜
	const bool bRet = Erase(&_root);
	if (bRet) UpdateProcessList(_threadList, &_root);

	// �X���b�h�ւ̓o�^
	for (unsigned int i = 0; i < _threadList.size(); ++i)
	{
		AppContext::GetInstance()->GetThreadChannel()->PushRequest(_threadList[i]);
	}

	// �X�V����
	_root.ProcessImpl([](Job* p){ p->Update(); });

	// �X���b�h�̓���
	for (unsigned int i = 0; i < _threadList.size(); ++i){ _threadList[i]->Wait(); }
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


