/**
	@file thread.h
	@brief �X���b�h
*/
#pragma once
#ifndef __THREAD_H__
#define __THREAD_H__


class ThreadRequestBase;

/**
	@brief	�v���Z�X�Ǘ�
*/
class ThreadChannel
{
public:
	/**
		@brief �R���X�g���N�^
	*/
	ThreadChannel(unsigned int threadNum);

	/**
		@brief �f�X�g���N�^
	*/
	~ThreadChannel();

	/**
		@brief ���N�G�X�g�̃v�b�V��
	*/
	void PushRequest(ThreadRequestBase* thread);
	
	/**
		@brief ���N�G�X�g�̃|�b�v
	*/
	ThreadRequestBase* PopRequest();

private:
	/**
		@brief	�d�������s����N���X
	*/
	class WorkerThread
	{
	public:
		WorkerThread(ThreadChannel* channel);
		~WorkerThread();

	private:
		void Run();

	private:
		ThreadChannel*	_channel;			//!< ThreadChannel�|�C���^
		std::thread		_thread;			//!< �X���b�h
		bool			_endFlg;			//!< �I���t���O
	};

	std::vector<WorkerThread*>			_workerThread;	//!< WorkerThread�z��
	std::queue<ThreadRequestBase*>		_queue;			//!< �L���[
	std::mutex							_mutex;			//!< �~���[�e�b�N�X
};

/**
	@brief	�W���u�Ǘ�
*/
class ThreadRequestBase
{
public:
	/**
		@brief �R���X�g���N�^
	*/
	ThreadRequestBase() : _isEnd(true){}
	
	/**
		@brief �f�X�g���N�^
	*/
	virtual ~ThreadRequestBase(){}
	
	/**
		@brief �I������܂őҋ@
	*/
	void Wait() const;

	/**
		@brief �I��������
	*/
	bool IsEnd() const { return _isEnd; }

	virtual ThreadRequestBase& operator =(const ThreadRequestBase& r) { this->_isEnd = r._isEnd; return *this; }

protected:
	/**
	@brief ����
	*/
	virtual void Execute() = 0;

private:
	bool	_isEnd;		//!< �����I���������t���O

	friend class ThreadChannel;
};

#endif		//__THREAD_H__


