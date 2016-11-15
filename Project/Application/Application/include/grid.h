/**
	@file grid.h
	@brief grid�̊Ǘ��A�\��
*/

#pragma once
#ifndef _GRID_H_
#define _GRID_H_

#include "framework/render.h"


/**
	@brief grid�̊Ǘ��A�\��
*/
class CGrid	: public CRender
{
public:
	CGrid();
	~CGrid();
	
	/// �����֐�
	virtual void render(void);

private:
	/*
		@brief 1���_�̏��
	*/
	struct SVertexData
	{
		D3DXVECTOR4		pos;
		D3DXCOLOR		color;
	};
private:
	/// ������
	void init();
	
	/// �I������
	void destroy();

private:
	static const unsigned int SPLIT_X_NUM = 10;
	static const unsigned int SPLIT_Z_NUM = 10;

	ID3D11Buffer*		m_pD3DBuffer;		// D3D11�o�b�t�@
};


#endif		// _GRID_H_

