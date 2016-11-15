/**
	@file define_type.h
	@brief マクロ定義
*/


#pragma once
#ifndef _DEFINE_TYPE_H_
#define _DEFINE_TYPE_H_

#include "assert.h"

/// メモリ開放
#ifdef SAFE_DELETE
#undef SAFE_DELETE
#endif
#ifdef SAFE_DELETE_ARRAY
#undef SAFE_DELETE_ARRAY
#endif
#ifdef SAFE_RELEASE
#undef SAFE_RELEASE
#endif

#define SAFE_DELETE(p)			if( (p) != nullptr) { delete (p); (p) = nullptr; }
#define SAFE_DELETE_ARRAY(p)	if( (p) != nullptr) { delete [] (p); (p) = nullptr; }
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=nullptr; } }
#define SAFE_TERMINATE(p)      { if (p) { (p)->terminate(); (p)=nullptr; } }


/// 配列数の計算
#define NUM_OF( staticArray )   (sizeof(staticArray)/sizeof(staticArray[0]))

#ifdef _PRINT
#undef _PRINT
#endif
#ifdef _WARNING
#undef _WARNING
#endif
#ifdef _ASSERT
#undef _ASSERT
#endif

/// アサート
#if _ASSERT_USE
	#ifdef NDEBUG
		#undef NDEBUG
		#define _ASSERT(expr)	{ assert(expr); }
		#define NDEBUG
	#else
		#define _ASSERT(expr)	{ assert(expr); }
	#endif
#else
	#define _ASSERT(expr)	{}
#endif

/// デバッグ出力
#if _DEBUG_PRINT
	/// デバッガログ出力
	static void message(const char* i_szFmt, ...){
		char buff[2048];
		memset( buff, 0, sizeof(buff) );
		va_list args;

		va_start(args, i_szFmt);
		vsnprintf_s(buff, sizeof(buff), _TRUNCATE, i_szFmt, args);
		va_end(args);

		::OutputDebugStringA(buff);
	}
	#define _PRINT(fomat, ...) { message(fomat, __VA_ARGS__); }
#else
	#define _PRINT(fomat, ...) {}
#endif

/// 静的アサート
#define STATIC_ASSERT( expr ) { static_assert( expr , ""); }
#define STATIC_ASSERT_MESS( expr, mess ) { static_assert( expr, mess ); }

/// 戻り値のチェック
#define _RET_CHECK(func)										\
{																\
	hr = (func);												\
	if( FAILED(hr) )											\
	{															\
		char buff[512];											\
		sprintf_s( buff, 512, "%s : %d", #func, (int)(hr) );	\
		_PRINT( 0, buff );										\
	}															\
}

#define _RET_CHECK_ASSERT(func)										\
{																	\
	hr = (func);													\
	if( FAILED(hr) )												\
	{																\
		char buff[512];												\
		sprintf_s( buff, 512, "%s : 0x%x\n", #func, (int)(hr) );	\
		_PRINT( buff );												\
		_ASSERT(false);												\
	}																\
}

#endif		//_DEFINE_TYPE_H_



