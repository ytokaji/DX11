/**
	@file processManager.h
	@brief �����K��N���X
*/
#pragma once
#ifndef __PROSESS_MANAGER_H__
#define __PROSESS_MANAGER_H__

/**
	@brief	�v���Z�X�Ǘ�
*/
class ProcessManagerBase
{
public:
	/**
	@brief �R���X�g���N�^
	*/
	ProcessManagerBase(){}

	/**
		@brief �f�X�g���N�^
	*/
	virtual ~ProcessManagerBase(){}
	
	/**
		@brief ���s
	*/
	virtual void Proc(void) = 0;
	
protected:
	/**
		@brief ���[�g�ɒǉ�
		@param child [in] �ǉ�����v���Z�X
		@param parent [in] �e�Bnullptr�Ȃ烋�[�g�̉�
	*/
	template<class TClass> void AddProcess(TClass* child, TClass* parent) const;

	/**
		@brief ����
		@param identifier [in] ���ʎq
	*/
	template<class TClass> TClass* FindProcess(TClass* process, const char* identifier) const;

	/**
		@brief �����t���O�̂����Ă���v���Z�X�̍폜
		@param i_pProcess [in] ��v���Z�X
		@return �폜���ꂽ���̂���������
	*/
	template<class TClass> bool Erase(TClass* process) const;

	/**
		@brief �v���Z�X���X�g�̍X�V
		@param i_pProcess [in] ��v���Z�X
	*/
	template<class TArrayClass, class TClass> void UpdateProcessList(std::vector<TArrayClass*>& list, TClass* root) const;
};

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
template<class TArrayClass, class TClass> void ProcessManagerBase::UpdateProcessList(std::vector<TArrayClass*>& list, TClass* root) const
{
	for (auto& i : list){ SAFE_DELETE(i); }
	list = std::vector<TArrayClass*>();
	list.reserve(PROCESS_ARRAY_MAX);

	root->ProcessImpl([&](TClass* p)
	{
		_ASSERT(list.capacity() > list.size() + 1);
		list.push_back(new TArrayClass(p));
	});
}

#endif		//__PROSESS_MANAGER_H__

