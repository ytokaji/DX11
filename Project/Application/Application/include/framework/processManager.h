/**
	@file processManager.h
	@brief �����K��N���X
*/
#pragma once
#ifndef __PROSESS_MANAGER_H__
#define __PROSESS_MANAGER_H__

#include "framework/job.h"
#include "framework/render.h"
#include "framework/thread.h"

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
	template<class TArrayClass, class TClass> void UpdateProcessList(std::vector<TArrayClass>& list, TClass* root) const;
};

/**
	@brief	�W���u�Ǘ�
*/
class JobManager	:	public ProcessManagerBase
{
public:
	/**
		@brief �R���X�g���N�^
	*/
	JobManager();
	
	/**
		@brief �f�X�g���N�^
	*/
	virtual ~JobManager();
	
	/**
		@brief ���s
	*/
	virtual void Proc(void);

	/**
		@brief �ǉ�
		@param child [in] �ǉ�����v���Z�X
		@param parent [in] �e�Bnullptr�Ȃ烋�[�g�̉�
	*/
	void AddJob(Job* child, Job* parent = nullptr);

	/**
		@brief ����
		@param identifier [in] ���ʎq
	*/
	Job* FindJob(const char* identifier);
	
private:
	/**
		@brief �X�V�p�X���b�h
	*/
	class ProcThread : public ThreadRequestBase
	{
	public:
		ProcThread(Job* process) : ThreadRequestBase(), _process(process) {}
		virtual ~ProcThread(){};
		virtual void Execute(void) { _process->UpdateASync(); }

	private:
		Job*		_process;		//!< �v���Z�X�|�C���^
	};

private:
	std::vector<ProcThread>		_threadList;	//!< �X�V�p�X���b�h�z��
	Job							_root;			//!< ���[�g�v���Z�X
};

/**
	@brief	�����_�[�Ǘ�
*/
class RenderManager	:	public ProcessManagerBase
{
public:
	/**
		@brief �R���X�g���N�^
	*/
	RenderManager();
	
	/**
		@brief �f�X�g���N�^
	*/
	virtual ~RenderManager();
	
	/**
		@brief ���s
	*/
	virtual void Proc(void);

	/**
		@brief �ǉ�
		@param child [in] �ǉ�����v���Z�X
		@param parent [in] �e�Bnullptr�Ȃ烋�[�g�̉�
	*/
	void AddRender(Render* child, Render* parent = nullptr);

	/**
		@brief ����
		@param identifier [in] ���ʎq
	*/
	Render* FindRender(const char* identifier);
	
private:
	/**
		@brief �X�V�p�X���b�h
	*/
	class ProcThread : public ThreadRequestBase
	{
	public:
		ProcThread(Render* i_pProcess);
		ProcThread(const ProcThread& r) : ProcThread(r._process){};
		virtual ~ProcThread();
		virtual void Execute(void);
		
		/**
			@brief �R�}���h���X�g�K�p
		*/
		void ExecuteCommandList(ID3D11DeviceContext* immediateContext);
		
		/**
			@brief ������Z�q
		*/
		ProcThread& operator =(const ProcThread& src);

	private:
		ID3D11DeviceContext*	_context;		//!< RenderAsync�p�̃f�t�@�[�h�R���e�L�X�g
		ID3D11CommandList*		_command;		//!< RenderAsync�p�̃R�}���h���X�g
		Render*				_process;		//!< �v���Z�X�|�C���^
	};

private:
	std::vector<ProcThread>		_threadList;		//!< �X�V�p�X���b�h�z��
	Render						_root;				//!< ���[�g�v���Z�X
};
#endif		//__PROSESS_MANAGER_H__

