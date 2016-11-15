/**
	@file render.h
	@brief 描画処理規定クラス
*/
#pragma once
#ifndef __RENDER_H__
#define __RENDER_H__

#include "framework/process.h"

/**
	@class CRender
	@brief 処理実行
*/
class CRender : public CProcess<CRender, RENDER_PRIORITY>
{
public:
	/**
		@brief 汎用的に使うようコンストラクター
		@param pszid [in] 識別子
		@param i_fPre [in] 事前処理ファンクタ
		@param i_fRender [in] 描画処理ファンクタ
		@param i_fPost [in] 事後処理ファンクタ
		@param nPriority [in] プライオリティー
	*/
	CRender(const char* i_pszid, RENDER_PRIORITY i_ePriority = RENDER_PRIORITY::DEFAULT)
		:	CRender(i_pszid, []{}, []{}, []{}, i_ePriority)
	{
	}
	CRender(const char* i_pszid,
		std::function<void()> i_fPre, std::function<void()> i_fRender, std::function<void()> i_fPost
			, RENDER_PRIORITY i_ePriority = RENDER_PRIORITY::DEFAULT)
		:	CProcess<CRender,RENDER_PRIORITY>	( i_pszid, i_ePriority )
		,	m_fPre				( i_fPre )
		,	m_fRender			( i_fRender )
		,	m_fPost				( i_fPost )
		,	m_pActiveContext	( nullptr )
	{
	}

	/**
		@brief デストラクター
	*/
	virtual ~CRender()
	{
	}
	
	/**
		@brief	事前処理
		@note	親子階層とプライオリティを考慮した同期で実行
	*/
	virtual void pre(void)	{m_fPre();}

	/**
		@brief	描画処理
		@note	順不同、非同期で実行
	*/
	virtual void render(void)	{ m_fRender(); }
	
	/**
		@brief	事後処理
		@note	親子階層とプライオリティを考慮した同期で実行
	*/
	virtual void post(void)	{m_fPost();}
	
	/**
		@brief	アクティブなコンテキストの設定
	*/
	void setActiveDeviceContext(ID3D11DeviceContext* i_pContext) { m_pActiveContext = i_pContext; }
	
	/**
		@brief	アクティブなコンテキストの取得
	*/
	ID3D11DeviceContext* getActiveDeviceContext() { return m_pActiveContext; }

private:
	const std::function<void()>		m_fPre;				//!< 事前処理
	const std::function<void()>		m_fRender;			//!< 描画処理
	const std::function<void()>		m_fPost;			//!< 事後処理

	ID3D11DeviceContext*			m_pActiveContext;	//!< アクティブなコンテキスト
};


#endif		//__RENDER_H__

