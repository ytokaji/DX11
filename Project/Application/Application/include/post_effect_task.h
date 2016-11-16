/**
	@file post_effect_task.h
	@brief �|�X�g�G�t�F�N�g�̏����A�\��
*/

#ifndef _POST_EFFECT_H_
#define _POST_EFFECT_H_

#include <D3D9.h>
#include <D3dx9math.h>
#include "task.h"
#include "shader_task.h"

/**
	@brief �|�X�g�G�t�F�N�g�^�X�N
	@note �|�X�g�G�t�F�N�g�Ǘ�
*/
class CPostEffectTask	: public CTask
{
public:
	CPostEffectTask();
	virtual ~CPostEffectTask();

	/**
		@brief �o�^����Ă���^�X�N�̍X�V���������s����
	*/
	virtual void Run(void)
	{
		unsigned int n=getSubTask();
		_ASSERT( n<STATE_MAX );
		(this->*m_pRunFunc[n])();
	}

	/**
		@brief �o�^����Ă���^�X�N�̕`�揈�������s����
	*/
	virtual void draw(void)
	{
		unsigned int n=getSubTask();
		_ASSERT( n<STATE_MAX );
		(this->*m_pDrawFunc[n])();
	}

	/**
		@brief �f�o�C�X���Z�b�g���Ɏ��s
	*/
	virtual void deviceReset();
	
	/**
		@brief �f�o�C�X���X�g���Ɏ��s
	*/
	virtual void deviceLost();

private:
	enum
	{
		STATE_INIT,
		STATE_MAIN,

		STATE_MAX
	};
	
	/**
		@brief �`��o�b�t�@�C���f�b�N�X
	*/
	enum BufferIndex
	{
		BufferIndex_32x32,
		BufferIndex_64x64,
		BufferIndex_96x96,
		BufferIndex_256x256,

		BufferIndex_FrameBuffer,

		BufferIndex_Max
	};

private:
	/// �X�e�[�g���Ƃ̏����֐�
	void _dummy(){};
	void _runInit();
	void _runMain();
	void _drawMain();
	
	/// �`��
	void drawSurface(IDirect3DSurface9* i_pRenderSurf,unsigned int i_nWindwW, unsigned int i_nWindwH, 
						CShaderTask::SHADER_INDEX i_eS_I, bool i_bClear, const char* i_pchTechnique );

private:
	/// �����֐���`
    typedef void (CPostEffectTask::*ProcFunc)();
	static const ProcFunc			m_pRunFunc[];			//!< �X�V�������s
	static const ProcFunc			m_pDrawFunc[];			//!< �X�V�������s
	static const unsigned int		m_nBufferSize[BufferIndex_Max][2];		//!< �o�b�t�@�T�C�Y

    IDirect3DVertexBuffer9*			m_pVB;					//!< ���_���
    IDirect3DVertexDeclaration9*	m_pVertexDecl;			//!< ���_�f�[�^�v�f

	/// �k���o�b�t�@
	IDirect3DTexture9*				m_pFilterTex[BufferIndex_Max];
	IDirect3DSurface9*				m_pFilterSurf[BufferIndex_Max];
};


#endif		// _POST_EFFECT_H_