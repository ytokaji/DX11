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
static const int	WINDOW_W = 640;
static const int	WINDOW_H = 480;

/**
	@brief IProcessManagerで管理できる総数
*/
static const unsigned int PROCESS_ARRAY_MAX = 512;

/**
	@brief CProcessの子の数
*/
static const unsigned int PROCESS_CHILD_MAX = 32;


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