/**
	@file property.h
	@brief �ݒ�
*/

#pragma once
#ifndef __PROPERTY_H__
#define __PROPERTY_H__


/**
	@brief �X�V�W���u�p�v���C�I���e�B
*/
enum class JOB_PRIORITY
{
	MIN = 0,		//!< �ŏ�

	DEFAULT,		//!< �f�t�H���g
};

/**
	@brief �`��W���u�p�v���C�I���e�B
*/
enum class RENDER_PRIORITY
{
	MIN = 0,		//!< �ŏ�
	GRID,			//!< ���_�O���b�h

	DEFAULT,		//!< �f�t�H���g

	HUD,			//!< UI
};

/**
	@brief �E�B���h�E�̃T�C�Y
*/
static const int	WINDOW_W = 640;
static const int	WINDOW_H = 480;

/**
	@brief IProcessManager�ŊǗ��ł��鑍��
*/
static const unsigned int PROCESS_ARRAY_MAX = 512;

/**
	@brief CProcess�̎q�̐�
*/
static const unsigned int PROCESS_CHILD_MAX = 32;


/**
	@brief �����̐ݒ�
*/
#ifdef _DEBUG

	/// �A�T�[�g�̎g�p
	#define _ASSERT_USE 1

	/// �f�o�b�O�o��
	#define _DEBUG_PRINT 1

	/// �R���p�C���ς݃V�F�[�_�[�̎g�p
	#define _PRECOMPILE_SHADER_USE 0

#else

	/// �A�T�[�g�̎g�p
	#define _ASSERT_USE 0

		/// �f�o�b�O�o��
	#define _DEBUG_PRINT 0

	/// �R���p�C���ς݃V�F�[�_�[�̎g�p
	#define _PRECOMPILE_SHADER_USE 1

#endif

#endif		//__PROPERTY_H__