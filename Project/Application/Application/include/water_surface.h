/**
	@file water_surface.h
	@brief ����
*/

#ifndef _WATER_SURFACE_H_
#define _WATER_SURFACE_H_

#include <D3dx9math.h>

class CShaderTask;

/**
	@brief �X�J�C�{�b�N�X�N���X
	@note �w�i�̃X�J�C�{�b�N�X
*/
class CWaterSurFace
{
public:
	CWaterSurFace();
	virtual ~CWaterSurFace();

	/**
		@brief ������
	*/
	void init();

	/**
		@brief �X�V
	*/
	void update( float i_fElapsd );

	/**
		@brief �`��
	*/
	void draw( D3DXMATRIX* i_pMat=nullptr );

	/**
		@brief �f�o�C�X���Z�b�g���Ɏ��s
	*/
	void deviceReset();
	
	/**
		@brief �f�o�C�X���X�g���Ɏ��s
	*/
	void deviceLost();

	/**
		@brief ���˃e�N�X�`���̐ݒ�
	*/
	void setReflectTex( IDirect3DTexture9* i_pTex ) { m_pReflectBuffer = i_pTex; }

private:
    IDirect3DVertexBuffer9*			m_pVB;				//!< ���_���
    IDirect3DVertexDeclaration9*	m_pVertexDecl;		//!< ���_�f�[�^�v�f
	IDirect3DTexture9*				m_pReflectBuffer;	//!< ���˃e�N�X�`��
	IDirect3DTexture9*				m_pWave;			//!< ���ʃm�[�}���}�b�v
};


#endif		// _WATER_SURFACE_H__