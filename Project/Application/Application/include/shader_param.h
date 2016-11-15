/**
	@file shader_param.h
	@brief �V�F�[�_�p�����[�^��`
*/

#ifndef _SHADER_PARAM_H_
#define _SHADER_PARAM_H_

static const char SHADER_PARAM_ID[4] = { 's','d','p','t'};

/**
	@brief ���ʃp�����[�^
	@note ���ʗp�p�����[�^
*/
struct SOtherParam
{
	float		m_f3LightDir[3];		//!< ���C�g����
	bool		m_bShaderReLoadReq;		//!< �V�F�[�_�����[�h�v��
};

/**
	@brief ���ʃp�����[�^
	@note ���ʗp�p�����[�^
*/
struct SWaterParam
{
	float		m_f3Color[4];			//!< ��{�F��RGB
	float		m_f3SpecularColor[3];	//!< �X�y�L�����F��RGB
	float		m_f2RefrParams[2];		//!< ���܂̂�炬�̋���U,V(RefrScale)
	float		m_f2ReflParams[2];		//!< ���˂̂�炬�̋���U,V(ReflScale)
	float		m_f2SpecularPower[2];	//!< �X�y�L�����̋���,�i��
	float		m_fReflBias;			//!< ���ˌ��ʂ̃o�C�A�X0�`1(Fresnel.x)
	float		m_fFresnelPower;		//!< �t���l���̋���(Fresnel.y)
};

/**
	@brief �|�X�g�V�F�[�_�p�����[�^
*/
struct SPostParam
{
	float m_fBrightness;				//!< �P�x
	float m_fFocusDistance;				//!< �t�H�[�J�X����
	float m_fFocusRange;				//!< �t�H�[�J�X�͈�
	bool m_bBloomUse;					//!< �u���[����ON/OFF
	bool m_bDofUse;						//!< dof��ON/OFF
};

/**
	@brief �t�@�[�V�F�[�_�p�����[�^
*/
struct SFurParam
{
	float m_f3Color[3];					//!< ��{�F��RGB
	float m_fDistance;					//!< ����
	float m_fNum;						//!< ��
};

/**
	@brief �o���v�V�F�[�_�p�����[�^
*/
struct SBumpParam
{
	float m_fSpecularPower;				//!< �X�y�L�����͈̔�
	float m_fSpecularRange;				//!< �X�y�L�����̋���
};

/**
	@brief �V�F�[�_�[�p�����[�^
	@note �V�F�[�_�[�p�p�����[�^
*/
struct SShaderParam
{
	char		m_chID[4];		//!< ���ʎq
	SOtherParam m_Others;		//!< ���̑�
	SWaterParam	m_Water;		//!< ����
	SPostParam	m_Post;			//!< �|�X�g
	SFurParam	m_Fur;			//!< �t�@�[
	SBumpParam	m_Bump;			//!< �o���v
};
#endif		// _SHADER_PARAM_H_