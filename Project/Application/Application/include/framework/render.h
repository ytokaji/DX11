/**
	@file render.h
	@brief 描画処理規定クラス
*/
#pragma once
#ifndef __RENDER_H__
#define __RENDER_H__

#include "framework/process.h"

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
		:	Render(id, []{}, []{}, []{}, priority)
	{
	}
	Render(const char* id,
		std::function<void()> i_fPre, std::function<void()> render
			, std::function<void()> post
			, RENDER_PRIORITY priority = RENDER_PRIORITY::DEFAULT)
		:	Process<Render,RENDER_PRIORITY>	( id, priority )
		,	_pre			( i_fPre )
		,	_render			( render )
		,	_post			( post )
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
		@brief	事前処理
		@note	親子階層とプライオリティを考慮した同期で実行
	*/
	virtual void Pre()	{_pre();}

	/**
		@brief	描画処理
		@note	順不同、非同期で実行
	*/
	virtual void RenderAsync()	{ _render(); }
	
	/**
		@brief	事後処理
		@note	親子階層とプライオリティを考慮した同期で実行
	*/
	virtual void Post()	{_post();}
	
	/**
		@brief	アクティブなコンテキストの設定
	*/
	void SetActiveDeviceContext(ID3D11DeviceContext* context) { _activeContext = context; }
	
	/**
		@brief	アクティブなコンテキストの取得
	*/
	ID3D11DeviceContext* GetActiveDeviceContext() { return _activeContext; }

private:
	const std::function<void()>		_pre;			//!< 事前処理
	const std::function<void()>		_render;		//!< 描画処理
	const std::function<void()>		_post;			//!< 事後処理

	ID3D11DeviceContext*			_activeContext;	//!< アクティブなコンテキスト
};


#endif		//__RENDER_H__

