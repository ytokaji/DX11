// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once


#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>

// C �����^�C�� �w�b�_�[ �t�@�C��
#include <stdlib.h>
#include <new.h>      // for placement new
#include <tchar.h>
#include <stdio.h>
#include <math.h>

// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă��������B
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
#include "DXUT11/Core/DXUT.h"
#include "DXUT11/Optional/DXUTgui.h"
#include "DXUT11/Optional/DXUTcamera.h"
#include "DXUT11/Optional/DXUTsettingsdlg.h"
#include "DXUT11/Optional/SDKmisc.h"
#include "DirectXTK/Inc/SimpleMath.h"

// other
#include "property.h"
#include "define_type.h"

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
