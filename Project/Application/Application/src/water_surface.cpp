/**
	@file water_surface.cpp
	@brief 水面
*/

#include "stdafx.h"
#include <D3D9.h>
#include "water_surface.h"
#include "application.h"
#include "shader_set_value.h"

namespace
{
	static const wchar_t* s_chNormalTexName = L"texture/waves2.dds";

	// 頂点情報の宣言
	D3DVERTEXELEMENT9 g_aSkyboxDecl[] =
	{
		 { 0, 0,	D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	// ポジション
		 { 0, 16,	D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// UV
		 D3DDECL_END()
	};

	// 頂点設定
	struct SKYBOX_VERTEX
	{
		SKYBOX_VERTEX(D3DXVECTOR4 pos, D3DXVECTOR3 tex)
			:	m_vPos	(pos)
			,	m_vTex	(tex)
		{
		};

		D3DXVECTOR4 m_vPos;
		D3DXVECTOR3 m_vTex;
	};

	static const unsigned int s_nSubdivisionX = 2;
	static const unsigned int s_nSubdivisionY = 2;
	static const unsigned int s_nTriNum = (s_nSubdivisionX*s_nSubdivisionY)<<1;
	static const unsigned int s_nVerNum = s_nTriNum * 3;
	static const float s_fEdgeLen =50.f;
	static const float fUvRatioX = 1.f/(float)s_nSubdivisionX;
	static const float fUvRatioY = 1.f/(float)s_nSubdivisionY;
	static const float fStartX = s_nSubdivisionX*s_fEdgeLen*-0.5f;
	static const float fStartY = s_nSubdivisionY*s_fEdgeLen*-0.5f;
};

//---------------------------------------------------------------------
CWaterSurFace::CWaterSurFace()
	:	m_pVB				( nullptr )
	,	m_pVertexDecl		( nullptr )
	,	m_pReflectBuffer	( nullptr )
	,	m_pWave				( nullptr )
{
}

//---------------------------------------------------------------------
CWaterSurFace::~CWaterSurFace()
{
	deviceLost();

	SAFE_RELEASE( m_pVB );
	SAFE_RELEASE( m_pVertexDecl );
	SAFE_RELEASE( m_pWave );
}

//---------------------------------------------------------------------
void CWaterSurFace::init()
{
	HRESULT hr = S_OK;
	IDirect3DDevice9* pDevice = AppContext::GetInstance()->getD3D9Device();

	// 頂点情報の設定
	_RET_CHECK( pDevice->CreateVertexDeclaration( g_aSkyboxDecl, &m_pVertexDecl ) );

	// テクスチャロード
	_RET_CHECK( D3DXCreateTextureFromFileEx( pDevice, s_chNormalTexName, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_A16B16G16R16F,
											D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, nullptr,
											nullptr, &m_pWave ) );
}

//---------------------------------------------------------------------
void CWaterSurFace::update(float i_fElapsd)
{
}

//---------------------------------------------------------------------
void CWaterSurFace::draw( D3DXMATRIX* mat )
{
	IDirect3DDevice9* pDevice = AppContext::GetInstance()->getD3D9Device();
	const CShaderTask* pShaderTask = (CShaderTask*)CTaskMan::getInstance()->findTask("CShaderTask");
	_ASSERT( pShaderTask );
	CShaderSetValueDelegate* pDele = pShaderTask->getShaderDelegate(CShaderTask::S_I_WATER);
	ID3DXEffect* pEffect = pDele->getEffect();
	HRESULT hr = S_OK;

	pDele->preRenderSetParam(mat);
	_RET_CHECK( pEffect->SetTexture( "reflectTex", m_pReflectBuffer ) );
	_RET_CHECK( pEffect->SetTexture( "normalMap", m_pWave ) );
	_RET_CHECK( pEffect->SetTexture( "frameBuffer", AppContext::GetInstance()->getFrameBuffer() ) );

	UINT uiPass, uiNumPasses;
	_RET_CHECK( pEffect->SetTechnique( "render" ) );

	pDevice->SetStreamSource( 0, m_pVB, 0, sizeof( SKYBOX_VERTEX ) );
	pDevice->SetVertexDeclaration( m_pVertexDecl );
	
	_RET_CHECK( pEffect->Begin( &uiNumPasses, 0 ) );
	for( uiPass = 0; uiPass < uiNumPasses; uiPass++ )
	{
		pDele->passRenderSetParam(nullptr);
		_RET_CHECK( pEffect->BeginPass( uiPass ) );
	 	pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, s_nTriNum );
		_RET_CHECK( pEffect->EndPass() );
	}

	_RET_CHECK( pEffect->End() );
}

//---------------------------------------------------------------------
void CWaterSurFace::deviceReset()
{
	HRESULT hr;

	IDirect3DDevice9* pDevice = AppContext::GetInstance()->getD3D9Device();
	if( pDevice == nullptr )
	 	 return;
	

	// グリッド状の板を作る
	_RET_CHECK(pDevice->CreateVertexBuffer( s_nVerNum * sizeof( SKYBOX_VERTEX ),
										D3DUSAGE_WRITEONLY, 0,
										D3DPOOL_DEFAULT, &m_pVB, nullptr ) );

	SKYBOX_VERTEX* pVertex = nullptr;
	_RET_CHECK( m_pVB->Lock( 0, 0, ( void** )&pVertex, 0 ) );
	
	const int anPosOffX[6] = { 0,0,1,0,1,1 };
	const int anPosOffY[6] = { 0,1,0,1,1,0 };
	for( unsigned int y=0; y<s_nSubdivisionY; ++y )
	{
		const float fYPos = s_fEdgeLen * y;
		for( unsigned int x=0; x<s_nSubdivisionX; ++x )
		{
			const unsigned int nIndex = ((y*s_nSubdivisionY) + x)*6;
			for( int i=0; i<6; ++i )
			{
				const int nOffX = x+anPosOffX[i];
				const int nOffY = y+anPosOffY[i];
				pVertex[nIndex+i].m_vPos = D3DXVECTOR4( fStartX+s_fEdgeLen*nOffX, 0.f, fStartY+s_fEdgeLen*nOffY, 1.f );
				pVertex[nIndex+i].m_vTex = D3DXVECTOR3( fUvRatioX*nOffX, fUvRatioY*nOffY, 1.f );
			}
		}
	}
	 m_pVB->Unlock();
}
	
//---------------------------------------------------------------------
void CWaterSurFace::deviceLost()
{
	SAFE_RELEASE( m_pVB );
}
