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
class Grid
{
public:
	Grid();
	~Grid();

protected:
	/// �����֐�
	void RenderAsync(void);

	/// ������
	void Init();

	/// �I������
	void Destroy();

private:
	/*
		@brief 1���_�̏��
	*/
	struct SVertexData
	{
		DirectX::SimpleMath::Vector4	pos;
		DirectX::SimpleMath::Color		color;
	};

private:
	static const unsigned int SPLIT_X_NUM = 10;
	static const unsigned int SPLIT_Z_NUM = 10;

	Render				_render;
	ID3D11Buffer*		_d3DBuffer;		// D3D11�o�b�t�@
};


#endif		// _GRID_H_

