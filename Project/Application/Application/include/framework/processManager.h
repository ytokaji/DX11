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
class IProcessManager
{
public:
	/**
	@brief コンストラクタ
	*/
	IProcessManager()
	{
	}

	/**
		@brief デストラクタ
	*/
	virtual ~IProcessManager()
	{
	}
	
	/**
		@brief 実行
	*/
	virtual void proc(void) = 0;
	
protected:
	/**
		@brief ルートに追加
		@param i_pChild [in] 追加するプロセス
		@param i_pParent [in] 親。nullptrならルートの下
	*/
	template<class TClass> void addProcess(TClass* i_pChild, TClass* i_pParent) const;

	/**
		@brief 検索
		@param i_pIdentifier [in] 識別子
	*/
	template<class TClass> TClass* findProcess(TClass* i_pProcess, const char* i_pIdentifier) const;

	/**
		@brief 消去フラグのたっているプロセスの削除
		@param i_pProcess [in] 基準プロセス
		@return 削除されたものがあったか
	*/
	template<class TClass> bool erase(TClass* i_pProcess) const;

	/**
		@brief プロセスリストの更新
		@param i_pProcess [in] 基準プロセス
	*/
	template<class TArrayClass, class TClass> void updateProcessList(std::vector<TArrayClass>& i_apList, TClass* i_pRoot) const;
};

/**
	@brief	ジョブ管理
*/
class CJobManager	:	public IProcessManager
{
public:
	/**
		@brief コンストラクタ
	*/
	CJobManager();
	
	/**
		@brief デストラクタ
	*/
	virtual ~CJobManager();
	
	/**
		@brief 実行
	*/
	virtual void proc(void);

	/**
		@brief 追加
		@param i_pChild [in] 追加するプロセス
		@param i_pParent [in] 親。nullptrならルートの下
	*/
	void addJob(CJob* i_pChild, CJob* i_pParent = nullptr);

	/**
		@brief 検索
		@param i_pIdentifier [in] 識別子
	*/
	CJob* findJob(const char* i_pIdentifier);
	
private:
	/**
		@brief 更新用スレッド
	*/
	class CProcThread : public IThreadRequest
	{
	public:
		CProcThread(CJob* i_pProcess) : IThreadRequest(), m_pProcess(i_pProcess) {}
		virtual ~CProcThread(){};
		virtual void execute(void) { m_pProcess->updateASync(); }

	private:
		CJob*		m_pProcess;		//!< プロセスポインタ
	};

private:
	std::vector<CProcThread>	m_aThreadList;	//!< 更新用スレッド配列
	CJob						m_Root;			//!< ルートプロセス
};

/**
	@brief	レンダー管理
*/
class CRenderManager	:	public IProcessManager
{
public:
	/**
		@brief コンストラクタ
	*/
	CRenderManager();
	
	/**
		@brief デストラクタ
	*/
	virtual ~CRenderManager();
	
	/**
		@brief 実行
	*/
	virtual void proc(void);

	/**
		@brief 追加
		@param i_pChild [in] 追加するプロセス
		@param i_pParent [in] 親。nullptrならルートの下
	*/
	void addRender(CRender* i_pChild, CRender* i_pParent = nullptr);

	/**
		@brief 検索
		@param i_pIdentifier [in] 識別子
	*/
	CRender* findRender(const char* i_pIdentifier);
	
private:
	/**
		@brief 更新用スレッド
	*/
	class CProcThread : public IThreadRequest
	{
	public:
		CProcThread(CRender* i_pProcess);
		CProcThread(const CProcThread& r) : CProcThread(r.m_pProcess){};
		virtual ~CProcThread();
		virtual void execute(void);
		
		/**
			@brief コマンドリスト適用
		*/
		void executeCommandList(ID3D11DeviceContext* i_pImmediateContext);
		
		/**
			@brief 代入演算子
		*/
		CProcThread& operator =(const CProcThread& src);

	private:
		ID3D11DeviceContext*	m_pContext;		//!< render用のデファードコンテキスト
		ID3D11CommandList*		m_pCommand;		//!< render用のコマンドリスト
		CRender*				m_pProcess;		//!< プロセスポインタ
	};

private:
	std::vector<CProcThread>	m_aThreadList;		//!< 更新用スレッド配列

	CRender						m_Root;				//!< ルートプロセス
};
#endif		//__PROSESS_MANAGER_H__

