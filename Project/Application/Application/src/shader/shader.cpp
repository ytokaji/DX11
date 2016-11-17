/**
	@file shader.h
	@brief シェーダファイル
*/


#include "stdafx.h"
#include "shader/shader.h"
#include "appContext.h"
/*
#include "shader/shaderManager.h"
#include "shader/shaderValue.h"
*/
//---------------------------------------------------------------------
Shader::Shader()
	: _layout(nullptr)
{
}

//---------------------------------------------------------------------
Shader::~Shader()
{
	SAFE_RELEASE(_layout);
}

#if !_PRECOMPILE_SHADER_USE
//---------------------------------------------------------------------
bool Shader::CompileInitShader(wchar_t* fileName, char* shaderProfile, char* functionName, eTYPE type)
{
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#else
	dwShaderFlags |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif

	HRESULT hr;

	// コンパイル
	ID3DBlob *pEffectBlob = 0, *pErrorBlob = 0;
	hr = D3DCompileFromFile(fileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, functionName, shaderProfile, dwShaderFlags, 0, &pEffectBlob, &pErrorBlob);

	// エラー時処理
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL){ OutputDebugStringA((char*)pErrorBlob->GetBufferPointer()); }
		SAFE_RELEASE(pErrorBlob);

		_ASSERT(0);
		return false;
	}
	SAFE_RELEASE(pErrorBlob);

	// 初期化処理
	bool bRet = InitShader(pEffectBlob->GetBufferPointer(), pEffectBlob->GetBufferSize(), type);
	SAFE_RELEASE(pEffectBlob);

	return bRet;
}
#endif

//---------------------------------------------------------------------
bool Shader::InitShader(const void* buff, size_t size, eTYPE type)
{
	typedef bool (Shader::*ProcFunc)(const void*, size_t);
	static const ProcFunc sc_aInitFunc[] =
	{
		&Shader::InitShaderVertex,
		&Shader::InitShaderPixel,
		&Shader::InitShaderHull,
		&Shader::InitShaderDomain,
		&Shader::InitShaderGeometry,
		&Shader::InitShaderCompute,
	};
	STATIC_ASSERT(NUM_OF(sc_aInitFunc) == (uint8_t)eTYPE::MAX);

	_shadarData[(uint8_t)type] = ShaderData();

	// シェーダー作成
	bool ret = (this->*sc_aInitFunc[(uint8_t)type])(buff, size);
	if (ret == false) { return false; }

	// シェーダーリフレクションインターフェース取得
	HRESULT hr;
	_RET_CHECK_ASSERT(D3DReflect(buff, size, IID_ID3D11ShaderReflection, (void**)&_shadarData[(uint8_t)type]._reflection));

	setupParameter(type);

	return true;
}

//---------------------------------------------------------------------
bool Shader::InitShaderVertex(const void* buff, size_t size)
{
	ID3D11Device* pDevice = AppContext::GetInstance()->GetD3D11Device();
	HRESULT hr;

	// シェーダ作成
	_RET_CHECK_ASSERT(pDevice->CreateVertexShader(buff, size, NULL, &_shadarData[(uint8_t)eTYPE::VS]._shader._vertex));
	if (FAILED(hr)) return false;
	/*
	// InputLayoutの作成
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	_RET_CHECK_ASSERT(pDevice->CreateInputLayout(layout, ARRAYSIZE(layout), buff, size, &_layout));
	if (FAILED(hr)) return false;
	*/

	return true;
}

//---------------------------------------------------------------------
bool Shader::InitShaderPixel(const void* buff, size_t size)
{
	AppContext* pApp = AppContext::GetInstance();
	HRESULT hr;

	// シェーダ作成
	_RET_CHECK_ASSERT(pApp->GetD3D11Device()->CreatePixelShader(buff, size, NULL, &_shadarData[(uint8_t)eTYPE::PS]._shader._pixel));
	if (FAILED(hr)) return false;

	return true;
}
/*
//---------------------------------------------------------------------
void Shader::preRenderSetParam(DirectX::SimpleMath::Matrix* mat)
{
	IShaderValue::SArgParam param(nullptr, m_pEffect, mat);
	util::for_each(m_apDelegate, std::bind2nd(std::mem_fun(&IShaderValue::preRenderSetParam), &param));
}

//---------------------------------------------------------------------
void Shader::renderSetParam(CMaterialData* mate)
{
	IShaderValue::SArgParam param(mate, m_pEffect, nullptr);
	util::for_each(m_apDelegate, std::bind2nd(std::mem_fun(&IShaderValue::renderSetParam), &param));
}*/

//-------------------------------------------------------------------------
void Shader::setupParameter(eTYPE type)
{
	AppContext* app = AppContext::GetInstance();
	ShaderData* shaderData = &_shadarData[(uint8_t)type];

	HRESULT hr;

	D3D11_SHADER_DESC desc;
	shaderData->_reflection->GetDesc(&desc);

	// 数を調べる
	// 定数バッファ
	if (desc.ConstantBuffers > 0)
	{
		D3D11_SHADER_BUFFER_DESC buffDesc;
		ID3D11ShaderReflectionConstantBuffer* refConstant = shaderData->_reflection->GetConstantBufferByIndex(0);	// とりあえず0しか見ない
		refConstant->GetDesc(&buffDesc);

		// バッファ作成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = buffDesc.Size;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		_RET_CHECK_ASSERT(app->GetD3D11Device()->CreateBuffer(&bd, NULL, &shaderData->_d3dBuffer));

		shaderData->_buffer = new char[buffDesc.Size];
		shaderData->_bufferSize = buffDesc.Size;
		shaderData->_constantValue.resize(buffDesc.Variables);

		// 変数
		for (unsigned int i = 0; i < buffDesc.Variables; i++)
		{
			ID3D11ShaderReflectionVariable* variable = refConstant->GetVariableByIndex(i);
			D3D11_SHADER_VARIABLE_DESC varDecsc;
			variable->GetDesc(&varDecsc);
			shaderData->_constantValue[i].Create(this, varDecsc.Name, shaderData->_buffer + varDecsc.StartOffset);
		}
	}

	// リソースパラメータ
	if (desc.BoundResources > 0)
	{
		shaderData->_resourcesValue.resize(desc.BoundResources);
		for (unsigned int i = 0; i < desc.BoundResources; i++)
		{
			D3D11_SHADER_INPUT_BIND_DESC bindDesc;
			shaderData->_reflection->GetResourceBindingDesc(i, &bindDesc);
			if (bindDesc.Type == D3D_SIT_TEXTURE) {
				shaderData->_resourcesValue[i].Create(this, bindDesc.Name, bindDesc.BindPoint);
			}
		}
	}

	return;
}
