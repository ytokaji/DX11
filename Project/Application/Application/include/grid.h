/**
	@file grid.h
	@brief gridの管理、表示
*/

#pragma once
#ifndef _GRID_H_
#define _GRID_H_

#include "framework/render.h"


/**
	@brief gridの管理、表示
*/
class Grid
{
public:
	Grid();
	~Grid();

protected:
	/// 処理関数
	void RenderAsync(void);

	/// 初期化
	void Init();

	/// 終了処理
	void Destroy();

	/// バッファ作成
	void CreateBuffer(ID3D11Buffer** pBuffer, void* pData, size_t size, D3D11_BIND_FLAG BindFlag);

private:
	static const uint32_t SPLIT_NUM = 10;
	static const uint32_t GRID_SIZE = 1;

	RenderProcess					_render;
	ID3D11Buffer*					_d3DVertexBuffer;		// D3D11バッファ
	ID3D11Buffer*					_d3DIndexBuffer;		// D3D11バッファ
//	std::vector<DefaultVertexData>	_vertexBuffer;			// 頂点情報
};


#endif		// _GRID_H_

