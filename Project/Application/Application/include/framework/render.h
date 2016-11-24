/**
	@file render.h
	@brief �`�揈���K��N���X
*/
#pragma once
#ifndef __RENDER_H__
#define __RENDER_H__

#include "framework/process.h"
#include "framework/thread.h"

/**
	@class Render
	@brief �������s
*/
class Render : public Process<Render, RENDER_PRIORITY>
{
public:
	/**
		@brief �ėp�I�Ɏg���悤�R���X�g���N�^�[
		@param pszid [in] ���ʎq
		@param i_fPre [in] ���O�����t�@���N�^
		@param render [in] �`�揈���t�@���N�^
		@param post [in] ���㏈���t�@���N�^
		@param nPriority [in] �v���C�I���e�B�[
	*/
	Render(const char* id, RENDER_PRIORITY priority = RENDER_PRIORITY::DEFAULT)
		: Render(id, nullptr, nullptr, nullptr, priority)
	{
	}
	Render(const char* id
		, std::function<void()> pre
		, std::function<void()> render
		, std::function<void()> post
		, RENDER_PRIORITY priority = RENDER_PRIORITY::DEFAULT);

	/**
		@brief �f�X�g���N�^�[
	*/
	virtual ~Render();

	/**
		@brief	���O����
		@note	�e�q�K�w�ƃv���C�I���e�B���l�����������Ŏ��s
	*/
	virtual void Pre()	{ if (_pre){ _pre(); } }

	/**
		@brief	�`�揈��
		@note	���s���A�񓯊��Ŏ��s
	*/
	virtual void RenderAsync()	{ if (_render) { _render(); } }
	
	/**
		@brief	���㏈��
		@note	�e�q�K�w�ƃv���C�I���e�B���l�����������Ŏ��s
	*/
	virtual void Post()	{ if(_post) { _post(); } }
	
	/**
		@brief	�R���e�L�X�g�̎擾
	*/
	ID3D11DeviceContext* GetDeviceContext() { return _context; }

private:
	const std::function<void()>		_pre;			//!< ���O����
	const std::function<void()>		_render;		//!< �`�揈��
	const std::function<void()>		_post;			//!< ���㏈��

	ID3D11DeviceContext*			_context;		//!< RenderAsync�p�̃f�t�@�[�h�R���e�L�X�g
};


#endif		//__RENDER_H__

