/**
	@file render.h
	@brief �`�揈���K��N���X
*/
#pragma once
#ifndef __RENDER_H__
#define __RENDER_H__

#include "framework/process.h"

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
		:	Render(id, []{}, []{}, []{}, priority)
	{
	}
	Render(const char* id,
		std::function<void()> i_fPre, std::function<void()> render
			, std::function<void()> post
			, RENDER_PRIORITY priority = RENDER_PRIORITY::DEFAULT)
		:	Process<Render,RENDER_PRIORITY>	( id, priority )
		,	_pre			( i_fPre )
		,	_render			( render )
		,	_post			( post )
		,	_activeContext	( nullptr )
	{
	}

	/**
		@brief �f�X�g���N�^�[
	*/
	virtual ~Render()
	{
	}
	
	/**
		@brief	���O����
		@note	�e�q�K�w�ƃv���C�I���e�B���l�����������Ŏ��s
	*/
	virtual void Pre()	{_pre();}

	/**
		@brief	�`�揈��
		@note	���s���A�񓯊��Ŏ��s
	*/
	virtual void RenderAsync()	{ _render(); }
	
	/**
		@brief	���㏈��
		@note	�e�q�K�w�ƃv���C�I���e�B���l�����������Ŏ��s
	*/
	virtual void Post()	{_post();}
	
	/**
		@brief	�A�N�e�B�u�ȃR���e�L�X�g�̐ݒ�
	*/
	void SetActiveDeviceContext(ID3D11DeviceContext* context) { _activeContext = context; }
	
	/**
		@brief	�A�N�e�B�u�ȃR���e�L�X�g�̎擾
	*/
	ID3D11DeviceContext* GetActiveDeviceContext() { return _activeContext; }

private:
	const std::function<void()>		_pre;			//!< ���O����
	const std::function<void()>		_render;		//!< �`�揈��
	const std::function<void()>		_post;			//!< ���㏈��

	ID3D11DeviceContext*			_activeContext;	//!< �A�N�e�B�u�ȃR���e�L�X�g
};


#endif		//__RENDER_H__

