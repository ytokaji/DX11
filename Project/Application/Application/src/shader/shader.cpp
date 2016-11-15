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
CShader::CShader()
	: _layout(nullptr)
{
}

//---------------------------------------------------------------------
CShader::~CShader()
{
	SAFE_RELEASE(_layout);
}

#if !_PRECOMPILE_SHADER_USE
//---------------------------------------------------------------------
bool CShader::CompileInitShader(wchar_t* i_pFileName, char* i_pShaderProfile, char* i_pFunctionName, eTYPE i_eType)
{
	DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG;
	HRESULT hr;

	// コンパイル
	ID3DBlob *pEffectBlob = 0, *pErrorBlob = 0;
	hr = D3DX11CompileFromFile(i_pFileName, 0, 0, i_pFunctionName, i_pShaderProfile, dwShaderFlags, 0, 0, &pEffectBlob, &pErrorBlob, 0);

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
	bool bRet = InitShader(pEffectBlob->GetBufferPointer(), pEffectBlob->GetBufferSize(), i_eType);
	SAFE_RELEASE(pEffectBlob);

	return bRet;
//	IShaderValue::SArgParam param(nullptr, m_pEffect, nullptr);
//	util::for_each(m_apDelegate, std::bind2nd(std::mem_fun(&IShaderValue::attachParam), &param));
}
#endif

//---------------------------------------------------------------------
bool CShader::InitShader(const void* i_pBuff, size_t i_nSize, eTYPE i_eType)
{
	typedef bool (CShader::*ProcFunc)(const void*, size_t);
	static const ProcFunc sc_aInitFunc[] =
	{
		&CShader::InitShaderVertex,
		&CShader::InitShaderPixel,
		&CShader::InitShaderHull,
		&CShader::InitShaderDomain,
		&CShader::InitShaderGeometry,
		&CShader::InitShaderCompute,
	};
	STATIC_ASSERT(NUM_OF(sc_aInitFunc) == (int)eTYPE::MAX);

	_shadarData[(int)i_eType] = SShaderData();

	// シェーダー作成
	bool ret = (this->*sc_aInitFunc[(int)i_eType])(i_pBuff, i_nSize);
	if (ret == false) { return false; }

	// シェーダーリフレクションインターフェース取得
	HRESULT hr;
	_RET_CHECK_ASSERT(D3DReflect(i_pBuff, i_nSize, IID_ID3D11ShaderReflection, (void**)&_shadarData[(int)i_eType].reflection));

	setupParameter(i_eType);

	return true;
}

//---------------------------------------------------------------------
bool CShader::InitShaderVertex(const void* i_pBuff, size_t i_nSize)
{
	ID3D11Device* pDevice = CAppContext::getInstance()->getD3D11Device();
	HRESULT hr;

	// シェーダ作成
	_RET_CHECK_ASSERT(pDevice->CreateVertexShader(i_pBuff, i_nSize, NULL, &_shadarData[(int)eTYPE::VS].shader.vertex));
	if (FAILED(hr)) return false;
	/*
	// InputLayoutの作成
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	_RET_CHECK_ASSERT(pDevice->CreateInputLayout(layout, ARRAYSIZE(layout), i_pBuff, i_nSize, &_layout));
	if (FAILED(hr)) return false;
	*/

	return true;
}

//---------------------------------------------------------------------
bool CShader::InitShaderPixel(const void* i_pBuff, size_t i_nSize)
{
	CAppContext* pApp = CAppContext::getInstance();
	HRESULT hr;

	// シェーダ作成
	_RET_CHECK_ASSERT(pApp->getD3D11Device()->CreatePixelShader(i_pBuff, i_nSize, NULL, &_shadarData[(int)eTYPE::PS].shader.pixel));
	if (FAILED(hr)) return false;

	return true;
}
/*
//---------------------------------------------------------------------
void CShader::preRenderSetParam(D3DXMATRIX* i_pMat)
{
	IShaderValue::SArgParam param(nullptr, m_pEffect, i_pMat);
	util::for_each(m_apDelegate, std::bind2nd(std::mem_fun(&IShaderValue::preRenderSetParam), &param));
}

//---------------------------------------------------------------------
void CShader::renderSetParam(CMaterialData* i_pMate)
{
	IShaderValue::SArgParam param(i_pMate, m_pEffect, nullptr);
	util::for_each(m_apDelegate, std::bind2nd(std::mem_fun(&IShaderValue::renderSetParam), &param));
}*/

//-------------------------------------------------------------------------
void CShader::setupParameter(eTYPE i_eType)
{
	CAppContext* pApp = CAppContext::getInstance();
	SShaderData* pShaderData = &_shadarData[(int)i_eType];

	HRESULT hr;

	D3D11_SHADER_DESC desc;
	pShaderData->reflection->GetDesc(&desc);

	// 定数バッファ
	if (desc.ConstantBuffers > 0)
	{
		D3D11_SHADER_BUFFER_DESC buffDesc;
		ID3D11ShaderReflectionConstantBuffer* refConstant = pShaderData->reflection->GetConstantBufferByIndex(0);	// とりあえず0しか見ない
		refConstant->GetDesc(&buffDesc);

		// バッファ作成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = buffDesc.Size;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		_RET_CHECK_ASSERT(pApp->getD3D11Device()->CreateBuffer(&bd, NULL, &pShaderData->d3dBuffer));

		pShaderData->pBuffer = new char[buffDesc.Size];
		pShaderData->nBufferSize = buffDesc.Size;
		pShaderData->aVariableParam.resize(buffDesc.Variables);

		// 変数
		for (unsigned int i = 0; i < buffDesc.Variables; i++)
		{
			ID3D11ShaderReflectionVariable* variable = refConstant->GetVariableByIndex(i);
			D3D11_SHADER_VARIABLE_DESC varDecsc;
			variable->GetDesc(&varDecsc);
			pShaderData->aVariableParam[i].str = varDecsc.Name;
			pShaderData->aVariableParam[i].pBuff = pShaderData->pBuffer + varDecsc.StartOffset;
		}
	}

	// リソースパラメータ
	if (desc.BoundResources > 0)
	{
		pShaderData->aResourceParam.resize(desc.BoundResources);
		for (unsigned int i = 0; i < desc.BoundResources; i++)
		{
			D3D11_SHADER_INPUT_BIND_DESC bindDesc;
			pShaderData->reflection->GetResourceBindingDesc(i, &bindDesc);
			if (bindDesc.Type == D3D_SIT_TEXTURE) {
				pShaderData->aResourceParam[i].str = bindDesc.Name;
				pShaderData->aResourceParam[i].bindPoint = bindDesc.BindPoint;
			}
		}
	}

	return;
}
