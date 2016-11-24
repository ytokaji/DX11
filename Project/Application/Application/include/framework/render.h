/**
	@file render.h
	@brief 描画処理規定クラス
*/
#pragma once
#ifndef __RENDER_H__
#define __RENDER_H__

#include "framework/processManager.h"
#include "framework/process.h"
#include "framework/thread.h"

/**
	@class Render
	@brief 処理実行
*/
class Render : public Process<Render, RENDER_PRIORITY>
{
public:
	/**
		@brief 汎用的に使うようコンストラクター
		@param pszid [in] 識別子
		@param i_fPre [in] 事前処理ファンクタ
		@param render [in] 描画処理ファンクタ
		@param post [in] 事後処理ファンクタ
		@param nPriority [in] プライオリティー
	*/
	Render(const char* id, RENDER_PRIORITY priority = RENDER_PRIORITY::DEFAULT)
		: Render(id, priority, nullptr, nullptr, nullptr, nullptr)
	{
	}
	Render(const char* id
			, RENDER_PRIORITY priority = RENDER_PRIORITY::DEFAULT
			, std::function<void()> pre = nullptr
			, std::function<void()> render = nullptr
			, std::function<void()> post = nullptr
			, std::function<void()> destory = nullptr)
		:	Process<Render,RENDER_PRIORITY>	( id, priority )
		,	_pre			( pre )
		,	_render			( render )
		,	_post			( post )
		,	_destroy		( destory )
		,	_activeContext	( nullptr )
	{
	}

	/**
		@brief デストラクター
	*/
	virtual ~Render()
	{
	}

	/**
		@brief	初期化
		@note	device contextが出来た後に呼ばれる
	*/
	virtual void Init() {};

	/**
		@brief	事前処理
		@note	親子階層とプライオリティを考慮した同期で実行
	*/
	virtual void Pre()	{ if (_pre){ _pre(); } }

	/**
		@brief	描画処理
		@note	順不同、非同期で実行
	*/
	virtual void RenderAsync()	{ if (_render) { _render(); } }
	
	/**
		@brief	事後処理
		@note	親子階層とプライオリティを考慮した同期で実行
	*/
	virtual void Post()	{ if(_post) { _post(); } }
	
	/**
		@brief	アクティブなコンテキストの設定
	*/
	void SetActiveDeviceContext(ID3D11DeviceContext* context) { _activeContext = context; }
	
	/**
		@brief	アクティブなコンテキストの取得
	*/
	ID3D11DeviceContext* GetActiveDeviceContext() { return _activeContext; }

protected:
	/**
	@brief	削除処理
	@note	Destroyから呼ばれる
	*/
	virtual void OnDestroy(){ _destroy(); };

private:
	const std::function<void()>		_pre;			//!< 事前処理
	const std::function<void()>		_render;		//!< 描画処理
	const std::function<void()>		_post;			//!< 事後処理
	const std::function<void()>		_destroy;		//!< 終了処理

	ID3D11DeviceContext*			_activeContext;	//!< アクティブなコンテキスト
};


#endif		//__RENDER_H__

