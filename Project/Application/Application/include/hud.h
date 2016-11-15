/**
	@file hud.h
	@brief hudの管理、表示
*/

#pragma once
#ifndef _HUD_H_
#define _HUD_H_

#include "framework/render.h"

class CDXUTDialogResourceManager;
class CDXUTTextHelper;

/**
	@brief hudの管理、表示
	@note パフォーマンス表示等
*/
class CHud	: public CRender
{
public:
	CHud();
	~CHud();
	
	/// 処理関数
	virtual void render(void);

private:
	/// 初期化
	void init();
	
	/// 終了処理
	void destroy();

private:	
	CDXUTDialogResourceManager*		m_pDialogResourceManager;	 //!< ダイアログマネージャ
	CDXUTTextHelper*				m_pTxtHelper;

	// コールバックのハンドル
	size_t							m_nResizeHandle;
	size_t							m_nReleaseHandle;
	size_t							m_nMsgProcHandle;
};


#endif		// _HUD_H_