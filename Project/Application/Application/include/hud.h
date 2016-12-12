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
class Hud
{
public:
	Hud();
	~Hud();

protected:
	/**
		@brief	������
	*/
	void Init();

	/// �����֐�
	void RenderAsync();

	/// �I������
	void Destroy();

private:	
	CDXUTDialogResourceManager*		_dialogResourceManager;	 //!< �_�C�A���O�}�l�[�W��
	CDXUTTextHelper*				_txtHelper;
	RenderProcess							_render;

	// �R�[���o�b�N�̃n���h��
	uintptr_t						_resizeHandle;
	uintptr_t						_releaseHandle;
	uintptr_t						_msgProcHandle;
};


#endif		// _HUD_H_