/**
	@file object.h
	@brief オブジェクトモデルの管理、表示
*/

#include "stdafx.h"
#include "object.h"
#include "Core/DXUT.h"
#include "application.h"
#include "shader_set_value.h"

namespace
{
	// 頂点情報の宣言
	D3DVERTEXELEMENT9 g_aDecl[] =
	{
		 { 0, 0,	D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	// ポジション
		 { 0, 16,	D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },	// normal
		 { 0, 28,	D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },	// tangent
		 { 0, 40,	D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },	// binormal
		 { 0, 52,	D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// UV
		 D3DDECL_END()
	};
}

//---------------------------------------------------------------------
CObject::CObject(const wchar_t* i_pchFileName, CShaderTask::SHADER_INDEX shader)
	:	m_pMesh				( nullptr )
	,	m_vScl				( 1.f, 1.f, 1.f )
	,	m_vRot				( 0.f, 0.f, 0.f )
	,	m_vTrn				( 0.f, 0.f, 0.f )
	,	m_nPassDrawCount	( 1 )
	,	m_eShader			( shader )
{
	_ASSERT( m_eShader < CShaderTask::S_I_MAX );
	createMesh( i_pchFileName );
}

//---------------------------------------------------------------------
CObject::~CObject()
{
	deviceLost();
	
	SAFE_RELEASE( m_pMesh );
}

//---------------------------------------------------------------------
void CObject::update(float i_fElapsd)
{
}

//---------------------------------------------------------------------
void CObject::draw()
{
	const CShaderTask* pShaderTask = (CShaderTask*)CTaskMan::getInstance()->findTask("CShaderTask");
	_ASSERT( pShaderTask );
	CShaderSetValueDelegate* pDele = pShaderTask->getShaderDelegate(m_eShader);
	ID3DXEffect* pEffect = pDele->getEffect();
	HRESULT hr = S_OK;

	// マトリクス更新
	D3DXMATRIX mMat, mMatScl, mMatRot;
	D3DXMatrixScaling( &mMatScl, m_vScl.x, m_vScl.y, m_vScl.z );
	D3DXMatrixRotationYawPitchRoll( &mMatRot, m_vRot.x, m_vRot.y, m_vRot.z );
	D3DXMatrixMultiply( &mMat, &mMatScl, &mMatRot );
	
	const D3DXMATRIX mTmpWorld = *AppContext::GetInstance()->getWorldMatrix();
	D3DXMatrixMultiply( &mMat, &mMat, &mTmpWorld );
	mMat._41 += m_vTrn.x; mMat._42 += m_vTrn.y; mMat._43 += m_vTrn.z; mMat._44 = 1.f;

	pDele->preRenderSetParam(&mMat);

	// 描画
	UINT uiPass, uiNumPasses;
	_RET_CHECK( pEffect->SetTechnique( "render" ) );
	const unsigned int nMax = m_aMaterial.size();
	for( unsigned int i=0; i<nMax; ++i )
	{
		pDele->renderSetParam(&m_aMaterial[i]);
		for( unsigned int nCount=0; nCount<m_nPassDrawCount; ++nCount )
		{
			pDele->passRenderSetParam(&m_aMaterial[i]);
			_RET_CHECK( pEffect->Begin( &uiNumPasses, 0 ) );
			for( uiPass = 0; uiPass < uiNumPasses; uiPass++ )
			{
				_RET_CHECK( pEffect->BeginPass( uiPass ) );
				m_pMesh->DrawSubset( i );
				_RET_CHECK( pEffect->EndPass() );
			}
			_RET_CHECK( pEffect->End() );
		}
    }
}

//---------------------------------------------------------------------
void CObject::deviceReset()
{
}
	
//---------------------------------------------------------------------
void CObject::deviceLost()
{
}

//---------------------------------------------------------------------
void CObject::createMesh(const wchar_t* i_pchFileName)
{
	IDirect3DDevice9* pDevice = AppContext::GetInstance()->getD3D9Device();
	HRESULT hr;
	LPD3DXBUFFER pMateBuffer = nullptr;
    LPD3DXBUFFER pAdjacencyBuffer = nullptr;
	DWORD mateNum;

	// メッシュロード
	_RET_CHECK_ASSERT( D3DXLoadMeshFromX( i_pchFileName, D3DXMESH_MANAGED,
							pDevice, &pAdjacencyBuffer, &pMateBuffer, nullptr, &mateNum, &m_pMesh ));

	
    // メッシュ最適化
    _RET_CHECK_ASSERT( m_pMesh->OptimizeInplace(
                D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
                ( DWORD* )pAdjacencyBuffer->GetBufferPointer(), nullptr, nullptr, nullptr ) );

	
	// 頂点情報再計算
	{
		LPD3DXMESH pTempMesh;

		_RET_CHECK_ASSERT( m_pMesh->CloneMesh( m_pMesh->GetOptions(),
									g_aDecl,
									pDevice, &pTempMesh ));
		SAFE_RELEASE( m_pMesh );

//		hr = D3DXComputeNormals(pTempMesh, ( DWORD* )pAdjacencyBuffer->GetBufferPointer());
        hr = D3DXComputeTangentFrameEx( pTempMesh,
                                        D3DDECLUSAGE_TEXCOORD, 0,
                                        D3DDECLUSAGE_TANGENT, 0,
                                        D3DDECLUSAGE_BINORMAL, 0,
                                        D3DDECLUSAGE_NORMAL, 0,
                                        0, ( DWORD* )pAdjacencyBuffer->GetBufferPointer(),
                                        0.01f, 0.25f, 0.01f,
                                        &m_pMesh, nullptr );
	
		SAFE_RELEASE( pTempMesh );
	}

	// マテリアル解析
	if( mateNum > 0 )
	{
		m_aMaterial.resize( mateNum );
		for( unsigned int i=0; i<mateNum; ++i )
		{
			D3DXMATERIAL* pMate = (D3DXMATERIAL*)(pMateBuffer->GetBufferPointer())+i;
			m_aMaterial[i].m_Mate = pMate->MatD3D;
			
			// テクスチャ
			if( pMate->pTextureFilename )
			{
				wchar_t strPath[MAX_PATH];
				wchar_t strTexture[MAX_PATH];
				MultiByteToWideChar( CP_ACP, 0, pMate->pTextureFilename, -1, strTexture, MAX_PATH );
				wcscpy_s( strPath, MAX_PATH, i_pchFileName );
				wchar_t* pchPos = wcsrchr( strPath, L'/' );
				if( pchPos == nullptr ) pchPos = wcsrchr( strPath, L'\\' );
				if( pchPos != nullptr )
				{
					pchPos[1] = 0;
					wcsncat_s( strPath, strTexture, _TRUNCATE );
				}
				else
				{
					wcscpy_s( strPath, MAX_PATH, strTexture );
				}

				hr = D3DXCreateTextureFromFile( pDevice, strPath, &m_aMaterial[i].m_pTex );
				if( hr != D3D_OK )
				{
					_WARNING(0, pMate->pTextureFilename);
					SAFE_RELEASE( m_aMaterial[i].m_pTex );
				}
			}
		}
	}
    SAFE_RELEASE( pMateBuffer );
    SAFE_RELEASE( pAdjacencyBuffer );
}
