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

	/// �o�b�t�@�쐬
	void CreateBuffer(ID3D11Buffer** pBuffer, void* pData, size_t size, D3D11_BIND_FLAG BindFlag);

private:
	static const uint32_t SPLIT_NUM = 10;
	static const uint32_t GRID_SIZE = 1;

	RenderProcess					_render;
	ID3D11Buffer*					_d3DVertexBuffer;		// D3D11�o�b�t�@
	ID3D11Buffer*					_d3DIndexBuffer;		// D3D11�o�b�t�@
//	std::vector<DefaultVertexData>	_vertexBuffer;			// ���_���
};


#endif		// _GRID_H_

