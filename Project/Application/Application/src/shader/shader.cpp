/**
	@file shader.h
	@brief シェーダファイル
*/


#include "stdafx.h"
#include "shader/shader.h"
#include "appContext.h"

using namespace cpplinq;

namespace
{
	// シェーダーセット関数
	static const std::function<void(ID3D11DeviceContext* context, Shader::ShaderData* shader)> SET_SHADER_FUNC[] =
	{
		[](ID3D11DeviceContext* context, Shader::ShaderData* shader){context->VSSetShader(shader->_shader._vertex, nullptr, 0); },
		[](ID3D11DeviceContext* context, Shader::ShaderData* shader){context->PSSetShader(shader->_shader._pixel, nullptr, 0); },
		[](ID3D11DeviceContext* context, Shader::ShaderData* shader){context->HSSetShader(shader->_shader._hull, nullptr, 0); },
		[](ID3D11DeviceContext* context, Shader::ShaderData* shader){context->DSGetShader(&shader->_shader._domain, nullptr, 0); },
		[](ID3D11DeviceContext* context, Shader::ShaderData* shader){context->GSGetShader(&shader->_shader._geometry, nullptr, 0); },
		[](ID3D11DeviceContext* context, Shader::ShaderData* shader){context->CSSetShader(shader->_shader._compute, nullptr, 0); },
	};
	static_assert(NUM_OF(SET_SHADER_FUNC) == (uint8_t)Shader::eTYPE::MAX, "");

	// シェーダー定数バッファ関数
	static const std::function<void(ID3D11DeviceContext* context, ID3D11Buffer* buffer)> SET_CONSTANT_BUFFER_FUNC[] =
	{
		[](ID3D11DeviceContext* context, ID3D11Buffer* buffer){context->VSSetConstantBuffers(0, 1, &buffer); },
		[](ID3D11DeviceContext* context, ID3D11Buffer* buffer){context->PSSetConstantBuffers(0, 1, &buffer); },
		[](ID3D11DeviceContext* context, ID3D11Buffer* buffer){context->HSSetConstantBuffers(0, 1, &buffer); },
		[](ID3D11DeviceContext* context, ID3D11Buffer* buffer){context->DSGetConstantBuffers(0, 1, &buffer); },
		[](ID3D11DeviceContext* context, ID3D11Buffer* buffer){context->GSGetConstantBuffers(0, 1, &buffer); },
		[](ID3D11DeviceContext* context, ID3D11Buffer* buffer){context->CSSetConstantBuffers(0, 1, &buffer); },
	};
	static_assert(NUM_OF(SET_CONSTANT_BUFFER_FUNC) == (uint8_t)Shader::eTYPE::MAX, "");
}

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
	typedef bool (Shader::*ProcFunc)(ShaderData* shader, const void*, size_t);
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

	_shadarData.push_back(std::unique_ptr<ShaderData>(new ShaderData()));
	_shadarData.back()->_type = type;

	// シェーダー作成
	bool ret = (this->*sc_aInitFunc[(uint8_t)type])(_shadarData.back().get(), buff, size);
	if (ret == false) { return false; }

	// シェーダーリフレクションインターフェース取得
	HRESULT hr;
	_RET_CHECK_ASSERT(D3DReflect(buff, size, IID_ID3D11ShaderReflection, (void**)&_shadarData.back()->_reflection));

	setupParameter(_shadarData.back().get());

	return true;
}

//---------------------------------------------------------------------
bool Shader::InitShaderVertex(ShaderData* shader, const void* buff, size_t size)
{
	ID3D11Device* device = AppContext::GetInstance()->GetD3D11Device();
	HRESULT hr;
	
	// シェーダ作成
	_RET_CHECK_ASSERT(device->CreateVertexShader(buff, size, NULL, &(shader->_shader._vertex)));
	if (FAILED(hr)) return false;

	// 入力レイアウトを生成.
	_RET_CHECK_ASSERT(device->CreateInputLayout(DEFAULT_ELEMENT_LAYOUT, DEFAULT_ELEMENT_LAYOUT_NUM, buff, size, &_layout));
	if (FAILED(hr)) return false;

	return true;
}

//---------------------------------------------------------------------
bool Shader::InitShaderPixel(ShaderData* shader, const void* buff, size_t size)
{
	AppContext* pApp = AppContext::GetInstance();
	HRESULT hr;

	// シェーダ作成
	_RET_CHECK_ASSERT(pApp->GetD3D11Device()->CreatePixelShader(buff, size, NULL, &(shader->_shader._pixel)));
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
void Shader::setupParameter(ShaderData* shaderData)
{
	AppContext* app = AppContext::GetInstance();

	HRESULT hr;

	D3D11_SHADER_DESC desc;
	shaderData->_reflection->GetDesc(&desc);

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
		shaderData->_constantValue.resize(buffDesc.Variables, this);

		// 変数
		for (unsigned int i = 0; i < buffDesc.Variables; i++)
		{
			ID3D11ShaderReflectionVariable* variable = refConstant->GetVariableByIndex(i);
			D3D11_SHADER_VARIABLE_DESC varDecsc;
			variable->GetDesc(&varDecsc);
			shaderData->_constantValue[i].Create(varDecsc.Name, shaderData->_buffer + varDecsc.StartOffset);
		}
	}

	// リソースパラメータ
	if (desc.BoundResources > 0)
	{
		shaderData->_resourcesValue.resize(desc.BoundResources, this);
		for (unsigned int i = 0; i < desc.BoundResources; i++)
		{
			D3D11_SHADER_INPUT_BIND_DESC bindDesc;
			shaderData->_reflection->GetResourceBindingDesc(i, &bindDesc);
			if (bindDesc.Type == D3D_SIT_TEXTURE) {
				shaderData->_resourcesValue[i].Create(bindDesc.Name, bindDesc.BindPoint);
			}
		}
	}

	return;
}

//-------------------------------------------------------------------------
void Shader::Apply(ID3D11DeviceContext* context)
{
	for (auto&& i : _shadarData)
	{
		SET_SHADER_FUNC[(int)i->_type](context, i.get());
		for (auto&& j : i->_constantValue) {
			j.Apply();
		}
		for (auto&& j : i->_resourcesValue) { j.Apply(); }

		if (i->_d3dBuffer)
		{
			context->UpdateSubresource(i->_d3dBuffer, 0, nullptr, i->_buffer, 0, 0);
			SET_CONSTANT_BUFFER_FUNC[(int)i->_type](context, i->_d3dBuffer);
		}
	}
	context->IASetInputLayout(_layout);
}

//-------------------------------------------------------------------------
void Shader::RegistShaderParamSetFunc(const char* name, std::function<void(ShaderValueBase*)> func)
{
	for (auto&& i : _shadarData)
	{
		for (auto&& j : i->_constantValue)
		{
			if (j.GetName() != name){ continue; }
			j.SetApplyFunc(func);
		}

		for (auto&& j : i->_resourcesValue)
		{
			if (j.GetName() != name){ continue; }
			j.SetApplyFunc(func);
		}
	}
}

