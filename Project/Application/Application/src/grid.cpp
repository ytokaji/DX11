/**
@file grid.cpp
@brief gridの管理、表示
*/

#include "stdafx.h"

#include "grid.h"
#include "appContext.h"
#include "shader/shader.h"
#include "appContext.h"
#include "framework/renderManager.h"

//---------------------------------------------------------------------
Grid::Grid()
	: _render("Grid", nullptr, std::bind(&Grid::RenderAsync, this), nullptr, RENDER_PRIORITY::GRID)
	, _d3DVertexBuffer(nullptr)
	, _d3DIndexBuffer(nullptr)
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

	// 頂点情報の生成
	const auto start = (SPLIT_NUM*GRID_SIZE)*0.5f;
	const uint16_t size = (SPLIT_NUM + 1) * 2 * 2;
	std::unique_ptr<DefaultVertexData[]> vertexBuffer(new DefaultVertexData[size]);
	std::unique_ptr<uint16_t[]> indexBuff(new uint16_t[size]);

#ifdef TEST
	vertexBuffer[0].pos = DirectX::SimpleMath::Vector4(-1.f, 1.f, 1.f, 1.f);
	vertexBuffer[1].pos = DirectX::SimpleMath::Vector4(1.f, -1.f, 1.f, 1.f);
	vertexBuffer[2].pos = DirectX::SimpleMath::Vector4(1.f, 1.f, -1.f, 1.f);
#else
	for (uint16_t i = 0; i < size; ++i)
	{
		auto x = ((i % 2) == 0 ? -start : start);
		auto z = start - ((((i / 2) % (SPLIT_NUM+1)) * GRID_SIZE));

		vertexBuffer[i].pos = DirectX::SimpleMath::Vector4(x, 0.f, z, 1.f);
//		vertexBuffer[i].color = DirectX::SimpleMath::Color(1.f, 1.f, 1.f, 1.f);
//		vertexBuffer[i].normal = DirectX::SimpleMath::Vector3(0.f, 1.f, 0.f);
		if (i < (SPLIT_NUM + 1) * 2) { std::swap(vertexBuffer[i].pos.x, vertexBuffer[i].pos.z); }
		indexBuff[i] = i;
	}
#endif

	CreateBuffer(&_d3DVertexBuffer, vertexBuffer.get(), sizeof(DefaultVertexData)*size, D3D11_BIND_VERTEX_BUFFER);
	CreateBuffer(&_d3DIndexBuffer, indexBuff.get(), sizeof(uint16_t)*size, D3D11_BIND_INDEX_BUFFER);

	// シェーダーパラメータ適用関数の設定
	auto shader = app->GetShaderManager()->GetShader(ShaderManager::SHADER_TYPE::GRID);
	shader->RegistShaderParamSetFunc("g_mWorldViewProjection", [](ShaderValueBase* x)
	{
		DirectX::SimpleMath::Matrix world = AppContext::GetInstance()->GetCameraWorldMatrix();
		DirectX::SimpleMath::Matrix view = AppContext::GetInstance()->GetViewMatrix();
		DirectX::SimpleMath::Matrix proj = AppContext::GetInstance()->GetProjMatrix();
		DirectX::SimpleMath::Matrix worldViewPorj = world * view * proj;
		reinterpret_cast<ShaderValueConstantBuffer*>(x)->SetBuffer(worldViewPorj);
	});

	// 登録
	AppContext::GetInstance()->GetRenderManager()->AddRender(&_render);
}

//---------------------------------------------------------------------
void Grid::CreateBuffer(ID3D11Buffer** d3dBuffer, void* pData, size_t size, D3D11_BIND_FLAG BindFlag)
{
	_ASSERT(pData != nullptr);
	_ASSERT(size != 0);

	// バッファの設定
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = size;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = BindFlag;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// サブリソースの設定
	D3D11_SUBRESOURCE_DATA srd;
	srd.pSysMem = pData;
	srd.SysMemPitch = 0;
	srd.SysMemSlicePitch = 0;

	// バッファを作成する
	HRESULT hr = E_FAIL;
	_RET_CHECK_ASSERT(AppContext::GetInstance()->GetD3D11Device()->CreateBuffer(&bd, &srd, d3dBuffer));
}

//---------------------------------------------------------------------
void Grid::Destroy()
{
	SAFE_RELEASE(_d3DVertexBuffer);
	SAFE_RELEASE(_d3DIndexBuffer);
}

//---------------------------------------------------------------------
void Grid::RenderAsync()
{
	auto app = AppContext::GetInstance();
	auto context = _render.GetDeviceContext();

	auto shader = app->GetShaderManager()->GetShader(ShaderManager::SHADER_TYPE::GRID);
	shader->Apply(context);

#ifdef TEST
	// ラスタライザーステートの設定に必要なパラメータを設定
	D3D11_RASTERIZER_DESC rastDesc;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	rastDesc.FrontCounterClockwise = TRUE;
	rastDesc.DepthBias = 0;
	rastDesc.DepthBiasClamp = 0.f;
	rastDesc.SlopeScaledDepthBias = 0.f;
	rastDesc.DepthClipEnable = FALSE;
	rastDesc.ScissorEnable = TRUE;
	rastDesc.MultisampleEnable = FALSE;
	rastDesc.AntialiasedLineEnable = FALSE;
//	rastDesc.CullMode = D3D11_CULL_FRONT;
	rastDesc.CullMode = D3D11_CULL_NONE;

	ID3D11RasterizerState * pState;
	app->GetD3D11Device()->CreateRasterizerState(&rastDesc, &pState);
//	context->RSSetState(pState);
	pState->Release();

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(DefaultVertexData), offset = 0;
	context->IASetVertexBuffers(0, 1, &_d3DVertexBuffer, &stride, &offset);

	context->Draw(3, 0);
#else
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	UINT stride = sizeof(DefaultVertexData), offset = 0;
	context->IASetVertexBuffers(0, 1, &_d3DVertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(_d3DIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	context->DrawIndexed((SPLIT_NUM + 1) * 2 * 2, 0, 0);
#endif
}



