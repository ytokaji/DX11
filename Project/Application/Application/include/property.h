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
static const int	WINDOW_W = 1280;
static const int	WINDOW_H = 768;

/**
	@brief IProcessManager�ŊǗ��ł��鑍��
*/
static const unsigned int PROCESS_ARRAY_MAX = 512;

/**
	@brief CProcess�̎q�̐�
*/
static const unsigned int PROCESS_CHILD_MAX = 32;

/**
@brief �f�t�H���g�̓��̓��C�A�E�g�̒�`
*/
static const D3D11_INPUT_ELEMENT_DESC DEFAULT_ELEMENT_LAYOUT[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
/**
@brief �f�t�H���g�̓��̓��C�A�E�g���̒�`
*/
static const UINT DEFAULT_ELEMENT_LAYOUT_NUM = sizeof(DEFAULT_ELEMENT_LAYOUT) / sizeof(DEFAULT_ELEMENT_LAYOUT[0]);

/*
@brief 1���_�̏��
*/
struct DefaultVertexData
{
	DirectX::SimpleMath::Vector4	pos;
/*	DirectX::SimpleMath::Color		color;
	DirectX::SimpleMath::Vector3	normal;
	DirectX::SimpleMath::Vector2	uv;
	uint8_t							pad[3*4];
*/
};
static_assert(sizeof(DefaultVertexData) % 16 == 0, "");

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