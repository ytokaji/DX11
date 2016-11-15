/**
	@file shaderValue.cpp
	@brief シェーダパラメータの設定
*/

#include "stdafx.h"
#include "shader/shaderValue.h"
#include "shader/shader.h"
#include "appContext.h"

using namespace std;

namespace
{
	//! サンプリングポイント数.
	static const unsigned int s_nGaussianSamplingPoint = 4;

	/// セマンティックリスト
	tuple<string, function<void(ShaderValue*)>> applyFunc[] =
	{
		std::make_tuple("Projection", ShaderValue::Projection),
		std::make_tuple("World", ShaderValue::World),
	};
}

//---------------------------------------------------------------------
ShaderValue::ShaderValue()
	: _shader(nullptr)
	, _offset(0)
	, _textureSlot(0)
{
}

//---------------------------------------------------------------------
size_t ShaderValue::Create(CShader* shader, ID3D11ShaderReflectionVariable* variable)
{
	D3D11_SHADER_VARIABLE_DESC varDesc;
	D3D11_SHADER_TYPE_DESC typDesc;
	variable->GetDesc(&varDesc);
	variable->GetType()->GetDesc(&typDesc);

	_shader = shader;
	_offset = varDesc.StartOffset;

	for each (auto i in applyFunc)
	{
		if (varDesc.Name != std::get<0>(i)) { continue; }
		_applyFunc = std::get<1>(i);
	}

	// サイズ
	return static_cast<size_t>(sizeof(float) * typDesc.Columns * typDesc.Rows * std::max(typDesc.Elements, (UINT)1));
}

//---------------------------------------------------------------------
void ShaderValue::Apply()
{
	_applyFunc(this);
}

//---------------------------------------------------------------------
void ShaderValue::Projection(ShaderValue* shader)
{
}

//---------------------------------------------------------------------
void ShaderValue::World(ShaderValue* shader)
{
}

#if 0
//---------------------------------------------------------------------
CShaderValue_Semantic::CShaderValue_Semantic()
	:	IShaderValue			()
	,	m_hPorj					( nullptr )
	,	m_hWorld				( nullptr )
	,	m_hWorldView			( nullptr )
	,	m_hWorldViewPorj		( nullptr )
	,	m_hCameraPosition		( nullptr )
	,	m_hDirectionalLightDir	( nullptr )
	,	m_hTime					( nullptr )
	,	m_hAmbient				( nullptr )
	,	m_hDiffuse				( nullptr )
	,	m_hSpecular				( nullptr )
{
}

//---------------------------------------------------------------------
CShaderValue_Semantic::~CShaderValue_Semantic()
{
}

//---------------------------------------------------------------------
void CShaderValue_Semantic::SetValue(D3DXMATRIX& i_rMat)
{
//	D3DXMatrixIdentity( &m_mWorld );

	D3DXMATRIX mWorld;
	D3DXMatrixIdentity( &mWorld );
	if( i_pParam->pMat )
	{
		mWorld = *i_pParam->pMat;
	}
	D3DXMATRIX mWorldView;
	D3DXMatrixMultiply( &mWorldView, &mWorld, AppContext::GetInstance()->getViewMatrix() );
	
	D3DXMATRIX mProj = *AppContext::GetInstance()->getProjMatrix();
	D3DXMATRIX mWorldViewPorj;
	D3DXMatrixMultiply( &mWorldViewPorj, &mWorldView, &mProj );

	HRESULT hr = S_OK;
	if( m_hPorj )
	{
		_RET_CHECK( i_pParam->pEffect->SetMatrix( m_hPorj, AppContext::GetInstance()->getProjMatrix()) );
	}

	if( m_hWorld )
	{
		_RET_CHECK( i_pParam->pEffect->SetMatrix( m_hWorld, &mWorld ) );
	}

	if( m_hWorldView )
	{
		_RET_CHECK( i_pParam->pEffect->SetMatrix( m_hWorldView, &mWorldView ) );
	}

	if( m_hWorldViewPorj )
	{
		_RET_CHECK( i_pParam->pEffect->SetMatrix( m_hWorldViewPorj, &mWorldViewPorj ) );
	}
	
	if( m_hCameraPosition )
	{
		const D3DXVECTOR3* pPos = AppContext::GetInstance()->getCamera()->GetEyePt();
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_hCameraPosition, &pPos->x, 3) );
	}
	
	if( m_hDirectionalLightDir )
	{
		const D3DXVECTOR3* pPos = AppContext::GetInstance()->getDirectionalLightDir();
		D3DXVECTOR3 vDir;
		D3DXVec3Normalize( &vDir, pPos );
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_hDirectionalLightDir, &vDir.x, 3) );
	}

	if( m_hTime )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloat( m_hTime, AppContext::GetInstance()->getElapsdTime() ) );
	}
}

//---------------------------------------------------------------------
void CShaderValue_Semantic::renderSetParam(CMaterial* i_pMate)
{
	HRESULT hr = S_OK;
	if( m_hAmbient )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_hAmbient, &i_pParam->pMate->m_Mate.Ambient.r, 4 ) );
	}
	
	if( m_hDiffuse )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_hDiffuse, &i_pParam->pMate->m_Mate.Diffuse.r, 4 ) );
	}

	if( m_hSpecular )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_hSpecular, &i_pParam->pMate->m_Mate.Specular.r, 4 ) );
	}
}

//---------------------------------------------------------------------
void CShaderValue_Semantic::attach(CShader* i_pParam)
{
	m_pShader = i_pParam;
	m_hPorj = i_pParam->pEffect->GetParameterBySemantic( 0, "Projection" );
	m_hWorld = i_pParam->pEffect->GetParameterBySemantic( 0, "World" );
	m_hWorldView = i_pParam->pEffect->GetParameterBySemantic( 0, "WorldView" );
	m_hWorldViewPorj = i_pParam->pEffect->GetParameterBySemantic( 0, "WorldViewProjection" );
	m_hCameraPosition = i_pParam->pEffect->GetParameterBySemantic( 0, "CameraPositon" );
	m_hDirectionalLightDir = i_pParam->pEffect->GetParameterBySemantic( 0, "DirectionalLightDir" );
	m_hTime = i_pParam->pEffect->GetParameterBySemantic( 0, "Time" );
	m_hAmbient = i_pParam->pEffect->GetParameterBySemantic( 0, "Ambient" );
	m_hDiffuse = i_pParam->pEffect->GetParameterBySemantic( 0, "Diffuse" );
	m_hSpecular = i_pParam->pEffect->GetParameterBySemantic( 0, "Specular" );
}

//---------------------------------------------------------------------
CShaderValue_DiffuseTexture::CShaderValue_DiffuseTexture()
	:	IShaderValue		()
	,	m_hDiffuseTexture	( nullptr )
{
}

//---------------------------------------------------------------------
CShaderValue_DiffuseTexture::~CShaderValue_DiffuseTexture()
{
}

//---------------------------------------------------------------------
void CShaderValue_DiffuseTexture::renderSetParam(CMaterial* i_pMate)
{
	HRESULT hr = S_OK;
	if( m_hDiffuseTexture )
		_RET_CHECK( i_pParam->pEffect->SetTexture( m_hDiffuseTexture, i_pParam->pMate->m_pTex) );
}

//---------------------------------------------------------------------
void CShaderValue_DiffuseTexture::attach(CShader* i_pParam)
{
	m_hDiffuseTexture = i_pParam->pEffect->GetParameterBySemantic( 0, "DiffuseTexture" );
}

//---------------------------------------------------------------------
CShaderValue_FrameBufferTexture::CShaderValue_FrameBufferTexture()
	:	IShaderValue				()
	,	m_hFrameBufferTexture		( nullptr )
	,	m_hFrameBufferDepthTexture	( nullptr )
{
}

//---------------------------------------------------------------------
CShaderValue_FrameBufferTexture::~CShaderValue_FrameBufferTexture()
{
}

//---------------------------------------------------------------------
void CShaderValue_FrameBufferTexture::SetValue(D3DXMATRIX& i_rMat)
{
	HRESULT hr = S_OK;
	if( m_hFrameBufferTexture )
		_RET_CHECK( i_pParam->pEffect->SetTexture( m_hFrameBufferTexture, AppContext::GetInstance()->getFrameBuffer()) );
	
	if( m_hFrameBufferDepthTexture )
		_RET_CHECK( i_pParam->pEffect->SetTexture( m_hFrameBufferDepthTexture, AppContext::GetInstance()->getDepthBuffer()) );
}

//---------------------------------------------------------------------
void CShaderValue_FrameBufferTexture::attach(CShader* i_pParam)
{
	m_hFrameBufferTexture = i_pParam->pEffect->GetParameterBySemantic( 0, "FrameBuffer" );
	m_hFrameBufferDepthTexture = i_pParam->pEffect->GetParameterBySemantic( 0, "FrameBufferDepth" );
}

//---------------------------------------------------------------------
CShaderValue_WaterParam::CShaderValue_WaterParam()
	:	IShaderValue		()
	,	m_h4Color			( nullptr )
	,	m_h3SpecularColor	( nullptr )
	,	m_h2RefrParams		( nullptr )
	,	m_h2ReflParams		( nullptr )
	,	m_h2SpecularPower	( nullptr )
	,	m_hReflBias			( nullptr )
	,	m_hFresnelPower		( nullptr )
	,	m_h2WaveOffset		( nullptr )
	,	m_h2FrameBufferSize	( nullptr )
{
	memset( m_pBumpOffsetUV, 0, sizeof(m_pBumpOffsetUV) );
}

//---------------------------------------------------------------------
CShaderValue_WaterParam::~CShaderValue_WaterParam()
{
}

//---------------------------------------------------------------------
void CShaderValue_WaterParam::SetValue(D3DXMATRIX& i_rMat)
{
	const SWaterParam* pParam = &AppContext::GetInstance()->getShaderParam()->m_Water;
	HRESULT hr = S_OK;

	if( m_h4Color )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_h4Color, pParam->m_f3Color, 4) );
	}
	
	if( m_h3SpecularColor )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_h3SpecularColor, pParam->m_f3SpecularColor, 3) );
	}
		
	if( m_h2RefrParams )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_h2RefrParams, pParam->m_f2RefrParams, 2) );
	}
		
	if( m_h2ReflParams )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_h2ReflParams, pParam->m_f2ReflParams, 2) );
	}
		
	if( m_h2SpecularPower )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_h2SpecularPower, pParam->m_f2SpecularPower, 4) );
	}
		
	if( m_hReflBias	)
	{
		_RET_CHECK( i_pParam->pEffect->SetFloat( m_hReflBias, pParam->m_fReflBias) );
	}
		
	if( m_hFresnelPower )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloat( m_hFresnelPower, pParam->m_fFresnelPower) );
	}
		
	if( m_h2WaveOffset )
	{
		static float m_pBumpOffsetUV[2] = {0.f,0.f};
		m_pBumpOffsetUV[0] += 0.05f * AppContext::GetInstance()->getElapsdTime();
		m_pBumpOffsetUV[1] += 0.05f * AppContext::GetInstance()->getElapsdTime();
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_h2WaveOffset, m_pBumpOffsetUV, 2) );
	}

	if( m_h2FrameBufferSize )
	{
		static const float fFrameBufferSize[2] = {1.f/(float)AppContext::WINDOW_W, 1.f/(float)AppContext::WINDOW_H};
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_h2FrameBufferSize, fFrameBufferSize, 2) );
	}

	if( m_f3Light )
	{
		//接線計算代わり
		const D3DXVECTOR3* pPos = AppContext::GetInstance()->getDirectionalLightDir();
		D3DXMATRIX mRot;
		D3DXMatrixRotationY( &mRot, 90 );
		D3DXVECTOR4 vDir;
		D3DXVec3Transform( &vDir, pPos, &mRot );
		D3DXVec4Normalize( &vDir, &vDir );
		vDir *= -1;
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_f3Light, &vDir.x, 3) );
	}
}

//---------------------------------------------------------------------
void CShaderValue_WaterParam::attach(CShader* i_pParam)
{	
	m_h4Color = i_pParam->pEffect->GetParameterByName( 0, "g_f4Color" );
	m_h3SpecularColor = i_pParam->pEffect->GetParameterByName( 0, "g_f3SpecularColor" );
	m_h2RefrParams = i_pParam->pEffect->GetParameterByName( 0, "g_f2RefrParams" );
	m_h2ReflParams = i_pParam->pEffect->GetParameterByName( 0, "g_f2ReflParams" );
	m_h2SpecularPower = i_pParam->pEffect->GetParameterByName( 0, "g_f2SpecularPower" );
	m_hReflBias = i_pParam->pEffect->GetParameterByName( 0, "g_fReflBias" );
	m_hFresnelPower = i_pParam->pEffect->GetParameterByName( 0, "g_fFresnelPower" );
	m_h2WaveOffset = i_pParam->pEffect->GetParameterByName( 0, "g_f2WaveOffset" );
	m_h2FrameBufferSize = i_pParam->pEffect->GetParameterByName( 0, "g_f2FrameBufferSize" );
	m_f3Light = i_pParam->pEffect->GetParameterByName( 0, "g_f3WaterLightDir" );
}

//---------------------------------------------------------------------
CShaderValue_Bump::CShaderValue_Bump()
	:	IShaderValue		()
	,	m_h2NormalMap		( nullptr )
	,	m_hSpecularPower	( nullptr )
	,	m_hSpecularRange	( nullptr )
	,	m_pBumpTex			( nullptr )
{
	// テクスチャロード
	IDirect3DDevice9* pDevice = AppContext::GetInstance()->getD3D9Device();
	HRESULT hr = S_OK;
	_RET_CHECK( D3DXCreateTextureFromFileEx( pDevice, L"texture/default_bump_normal.dds", D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_A16B16G16R16F,
											D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, nullptr,
											nullptr, &m_pBumpTex ) );
}

//---------------------------------------------------------------------
CShaderValue_Bump::~CShaderValue_Bump()
{
	SAFE_RELEASE( m_pBumpTex );
}

//---------------------------------------------------------------------
void CShaderValue_Bump::SetValue(D3DXMATRIX& i_rMat)
{
	const SBumpParam* pParam = &AppContext::GetInstance()->getShaderParam()->m_Bump;
	HRESULT hr = S_OK;

	if( m_h2NormalMap )
		_RET_CHECK( i_pParam->pEffect->SetTexture( m_h2NormalMap, m_pBumpTex) );
	
	if( m_hSpecularPower )
		_RET_CHECK( i_pParam->pEffect->SetFloat( m_hSpecularPower, pParam->m_fSpecularPower) );
	
	if( m_hSpecularRange )
		_RET_CHECK( i_pParam->pEffect->SetFloat( m_hSpecularRange, pParam->m_fSpecularRange) );
}

//---------------------------------------------------------------------
void CShaderValue_Bump::attach(CShader* i_pParam)
{
	m_h2NormalMap = i_pParam->pEffect->GetParameterByName( 0, "g_NormalMap" );
	m_hSpecularRange = i_pParam->pEffect->GetParameterByName( 0, "g_Specular" );
	m_hSpecularPower = i_pParam->pEffect->GetParameterByName( 0, "g_SpecularPower" );
}

//---------------------------------------------------------------------
CShaderValue_Fur::CShaderValue_Fur()
	:	IShaderValue		()
	,	m_h3furColor		( nullptr )
	,	m_hFurDistance		( nullptr )
	,	m_h2FurMap			( nullptr )
	,	m_hCount			( nullptr )
	,	m_pFurTex			( nullptr )
	,	m_nCount			( 0 )
{
	// テクスチャロード
	IDirect3DDevice9* pDevice = AppContext::GetInstance()->getD3D9Device();
	HRESULT hr = S_OK;
	_RET_CHECK( D3DXCreateTextureFromFileEx( pDevice, L"texture/furmap.dds", D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_A16B16G16R16F,
											D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, nullptr,
											nullptr, &m_pFurTex ) );
}

//---------------------------------------------------------------------
CShaderValue_Fur::~CShaderValue_Fur()
{
	SAFE_RELEASE( m_pFurTex );
}

//---------------------------------------------------------------------
void CShaderValue_Fur::SetValue(D3DXMATRIX& i_rMat)
{
	const SFurParam* pParam = &AppContext::GetInstance()->getShaderParam()->m_Fur;
	HRESULT hr = S_OK;
	if( m_h2FurMap )
		_RET_CHECK( i_pParam->pEffect->SetTexture( m_h2FurMap, m_pFurTex) );
	
	if( m_h3furColor )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_h3furColor, pParam->m_f3Color, 3) );
	}

	if( m_hFurDistance )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloat( m_hFurDistance, pParam->m_fDistance) );
	}

	m_nCount = 0;
}

//---------------------------------------------------------------------
void CShaderValue_Fur::attach(CShader* i_pParam)
{
	m_h3furColor = i_pParam->pEffect->GetParameterByName( 0, "g_f3furColor" );
	m_hFurDistance = i_pParam->pEffect->GetParameterByName( 0, "g_fFurDistance" );
	m_h2FurMap = i_pParam->pEffect->GetParameterByName( 0, "g_FurMap" );
	m_hCount = i_pParam->pEffect->GetParameterByName( 0, "g_nFurNumber" );
}

//---------------------------------------------------------------------
CShaderValue_Gaussian::CShaderValue_Gaussian()
	:	IShaderValue		()
	,	m_hfUvOffset			( nullptr )
	,	m_hfOffset			( nullptr )
	,	m_hfWindowRatio		( nullptr )
	,	m_hfWeight			( nullptr )
{
	float fTotal( 0.0f );
	const float c_fResDispersion( 1.f/4.7f );
		
	for( unsigned int i=0; i<s_nGaussianSamplingPoint; ++i )
	{
		m_fWeight[ i ] = exp( -0.5f * (float)( i * i ) * c_fResDispersion );
		fTotal += m_fWeight[ i ];
	}
	fTotal += fTotal;		// 倍にする.
		
	const float c_fResTotal( 1.f/fTotal );
	for( unsigned int i = 0 ; i < s_nGaussianSamplingPoint ; ++i ){
		m_fWeight[ i ] *= c_fResTotal;
	}
}

//---------------------------------------------------------------------
CShaderValue_Gaussian::~CShaderValue_Gaussian()
{
}

//---------------------------------------------------------------------
void CShaderValue_Gaussian::SetValue(D3DXMATRIX& i_rMat)
{
	const float c_fWindowRatio[2] = 
	{
		1.f/(float)AppContext::WINDOW_W,
		1.f/(float)AppContext::WINDOW_H
	};
	
	HRESULT hr = S_OK;

	if( m_hfUvOffset )
	{
		const float fArray[4] = { -1.f, -3.f, -5.f, -7.f };
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_hfUvOffset, fArray, 4) );
	}
	
	if( m_hfWindowRatio )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_hfWindowRatio, c_fWindowRatio, 2) );
	}

	if( m_hfOffset )
	{
		const float fVal = (float)s_nGaussianSamplingPoint * 2.0f;
		_RET_CHECK( i_pParam->pEffect->SetFloat( m_hfOffset, fVal) );
	}

	if( m_hfWeight )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_hfWeight, m_fWeight, 4) );
	}
}

//---------------------------------------------------------------------
void CShaderValue_Gaussian::attach(CShader* i_pParam)
{
	m_hfUvOffset = i_pParam->pEffect->GetParameterByName( 0, "g_f4UVOffset" );
	m_hfWindowRatio = i_pParam->pEffect->GetParameterByName( 0, "g_2fWindowRatio" );
	m_hfOffset = i_pParam->pEffect->GetParameterByName( 0, "g_fOffset" );
	m_hfWeight = i_pParam->pEffect->GetParameterByName( 0, "g_f4weight" );
}


//---------------------------------------------------------------------
CShaderValue_Brightness::CShaderValue_Brightness()
	:	IShaderValue		()
	,	m_hfBrighness		( nullptr )
	,	m_hfWindowRatio		( nullptr )
{
}

//---------------------------------------------------------------------
CShaderValue_Brightness::~CShaderValue_Brightness()
{
}

//---------------------------------------------------------------------
void CShaderValue_Brightness::SetValue(D3DXMATRIX& i_rMat)
{
	const SPostParam* pParam = &AppContext::GetInstance()->getShaderParam()->m_Post;

	const float c_fWindowRatio[2] = 
	{
		1.f/(float)AppContext::WINDOW_W,
		1.f/(float)AppContext::WINDOW_H
	};

	HRESULT hr = S_OK;

	if( m_hfBrighness )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloat( m_hfBrighness, pParam->m_fBrightness) );
	}

	if( m_hfWindowRatio )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloatArray( m_hfWindowRatio, c_fWindowRatio, 2) );
	}
}

//---------------------------------------------------------------------
void CShaderValue_Brightness::attach(CShader* i_pParam)
{
	m_hfBrighness = i_pParam->pEffect->GetParameterByName( 0, "g_fBrightnessBias" );
	m_hfWindowRatio = i_pParam->pEffect->GetParameterByName( 0, "g_2fWindowRatio" );
}

//---------------------------------------------------------------------
CShaderValue_Dof::CShaderValue_Dof()
	:	IShaderValue		()
	,	m_hfFocusDistance	( nullptr )
	,	m_hfFocusRange		( nullptr )
{
}

//---------------------------------------------------------------------
CShaderValue_Dof::~CShaderValue_Dof()
{
}

//---------------------------------------------------------------------
void CShaderValue_Dof::SetValue(D3DXMATRIX& i_rMat)
{
	const SPostParam* pParam = &AppContext::GetInstance()->getShaderParam()->m_Post;
	HRESULT hr = S_OK;

	if( m_hfFocusDistance )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloat( m_hfFocusDistance, pParam->m_fFocusDistance) );
	}

	if( m_hfFocusRange )
	{
		_RET_CHECK( i_pParam->pEffect->SetFloat( m_hfFocusRange, pParam->m_fFocusRange) );
	}
}

//---------------------------------------------------------------------
void CShaderValue_Dof::attach(CShader* i_pParam)
{
	m_hfFocusDistance = i_pParam->pEffect->GetParameterByName( 0, "g_fFocusDistance" );
	m_hfFocusRange = i_pParam->pEffect->GetParameterByName( 0, "g_fFocusRange" );
}

#endif
