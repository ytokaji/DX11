/**
	@file shader_param.h
	@brief シェーダパラメータ定義
*/

#ifndef _SHADER_PARAM_H_
#define _SHADER_PARAM_H_

static const char SHADER_PARAM_ID[4] = { 's','d','p','t'};

/**
	@brief 水面パラメータ
	@note 水面用パラメータ
*/
struct SOtherParam
{
	float		m_f3LightDir[3];		//!< ライト方向
	bool		m_bShaderReLoadReq;		//!< シェーダリロード要求
};

/**
	@brief 水面パラメータ
	@note 水面用パラメータ
*/
struct SWaterParam
{
	float		m_f3Color[4];			//!< 基本色味RGB
	float		m_f3SpecularColor[3];	//!< スペキュラ色味RGB
	float		m_f2RefrParams[2];		//!< 屈折のゆらぎの強さU,V(RefrScale)
	float		m_f2ReflParams[2];		//!< 反射のゆらぎの強さU,V(ReflScale)
	float		m_f2SpecularPower[2];	//!< スペキュラの強さ,絞り
	float		m_fReflBias;			//!< 反射効果のバイアス0～1(Fresnel.x)
	float		m_fFresnelPower;		//!< フレネルの強さ(Fresnel.y)
};

/**
	@brief ポストシェーダパラメータ
*/
struct SPostParam
{
	float m_fBrightness;				//!< 輝度
	float m_fFocusDistance;				//!< フォーカス距離
	float m_fFocusRange;				//!< フォーカス範囲
	bool m_bBloomUse;					//!< ブルームのON/OFF
	bool m_bDofUse;						//!< dofのON/OFF
};

/**
	@brief ファーシェーダパラメータ
*/
struct SFurParam
{
	float m_f3Color[3];					//!< 基本色味RGB
	float m_fDistance;					//!< 距離
	float m_fNum;						//!< 数
};

/**
	@brief バンプシェーダパラメータ
*/
struct SBumpParam
{
	float m_fSpecularPower;				//!< スペキュラの範囲
	float m_fSpecularRange;				//!< スペキュラの距離
};

/**
	@brief シェーダーパラメータ
	@note シェーダー用パラメータ
*/
struct SShaderParam
{
	char		m_chID[4];		//!< 識別子
	SOtherParam m_Others;		//!< その他
	SWaterParam	m_Water;		//!< 水面
	SPostParam	m_Post;			//!< ポスト
	SFurParam	m_Fur;			//!< ファー
	SBumpParam	m_Bump;			//!< バンプ
};
#endif		// _SHADER_PARAM_H_