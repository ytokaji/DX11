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
class IProcessManager
{
public:
	/**
	@brief �R���X�g���N�^
	*/
	IProcessManager()
	{
	}

	/**
		@brief �f�X�g���N�^
	*/
	virtual ~IProcessManager()
	{
	}
	
	/**
		@brief ���s
	*/
	virtual void proc(void) = 0;
	
protected:
	/**
		@brief ���[�g�ɒǉ�
		@param i_pChild [in] �ǉ�����v���Z�X
		@param i_pParent [in] �e�Bnullptr�Ȃ烋�[�g�̉�
	*/
	template<class TClass> void addProcess(TClass* i_pChild, TClass* i_pParent) const;

	/**
		@brief ����
		@param i_pIdentifier [in] ���ʎq
	*/
	template<class TClass> TClass* findProcess(TClass* i_pProcess, const char* i_pIdentifier) const;

	/**
		@brief �����t���O�̂����Ă���v���Z�X�̍폜
		@param i_pProcess [in] ��v���Z�X
		@return �폜���ꂽ���̂���������
	*/
	template<class TClass> bool erase(TClass* i_pProcess) const;

	/**
		@brief �v���Z�X���X�g�̍X�V
		@param i_pProcess [in] ��v���Z�X
	*/
	template<class TArrayClass, class TClass> void updateProcessList(std::vector<TArrayClass>& i_apList, TClass* i_pRoot) const;
};

/**
	@brief	�W���u�Ǘ�
*/
class CJobManager	:	public IProcessManager
{
public:
	/**
		@brief �R���X�g���N�^
	*/
	CJobManager();
	
	/**
		@brief �f�X�g���N�^
	*/
	virtual ~CJobManager();
	
	/**
		@brief ���s
	*/
	virtual void proc(void);

	/**
		@brief �ǉ�
		@param i_pChild [in] �ǉ�����v���Z�X
		@param i_pParent [in] �e�Bnullptr�Ȃ烋�[�g�̉�
	*/
	void addJob(CJob* i_pChild, CJob* i_pParent = nullptr);

	/**
		@brief ����
		@param i_pIdentifier [in] ���ʎq
	*/
	CJob* findJob(const char* i_pIdentifier);
	
private:
	/**
		@brief �X�V�p�X���b�h
	*/
	class CProcThread : public IThreadRequest
	{
	public:
		CProcThread(CJob* i_pProcess) : IThreadRequest(), m_pProcess(i_pProcess) {}
		virtual ~CProcThread(){};
		virtual void execute(void) { m_pProcess->updateASync(); }

	private:
		CJob*		m_pProcess;		//!< �v���Z�X�|�C���^
	};

private:
	std::vector<CProcThread>	m_aThreadList;	//!< �X�V�p�X���b�h�z��
	CJob						m_Root;			//!< ���[�g�v���Z�X
};

/**
	@brief	�����_�[�Ǘ�
*/
class CRenderManager	:	public IProcessManager
{
public:
	/**
		@brief �R���X�g���N�^
	*/
	CRenderManager();
	
	/**
		@brief �f�X�g���N�^
	*/
	virtual ~CRenderManager();
	
	/**
		@brief ���s
	*/
	virtual void proc(void);

	/**
		@brief �ǉ�
		@param i_pChild [in] �ǉ�����v���Z�X
		@param i_pParent [in] �e�Bnullptr�Ȃ烋�[�g�̉�
	*/
	void addRender(CRender* i_pChild, CRender* i_pParent = nullptr);

	/**
		@brief ����
		@param i_pIdentifier [in] ���ʎq
	*/
	CRender* findRender(const char* i_pIdentifier);
	
private:
	/**
		@brief �X�V�p�X���b�h
	*/
	class CProcThread : public IThreadRequest
	{
	public:
		CProcThread(CRender* i_pProcess);
		CProcThread(const CProcThread& r) : CProcThread(r.m_pProcess){};
		virtual ~CProcThread();
		virtual void execute(void);
		
		/**
			@brief �R�}���h���X�g�K�p
		*/
		void executeCommandList(ID3D11DeviceContext* i_pImmediateContext);
		
		/**
			@brief ������Z�q
		*/
		CProcThread& operator =(const CProcThread& src);

	private:
		ID3D11DeviceContext*	m_pContext;		//!< render�p�̃f�t�@�[�h�R���e�L�X�g
		ID3D11CommandList*		m_pCommand;		//!< render�p�̃R�}���h���X�g
		CRender*				m_pProcess;		//!< �v���Z�X�|�C���^
	};

private:
	std::vector<CProcThread>	m_aThreadList;		//!< �X�V�p�X���b�h�z��

	CRender						m_Root;				//!< ���[�g�v���Z�X
};
#endif		//__PROSESS_MANAGER_H__

