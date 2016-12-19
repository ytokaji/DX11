/**
	@file renderManager.h
	@brief 描画処理規定クラス
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
@brief	レンダー管理
*/
class RenderManager : public ProcessManagerBase
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
	void AddRender(RenderProcess* child, RenderProcess* parent = nullptr);

	/**
	@brief 検索
	@param identifier [in] 識別子
	*/
	RenderProcess* FindRender(const char* identifier);

private:
	/**
	@brief 更新用スレッド
	*/
	class ProcThread : public ThreadRequestBase
	{
	public:
		ProcThread(RenderProcess* i_pProcess);
		ProcThread(const ProcThread& r) : ProcThread(r._process){};
		virtual ~ProcThread();
		virtual void Execute(void);

		/**
		@brief コマンドリスト適用
		*/
		void ExecuteCommandList(ID3D11DeviceContext* immediateContext);

	private:
		/**
		@brief 代入演算子
		*/
		ProcThread& operator =(const ProcThread&){};

	private:
		ID3D11CommandList*		_command;		//!< RenderAsync用のコマンドリスト
		RenderProcess*			_process;		//!< プロセスポインタ
	};

private:
	std::vector<ProcThread*>	_threadList;	//!< 更新用スレッド配列
	RenderProcess				_root;			//!< ルートプロセス
};


#endif		//__RENDER_MANAGER_H__

