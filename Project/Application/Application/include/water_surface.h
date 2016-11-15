/**
	@file water_surface.h
	@brief 水面
*/

#ifndef _WATER_SURFACE_H_
#define _WATER_SURFACE_H_

#include <D3dx9math.h>

class CShaderTask;

/**
	@brief スカイボックスクラス
	@note 背景のスカイボックス
*/
class CWaterSurFace
{
public:
	CWaterSurFace();
	virtual ~CWaterSurFace();

	/**
		@brief 初期化
	*/
	void init();

	/**
		@brief 更新
	*/
	void update( float i_fElapsd );

	/**
		@brief 描画
	*/
	void draw( D3DXMATRIX* i_pMat=nullptr );

	/**
		@brief デバイスリセット時に実行
	*/
	void deviceReset();
	
	/**
		@brief デバイスロスト時に実行
	*/
	void deviceLost();

	/**
		@brief 反射テクスチャの設定
	*/
	void setReflectTex( IDirect3DTexture9* i_pTex ) { m_pReflectBuffer = i_pTex; }

private:
    IDirect3DVertexBuffer9*			m_pVB;				//!< 頂点情報
    IDirect3DVertexDeclaration9*	m_pVertexDecl;		//!< 頂点データ要素
	IDirect3DTexture9*				m_pReflectBuffer;	//!< 反射テクスチャ
	IDirect3DTexture9*				m_pWave;			//!< 水面ノーマルマップ
};


#endif		// _WATER_SURFACE_H__