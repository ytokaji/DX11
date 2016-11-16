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
class CGrid	: public Render
{
public:
	CGrid();
	~CGrid();
	
	/// 処理関数
	virtual void RenderAsync(void);

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
	/// 初期化
	void Init();
	
	/// 終了処理
	void destroy();

private:
	static const unsigned int SPLIT_X_NUM = 10;
	static const unsigned int SPLIT_Z_NUM = 10;

	ID3D11Buffer*		m_pD3DBuffer;		// D3D11バッファ
};


#endif		// _GRID_H_

