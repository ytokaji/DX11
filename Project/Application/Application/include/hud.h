/**
	@file hud.h
	@brief hud�̊Ǘ��A�\��
*/

#pragma once
#ifndef _HUD_H_
#define _HUD_H_

#include "framework/render.h"

class CDXUTDialogResourceManager;
class CDXUTTextHelper;

/**
	@brief hud�̊Ǘ��A�\��
	@note �p�t�H�[�}���X�\����
*/
class CHud	: public CRender
{
public:
	CHud();
	~CHud();
	
	/// �����֐�
	virtual void render(void);

private:
	/// ������
	void init();
	
	/// �I������
	void destroy();

private:	
	CDXUTDialogResourceManager*		m_pDialogResourceManager;	 //!< �_�C�A���O�}�l�[�W��
	CDXUTTextHelper*				m_pTxtHelper;

	// �R�[���o�b�N�̃n���h��
	size_t							m_nResizeHandle;
	size_t							m_nReleaseHandle;
	size_t							m_nMsgProcHandle;
};


#endif		// _HUD_H_