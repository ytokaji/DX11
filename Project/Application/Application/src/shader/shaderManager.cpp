/**
	@file shaderManager.h
	@brief シェーダファイルの管理
*/
#include "stdafx.h"
#include "shader/shaderManager.h"
#include "shader/shader.h"
#include "appContext.h"

/// シェーダーファイルのインクルード
#if _PRECOMPILE_SHADER_USE
#include "shader/CompileShader/grid_ps.h"
#include "shader/CompileShader/grid_vs.h"
#endif

using namespace cpplinq;

namespace
{

#if _PRECOMPILE_SHADER_USE
	struct ShaderData
	{
		BYTE*					pShader;
		size_t					nSize;
		Shader::eTYPE			eType;
		CShaderManager::SHADER_TYPE	eShader;
	};

	static const ShaderData SHADER_DATA[] =
	{
		{ grid	, NUM_OF(grid)	, eSHATER_TYPE::VS	, CShaderManager::SHADER::GRID },
		{ grid	, NUM_OF(grid)	, eSHATER_TYPE::PS	, CShaderManager::SHADER::GRID },
	};

#else
	struct ShaderData
	{
		wchar_t*				pFileName;
		char*					pShaderProfile;
		char*					pFunctionName;
		Shader::eTYPE			eType;
		ShaderManager::SHADER_TYPE	eShader;
	};

	static const ShaderData SHADER_DATA[] =
	{
		{ L"../Project/Application/Application/shader/grid_vs.fx"	, "vs_5_0"	, "main"	, Shader::eTYPE::VS	, ShaderManager::SHADER_TYPE::GRID },
		{ L"../Project/Application/Application/shader/grid_ps.fx"	, "ps_5_0"	, "main"	, Shader::eTYPE::PS	, ShaderManager::SHADER_TYPE::GRID },
	};
#endif
}

//---------------------------------------------------------------------
const std::function<void(Shader*)>	ShaderManager::_registDelegate[] =
{
	ShaderManager::RegistDelegate_Grid
	/*
	, &Shader::_addFunc_Bump
	, &Shader::_addFunc_Fur
	, &Shader::_addFunc_2D
	, &Shader::_addFunc_WATER
	, &Shader::_addFunc_GAUSSIAN
	, &Shader::_addFunc_BRIGHTNESS
	, &Shader::_addFunc_DOF
	*/
};

//---------------------------------------------------------------------
ShaderManager::ShaderManager()
{
	_shader.fill(nullptr);
}

//---------------------------------------------------------------------
ShaderManager::~ShaderManager()
{
	Destroy();
}

//---------------------------------------------------------------------
void ShaderManager::Init()
{	
	ShaderReLoadReq();
}

//---------------------------------------------------------------------
void ShaderManager::Destroy()
{
	for (size_t i = 0; i<_shader.size(); ++i)
		SAFE_DELETE(_shader[i]);
}

//---------------------------------------------------------------------
void ShaderManager::ShaderReLoadReq()
{
	Destroy();

	// シェーダロード、コンパイル
	for (size_t i = 0; i<_shader.size(); ++i)
	{
		_PRINT("create shader : [%d]\n", i);
		_shader[i] = CreateShader((SHADER_TYPE)i);
	}
}

//---------------------------------------------------------------------
Shader* ShaderManager::GetShader(SHADER_TYPE shader)
{
	_ASSERT(shader<SHADER_TYPE::MAX);
	return _shader[(int)shader];
}

//---------------------------------------------------------------------
Shader* ShaderManager::CreateShader(SHADER_TYPE shader)
{
	// 条件のShaderを作って初期化
	Shader* pShader = new Shader();
	from_array(SHADER_DATA)
		>> where([&](ShaderData x){return x.eShader == shader; })
		>> for_each([&](ShaderData x)
	{
#if _PRECOMPILE_SHADER_USE
		bool b = pShader->InitShader(x.pShader, x.nSize, x.eType);
#else
		bool b = pShader->CompileInitShader(x.pFileName, x.pShaderProfile, x.pFunctionName, x.eType);
#endif
		_ASSERT(b);
	});

	return pShader;
}

//---------------------------------------------------------------------
void ShaderManager::RegistDelegate_Grid(Shader* shader)
{
//	shader->registDelegate(new CShaderValue_Semantic());
//	shader->registDelegate(new CShaderValue_DiffuseTexture());
}

/*
//---------------------------------------------------------------------
void Shader::_addFunc_Bump()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_DiffuseTexture());
	m_apDelegate.push_back(new CShaderValue_Bump());
}

//---------------------------------------------------------------------
void Shader::_addFunc_Fur()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_DiffuseTexture());
	m_apDelegate.push_back(new CShaderValue_Fur());
}

//---------------------------------------------------------------------
void Shader::_addFunc_2D()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_FrameBufferTexture());
}

//---------------------------------------------------------------------
void Shader::_addFunc_WATER()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_WaterParam());
}

//---------------------------------------------------------------------
void Shader::_addFunc_GAUSSIAN()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_Gaussian());
}

//---------------------------------------------------------------------
void Shader::_addFunc_BRIGHTNESS()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_Brightness());
	m_apDelegate.push_back(new CShaderValue_FrameBufferTexture());
}

//---------------------------------------------------------------------
void Shader::_addFunc_DOF()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_FrameBufferTexture());
	m_apDelegate.push_back(new CShaderValue_Dof());
}
*/


