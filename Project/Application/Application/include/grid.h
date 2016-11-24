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

private:
	/*
		@brief 1頂点の情報
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
	ID3D11Buffer*		_d3DBuffer;		// D3D11バッファ
};


#endif		// _GRID_H_

