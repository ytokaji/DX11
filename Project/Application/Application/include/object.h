/**
	@file object.h
	@brief オブジェクトモデルの管理、表示
*/

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "shader_task.h"
#include "shader_set_value.h"


/**
	@brief オブジェクトクラス
	@note オブジェクトモデルの管理、表示
*/
class CObject
{
public:
	CObject(const wchar_t* i_pchFileName, CShaderTask::SHADER_INDEX shader);
	virtual ~CObject();

	/**
		@brief 更新
	*/
	void Update( float i_fElapsd );

	/**
		@brief 描画
	*/
	void draw();

	/**
		@brief デバイスリセット時に実行
	*/
	void deviceReset();
	
	/**
		@brief デバイスロスト時に実行
	*/
	void deviceLost();

	/**
		@brief 各種取得
	*/
	D3DXVECTOR3* getScl() { return &m_vScl; }
	D3DXVECTOR3* getRot() { return &m_vRot; }
	D3DXVECTOR3* getTrn() { return &m_vTrn; }

	/*
		@brief 同パスを複数回びょうが
	*/
	void setPassDrawCount( unsigned int i_nCount ) { m_nPassDrawCount = i_nCount; }

private:
	void createMesh(const wchar_t* i_pchFileName);
	
private:
	std::vector< CShaderSetValueDelegate::CMaterialData >	m_aMaterial;	//!< マテリアル

	ID3DXMesh*					m_pMesh;			//!< モデルデータ

	D3DXVECTOR3					m_vScl;				//!< スケール
	D3DXVECTOR3					m_vRot;				//!< ローテーション
	D3DXVECTOR3					m_vTrn;				//!< トランス
	unsigned int				m_nPassDrawCount;	//!< 同パスを複数回びょうが
	CShaderTask::SHADER_INDEX	m_eShader;			//!< 使用シェーダー
};


#endif		// _OBJECT_H_