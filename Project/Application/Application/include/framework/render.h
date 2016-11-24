/**
	@file render.h
	@brief 描画処理規定クラス
*/
#pragma once
#ifndef __RENDER_H__
#define __RENDER_H__

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
		: Render(id, nullptr, nullptr, nullptr, priority)
	{
	}
	Render(const char* id
		, std::function<void()> pre
		, std::function<void()> render
		, std::function<void()> post
		, RENDER_PRIORITY priority = RENDER_PRIORITY::DEFAULT);

	/**
		@brief デストラクター
	*/
	virtual ~Render();

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
		@brief	コンテキストの取得
	*/
	ID3D11DeviceContext* GetDeviceContext() { return _context; }

private:
	const std::function<void()>		_pre;			//!< 事前処理
	const std::function<void()>		_render;		//!< 描画処理
	const std::function<void()>		_post;			//!< 事後処理

	ID3D11DeviceContext*			_context;		//!< RenderAsync用のデファードコンテキスト
};


#endif		//__RENDER_H__

