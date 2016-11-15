// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once


#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <new.h>      // for placement new
#include <tchar.h>
#include <stdio.h>
#include <math.h>

// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#include <vector>
#include <bitset>
#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <array>
#include <tuple>
#include <map>
#include <memory>

// directx
#include <d3dcompiler.h>

// external libraty
#pragma warning( push )
#pragma warning(disable : 4100)
#include <CppLinq/cpplinq.hpp>
#pragma warning( pop )

// other
#include "property.h"
#include "define_type.h"
#include "util.h"
#include "Core/DXUT.h"
