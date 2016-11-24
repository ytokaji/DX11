/**
	@file render.h
	@brief �`�揈���K��N���X
*/
#pragma once
#ifndef __RENDER_H__
#define __RENDER_H__

#include "framework/processManager.h"
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
		: Render(id, priority, nullptr, nullptr, nullptr, nullptr)
	{
	}
	Render(const char* id
			, RENDER_PRIORITY priority = RENDER_PRIORITY::DEFAULT
			, std::function<void()> pre = nullptr
			, std::function<void()> render = nullptr
			, std::function<void()> post = nullptr
			, std::function<void()> destory = nullptr)
		:	Process<Render,RENDER_PRIORITY>	( id, priority )
		,	_pre			( pre )
		,	_render			( render )
		,	_post			( post )
		,	_destroy		( destory )
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
		@brief	������
		@note	device context���o������ɌĂ΂��
	*/
	virtual void Init() {};

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
		@brief	�A�N�e�B�u�ȃR���e�L�X�g�̐ݒ�
	*/
	void SetActiveDeviceContext(ID3D11DeviceContext* context) { _activeContext = context; }
	
	/**
		@brief	�A�N�e�B�u�ȃR���e�L�X�g�̎擾
	*/
	ID3D11DeviceContext* GetActiveDeviceContext() { return _activeContext; }

protected:
	/**
	@brief	�폜����
	@note	Destroy����Ă΂��
	*/
	virtual void OnDestroy(){ _destroy(); };

private:
	const std::function<void()>		_pre;			//!< ���O����
	const std::function<void()>		_render;		//!< �`�揈��
	const std::function<void()>		_post;			//!< ���㏈��
	const std::function<void()>		_destroy;		//!< �I������

	ID3D11DeviceContext*			_activeContext;	//!< �A�N�e�B�u�ȃR���e�L�X�g
};


#endif		//__RENDER_H__

