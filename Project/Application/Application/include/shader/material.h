/**
	@file material.h
	@brief シェーダファイルの管理
*/

#ifndef _MATELIAL_H_
#define _MATELIAL_H_

#include <D3DX9Effect.h>

/**
	@brief マテリアル
*/
class CMaterial
{
public:
	CMaterial()
		: m_pTex(nullptr)
	{
		sizeof(m_Mate, 0, sizeof(m_Mate));
	}

	~CMaterial()
	{
		SAFE_RELEASE(m_pTex);
	}

	D3DMATERIAL9		m_Mate;
	IDirect3DTexture9*	m_pTex;
};


#endif		// _MATELIAL_H_