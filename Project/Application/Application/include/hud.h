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
class hud
{
public:
	hud();
	~hud();
	
	/**
		@brief	������
		@note	device context���o������ɌĂ΂��
	*/
	void Init();

protected:
	/// �����֐�
	void RenderAsync();

	/// �I������
	void OnDestroy();

private:	
	CDXUTDialogResourceManager*		_dialogResourceManager;	 //!< �_�C�A���O�}�l�[�W��
	CDXUTTextHelper*				_txtHelper;
	Render							_render;

	// �R�[���o�b�N�̃n���h��
	uintptr_t						_resizeHandle;
	uintptr_t						_releaseHandle;
	uintptr_t						_msgProcHandle;
};


#endif		// _HUD_H_