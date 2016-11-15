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

namespace
{

#if _PRECOMPILE_SHADER_USE
	struct ShaderData
	{
		BYTE*					pShader;
		size_t					nSize;
		CShader::eTYPE			eType;
		CShaderManager::eSHADER	eShader;
	};

	static const ShaderData sc_pShaderData[] =
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
		CShader::eTYPE			eType;
		ShaderManager::eSHADER	eShader;
	};

	static const ShaderData sc_pShaderData[] =
	{
		{ L"../Project/Application/Application/shader/grid_vs.fx"	, "vs_5_0"	, "main"	, CShader::eTYPE::VS	, ShaderManager::eSHADER::GRID },
		{ L"../Project/Application/Application/shader/grid_ps.fx"	, "ps_5_0"	, "main"	, CShader::eTYPE::PS	, ShaderManager::eSHADER::GRID },
	};
#endif
}

//---------------------------------------------------------------------
const ShaderManager::RegistDelegateFunc	ShaderManager::m_pRegistDelegate[] =
{
	&ShaderManager::_registDelegate_Grid
	/*
	, &CShader::_addFunc_Bump
	, &CShader::_addFunc_Fur
	, &CShader::_addFunc_2D
	, &CShader::_addFunc_WATER
	, &CShader::_addFunc_GAUSSIAN
	, &CShader::_addFunc_BRIGHTNESS
	, &CShader::_addFunc_DOF
	*/
};

//---------------------------------------------------------------------
ShaderManager::ShaderManager()
{
	m_apShader.fill(nullptr);
}

//---------------------------------------------------------------------
ShaderManager::~ShaderManager()
{
	destroy();
}

//---------------------------------------------------------------------
void ShaderManager::init()
{	
	shaderReLoadReq();
}

//---------------------------------------------------------------------
void ShaderManager::destroy()
{
	for (size_t i = 0; i<m_apShader.size(); ++i)
		SAFE_DELETE(m_apShader[i]);
}

//---------------------------------------------------------------------
void ShaderManager::shaderReLoadReq()
{
	destroy();

	// シェーダロード、コンパイル
	for (size_t i = 0; i<m_apShader.size(); ++i)
	{
		_PRINT("create shader : [%d]\n", i);
		
		auto shader = createShader((eSHADER)i);
		if (shader == nullptr) continue;

		m_apShader[i] = shader;
	}
}

//---------------------------------------------------------------------
CShader* ShaderManager::getShader(eSHADER i_eShader)
{
	_ASSERT(i_eShader<eSHADER::MAX);
	return m_apShader[(int)i_eShader];
}

//---------------------------------------------------------------------
CShader* ShaderManager::createShader(eSHADER i_eShader)
{
	// 条件に合うものを探す
	std::array<const ShaderData*, (int)CShader::eTYPE::MAX> apList = {nullptr,};
	for (int i = 0; i < NUM_OF(sc_pShaderData); ++i)
	{
		if (sc_pShaderData[i].eShader != i_eShader)
			continue;

		apList[(int)sc_pShaderData[i].eType] = &sc_pShaderData[i];
	}
	
	// 条件のCShaderを作って初期化
	CShader* pShader = new CShader();
	for (size_t i = 0; i<apList.size(); ++i)
	{
#if _PRECOMPILE_SHADER_USE
		bool b = pShader->InitShader(apList[i]->pShader, apList[i]->nSize, apList[i]->eType);
#else
		bool b = pShader->CompileInitShader(apList[i]->pFileName, apList[i]->pShaderProfile, apList[i]->pFunctionName, apList[i]->eType);
#endif
		_ASSERT(b);
	}

	return pShader;
}

//---------------------------------------------------------------------
void ShaderManager::_registDelegate_Grid(CShader* i_pShader)
{
//	i_pShader->registDelegate(new CShaderValue_Semantic());
//	i_pShader->registDelegate(new CShaderValue_DiffuseTexture());
}

/*
//---------------------------------------------------------------------
void CShader::_addFunc_Bump()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_DiffuseTexture());
	m_apDelegate.push_back(new CShaderValue_Bump());
}

//---------------------------------------------------------------------
void CShader::_addFunc_Fur()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_DiffuseTexture());
	m_apDelegate.push_back(new CShaderValue_Fur());
}

//---------------------------------------------------------------------
void CShader::_addFunc_2D()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_FrameBufferTexture());
}

//---------------------------------------------------------------------
void CShader::_addFunc_WATER()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_WaterParam());
}

//---------------------------------------------------------------------
void CShader::_addFunc_GAUSSIAN()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_Gaussian());
}

//---------------------------------------------------------------------
void CShader::_addFunc_BRIGHTNESS()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_Brightness());
	m_apDelegate.push_back(new CShaderValue_FrameBufferTexture());
}

//---------------------------------------------------------------------
void CShader::_addFunc_DOF()
{
	m_apDelegate.push_back(new CShaderValue_Semantic());
	m_apDelegate.push_back(new CShaderValue_FrameBufferTexture());
	m_apDelegate.push_back(new CShaderValue_Dof());
}
*/


