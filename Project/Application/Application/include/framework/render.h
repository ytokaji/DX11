/**
	@file render.h
	@brief �`�揈���K��N���X
*/
#pragma once
#ifndef __RENDER_H__
#define __RENDER_H__

#include "framework/process.h"

/**
	@class CRender
	@brief �������s
*/
class CRender : public CProcess<CRender, RENDER_PRIORITY>
{
public:
	/**
		@brief �ėp�I�Ɏg���悤�R���X�g���N�^�[
		@param pszid [in] ���ʎq
		@param i_fPre [in] ���O�����t�@���N�^
		@param i_fRender [in] �`�揈���t�@���N�^
		@param i_fPost [in] ���㏈���t�@���N�^
		@param nPriority [in] �v���C�I���e�B�[
	*/
	CRender(const char* i_pszid, RENDER_PRIORITY i_ePriority = RENDER_PRIORITY::DEFAULT)
		:	CRender(i_pszid, []{}, []{}, []{}, i_ePriority)
	{
	}
	CRender(const char* i_pszid,
		std::function<void()> i_fPre, std::function<void()> i_fRender, std::function<void()> i_fPost
			, RENDER_PRIORITY i_ePriority = RENDER_PRIORITY::DEFAULT)
		:	CProcess<CRender,RENDER_PRIORITY>	( i_pszid, i_ePriority )
		,	m_fPre				( i_fPre )
		,	m_fRender			( i_fRender )
		,	m_fPost				( i_fPost )
		,	m_pActiveContext	( nullptr )
	{
	}

	/**
		@brief �f�X�g���N�^�[
	*/
	virtual ~CRender()
	{
	}
	
	/**
		@brief	���O����
		@note	�e�q�K�w�ƃv���C�I���e�B���l�����������Ŏ��s
	*/
	virtual void pre(void)	{m_fPre();}

	/**
		@brief	�`�揈��
		@note	���s���A�񓯊��Ŏ��s
	*/
	virtual void render(void)	{ m_fRender(); }
	
	/**
		@brief	���㏈��
		@note	�e�q�K�w�ƃv���C�I���e�B���l�����������Ŏ��s
	*/
	virtual void post(void)	{m_fPost();}
	
	/**
		@brief	�A�N�e�B�u�ȃR���e�L�X�g�̐ݒ�
	*/
	void setActiveDeviceContext(ID3D11DeviceContext* i_pContext) { m_pActiveContext = i_pContext; }
	
	/**
		@brief	�A�N�e�B�u�ȃR���e�L�X�g�̎擾
	*/
	ID3D11DeviceContext* getActiveDeviceContext() { return m_pActiveContext; }

private:
	const std::function<void()>		m_fPre;				//!< ���O����
	const std::function<void()>		m_fRender;			//!< �`�揈��
	const std::function<void()>		m_fPost;			//!< ���㏈��

	ID3D11DeviceContext*			m_pActiveContext;	//!< �A�N�e�B�u�ȃR���e�L�X�g
};


#endif		//__RENDER_H__

