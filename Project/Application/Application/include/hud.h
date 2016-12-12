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
class Hud
{
public:
	Hud();
	~Hud();

protected:
	/**
		@brief	初期化
	*/
	void Init();

	/// 処理関数
	void RenderAsync();

	/// 終了処理
	void Destroy();

private:	
	CDXUTDialogResourceManager*		_dialogResourceManager;	 //!< ダイアログマネージャ
	CDXUTTextHelper*				_txtHelper;
	RenderProcess							_render;

	// コールバックのハンドル
	uintptr_t						_resizeHandle;
	uintptr_t						_releaseHandle;
	uintptr_t						_msgProcHandle;
};


#endif		// _HUD_H_