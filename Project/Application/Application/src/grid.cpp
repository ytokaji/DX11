/**
	@file grid.cpp
	@brief gridの管理、表示
*/

#include "stdafx.h"

#include "grid.h"
#include "appContext.h"

//---------------------------------------------------------------------
// 入力レイアウトの定義
D3D11_INPUT_ELEMENT_DESC layout[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//---------------------------------------------------------------------
CGrid::CGrid()
	: CRender("CGrid", RENDER_PRIORITY::GRID)
	, m_pD3DBuffer(nullptr)
{
	init();
}

//---------------------------------------------------------------------
CGrid::~CGrid()
{
	destroy();
}

//---------------------------------------------------------------------
void CGrid::init()
{
	AppContext* pApp = AppContext::GetInstance();
	ID3D11Device* pDevice = pApp->GetD3D11Device();
	HRESULT hr = E_FAIL;

	// メモリの確保
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.ByteWidth = (((SPLIT_X_NUM + 1) << 1) + ((SPLIT_Z_NUM + 1) << 1)) * sizeof(SVertexData);
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_RET_CHECK_ASSERT(pDevice->CreateBuffer(&bd, NULL, &m_pD3DBuffer));

	// 入力レイアウトの定義
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	/*
	// 入力レイアウトを生成
	hr = gDemoApp.pDevice->CreateInputLayout(
		layout,
		numElements,
		pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),
		&gDemoApp.pVertexLayout);
	pVSBlob->Release();
	pVSBlob = NULL;
	if (FAILED(hr))
	{
		return hr;
	}

	// 入力アセンブラに入力レイアウトを設定
	gDemoApp.pDeviceContext->IASetInputLayout(gDemoApp.pVertexLayout);
	*/
}


//---------------------------------------------------------------------
void CGrid::destroy()
{
	SAFE_RELEASE(m_pD3DBuffer);
}

//---------------------------------------------------------------------
void CGrid::render()
{
}



