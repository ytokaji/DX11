/**
	@file thread.h
	@brief �X���b�h
*/
#pragma once
#ifndef __THREAD_H__
#define __THREAD_H__


class IThreadRequest;

/**
	@brief	�v���Z�X�Ǘ�
*/
class CThreadChannel
{
public:
	/**
		@brief �R���X�g���N�^
	*/
	CThreadChannel(unsigned int i_nThreadNum);

	/**
		@brief �f�X�g���N�^
	*/
	~CThreadChannel();

	/**
		@brief ���N�G�X�g�̃v�b�V��
	*/
	void pushRequest(IThreadRequest* i_pThread);
	
	/**
		@brief ���N�G�X�g�̃|�b�v
	*/
	IThreadRequest* popRequest();

private:
	/**
		@brief	�d�������s����N���X
	*/
	class CWorkerThread
	{
	public:
		CWorkerThread(CThreadChannel* i_pChannel);
		~CWorkerThread();

	private:
		void run();

	private:
		CThreadChannel*	m_pChannel;			//!< CThreadChannel�|�C���^
		std::thread		m_Thread;			//!< �X���b�h
		bool			m_bEndFlg;			//!< �I���t���O
	};

	std::vector<CWorkerThread*>			m_apWorkerThread;	//!< CWorkerThread�z��
	std::queue<IThreadRequest*>			m_Queue;			//!< �L���[
	std::mutex							m_Mutex;			//!< �~���[�e�b�N�X
};

/**
	@brief	�W���u�Ǘ�
*/
class IThreadRequest
{
public:
	/**
		@brief �R���X�g���N�^
	*/
	IThreadRequest() : m_bIsEnd(true){}
	
	/**
		@brief �f�X�g���N�^
	*/
	virtual ~IThreadRequest(){}
	
	/**
		@brief ����
	*/
	virtual void execute(void) = 0;
		
	/**
		@brief �I������܂őҋ@
	*/
	void wait(void);

	/**
		@brief �I��������
	*/
	bool isEnd(void) { return m_bIsEnd; }

	virtual IThreadRequest& operator =(const IThreadRequest& r) { this->m_bIsEnd = r.m_bIsEnd; return *this; }

private:
	bool	m_bIsEnd;		//!< �����I���������t���O

	friend class CThreadChannel;
};

#endif		//__THREAD_H__


