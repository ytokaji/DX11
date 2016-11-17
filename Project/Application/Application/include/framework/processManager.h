/**
	@file processManager.h
	@brief 処理規定クラス
*/
#pragma once
#ifndef __PROSESS_MANAGER_H__
#define __PROSESS_MANAGER_H__

#include "framework/job.h"
#include "framework/render.h"
#include "framework/thread.h"

/**
	@brief	プロセス管理
*/
class ProcessManagerBase
{
public:
	/**
	@brief コンストラクタ
	*/
	ProcessManagerBase(){}

	/**
		@brief デストラクタ
	*/
	virtual ~ProcessManagerBase(){}
	
	/**
		@brief 実行
	*/
	virtual void Proc(void) = 0;
	
protected:
	/**
		@brief ルートに追加
		@param child [in] 追加するプロセス
		@param parent [in] 親。nullptrならルートの下
	*/
	template<class TClass> void AddProcess(TClass* child, TClass* parent) const;

	/**
		@brief 検索
		@param identifier [in] 識別子
	*/
	template<class TClass> TClass* FindProcess(TClass* process, const char* identifier) const;

	/**
		@brief 消去フラグのたっているプロセスの削除
		@param i_pProcess [in] 基準プロセス
		@return 削除されたものがあったか
	*/
	template<class TClass> bool Erase(TClass* process) const;

	/**
		@brief プロセスリストの更新
		@param i_pProcess [in] 基準プロセス
	*/
	template<class TArrayClass, class TClass> void UpdateProcessList(std::vector<TArrayClass>& list, TClass* root) const;
};

/**
	@brief	ジョブ管理
*/
class JobManager	:	public ProcessManagerBase
{
public:
	/**
		@brief コンストラクタ
	*/
	JobManager();
	
	/**
		@brief デストラクタ
	*/
	virtual ~JobManager();
	
	/**
		@brief 実行
	*/
	virtual void Proc(void);

	/**
		@brief 追加
		@param child [in] 追加するプロセス
		@param parent [in] 親。nullptrならルートの下
	*/
	void AddJob(Job* child, Job* parent = nullptr);

	/**
		@brief 検索
		@param identifier [in] 識別子
	*/
	Job* FindJob(const char* identifier);
	
private:
	/**
		@brief 更新用スレッド
	*/
	class ProcThread : public ThreadRequestBase
	{
	public:
		ProcThread(Job* process) : ThreadRequestBase(), _process(process) {}
		virtual ~ProcThread(){};
		virtual void Execute(void) { _process->UpdateASync(); }

	private:
		Job*		_process;		//!< プロセスポインタ
	};

private:
	std::vector<ProcThread>		_threadList;	//!< 更新用スレッド配列
	Job							_root;			//!< ルートプロセス
};

/**
	@brief	レンダー管理
*/
class RenderManager	:	public ProcessManagerBase
{
public:
	/**
		@brief コンストラクタ
	*/
	RenderManager();
	
	/**
		@brief デストラクタ
	*/
	virtual ~RenderManager();
	
	/**
		@brief 実行
	*/
	virtual void Proc(void);

	/**
		@brief 追加
		@param child [in] 追加するプロセス
		@param parent [in] 親。nullptrならルートの下
	*/
	void AddRender(Render* child, Render* parent = nullptr);

	/**
		@brief 検索
		@param identifier [in] 識別子
	*/
	Render* FindRender(const char* identifier);
	
private:
	/**
		@brief 更新用スレッド
	*/
	class ProcThread : public ThreadRequestBase
	{
	public:
		ProcThread(Render* i_pProcess);
		ProcThread(const ProcThread& r) : ProcThread(r._process){};
		virtual ~ProcThread();
		virtual void Execute(void);
		
		/**
			@brief コマンドリスト適用
		*/
		void ExecuteCommandList(ID3D11DeviceContext* immediateContext);
		
		/**
			@brief 代入演算子
		*/
		ProcThread& operator =(const ProcThread& src);

	private:
		ID3D11DeviceContext*	_context;		//!< RenderAsync用のデファードコンテキスト
		ID3D11CommandList*		_command;		//!< RenderAsync用のコマンドリスト
		Render*				_process;		//!< プロセスポインタ
	};

private:
	std::vector<ProcThread>		_threadList;		//!< 更新用スレッド配列
	Render						_root;				//!< ルートプロセス
};
#endif		//__PROSESS_MANAGER_H__

