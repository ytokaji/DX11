/**
	@file property.h
	@brief 設定
*/

#pragma once
#ifndef __PROPERTY_H__
#define __PROPERTY_H__


/**
	@brief 更新ジョブ用プライオリティ
*/
enum class JOB_PRIORITY
{
	MIN = 0,		//!< 最小

	DEFAULT,		//!< デフォルト
};

/**
	@brief 描画ジョブ用プライオリティ
*/
enum class RENDER_PRIORITY
{
	MIN = 0,		//!< 最小
	GRID,			//!< 原点グリッド

	DEFAULT,		//!< デフォルト

	HUD,			//!< UI

};

/**
	@brief ウィンドウのサイズ
*/
static const int	WINDOW_W = 1280;
static const int	WINDOW_H = 768;

/**
	@brief IProcessManagerで管理できる総数
*/
static const unsigned int PROCESS_ARRAY_MAX = 512;

/**
	@brief CProcessの子の数
*/
static const unsigned int PROCESS_CHILD_MAX = 32;

/**
@brief デフォルトの入力レイアウトの定義
*/
static const D3D11_INPUT_ELEMENT_DESC DEFAULT_ELEMENT_LAYOUT[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
/**
@brief デフォルトの入力レイアウト数の定義
*/
static const UINT DEFAULT_ELEMENT_LAYOUT_NUM = sizeof(DEFAULT_ELEMENT_LAYOUT) / sizeof(DEFAULT_ELEMENT_LAYOUT[0]);


/**
	@brief 挙動の設定
*/
#ifdef _DEBUG

	/// アサートの使用
	#define _ASSERT_USE 1

	/// デバッグ出力
	#define _DEBUG_PRINT 1

	/// コンパイル済みシェーダーの使用
	#define _PRECOMPILE_SHADER_USE 0

#else

	/// アサートの使用
	#define _ASSERT_USE 0

		/// デバッグ出力
	#define _DEBUG_PRINT 0

	/// コンパイル済みシェーダーの使用
	#define _PRECOMPILE_SHADER_USE 1

#endif

#endif		//__PROPERTY_H__