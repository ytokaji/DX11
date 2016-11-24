/**
	@file grid.cpp
	@brief grid�̊Ǘ��A�\��
*/

#include "stdafx.h"

#include "grid.h"
#include "appContext.h"


//---------------------------------------------------------------------
Grid::Grid()
	: _render("Grid", nullptr, std::bind(&Grid::RenderAsync, this), nullptr, RENDER_PRIORITY::GRID)
	, _d3DBuffer(nullptr)
{
	Init();
}

//---------------------------------------------------------------------
Grid::~Grid()
{
	Destroy();
}

//---------------------------------------------------------------------
void Grid::Init()
{
	AppContext* app = AppContext::GetInstance();
	ID3D11Device* device = app->GetD3D11Device();
	HRESULT hr = E_FAIL;

	// �������̊m��
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.ByteWidth = (((SPLIT_X_NUM + 1) << 1) + ((SPLIT_Z_NUM + 1) << 1)) * sizeof(SVertexData);
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_RET_CHECK_ASSERT(device->CreateBuffer(&bd, NULL, &_d3DBuffer));
	/*
	// ���̓��C�A�E�g�𐶐�
	hr = app->GetD3D11Device()->CreateInputLayout(
		DEFAULT_ELEMENT_LAYOUT,
		DEFAULT_ELEMENT_LAYOUT_NUM,
		pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),
		&gDemoApp.pVertexLayout);
	pVSBlob->Release();
	pVSBlob = NULL;
	if (FAILED(hr))
	{
		return hr;
	}

	// ���̓A�Z���u���ɓ��̓��C�A�E�g��ݒ�
	gDemoApp.pDeviceContext->IASetInputLayout(gDemoApp.pVertexLayout);
	*/
}


//---------------------------------------------------------------------
void Grid::Destroy()
{
	SAFE_RELEASE(_d3DBuffer);
}

//---------------------------------------------------------------------
void Grid::RenderAsync()
{
}



