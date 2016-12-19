/**
	@file renderManager.h
	@brief �`�揈���K��N���X
*/
#pragma once
#ifndef __RENDER_MANAGER_H__
#define __RENDER_MANAGER_H__

#include "framework/processManager.h"
#include "framework/render.h"
#include "framework/process.h"
#include "framework/thread.h"

class RenderProcess;

/**
@brief	�����_�[�Ǘ�
*/
class RenderManager : public ProcessManagerBase
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
	void AddRender(RenderProcess* child, RenderProcess* parent = nullptr);

	/**
	@brief ����
	@param identifier [in] ���ʎq
	*/
	RenderProcess* FindRender(const char* identifier);

private:
	/**
	@brief �X�V�p�X���b�h
	*/
	class ProcThread : public ThreadRequestBase
	{
	public:
		ProcThread(RenderProcess* i_pProcess);
		ProcThread(const ProcThread& r) : ProcThread(r._process){};
		virtual ~ProcThread();
		virtual void Execute(void);

		/**
		@brief �R�}���h���X�g�K�p
		*/
		void ExecuteCommandList(ID3D11DeviceContext* immediateContext);

	private:
		/**
		@brief ������Z�q
		*/
		ProcThread& operator =(const ProcThread&){};

	private:
		ID3D11CommandList*		_command;		//!< RenderAsync�p�̃R�}���h���X�g
		RenderProcess*			_process;		//!< �v���Z�X�|�C���^
	};

private:
	std::vector<ProcThread*>	_threadList;	//!< �X�V�p�X���b�h�z��
	RenderProcess				_root;			//!< ���[�g�v���Z�X
};


#endif		//__RENDER_MANAGER_H__

