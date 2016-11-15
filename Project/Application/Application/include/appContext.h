/**
	@file appContext.h
	@brief �A�v���P�[�V�����Ǘ�
*/
#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Core/DXUT.h"
#include "Optional/DXUTcamera.h"
#include "shader_param.h"
#include "shader/shaderManager.h"


class CJobManager;
class CRenderManager;
class CStartJob;
class CThreadChannel;

/**
	@brief �A�v���P�[�V�����Ǘ��N���X
	@note �V���O���g���ɂĊǗ�
*/
class CAppContext
{
public:
	typedef std::function<void(ID3D11Device*, IDXGISwapChain*, const DXGI_SURFACE_DESC*)>	ResizedSwapChainArg;
	typedef std::function<void()>															ReleasingSwapChainArg;
	typedef std::function<void(HWND, UINT, WPARAM, LPARAM, bool*)>							MsgProcChainArg;

public:
	/**
		@brief CAppContext�̍쐬
	*/
	static CAppContext* createInstance();

	/**
		@brief CAppContext�̎擾
	*/
	static CAppContext* getInstance();

	/**
		@brief CAppContext�̔j��
	*/
	static void disposeInstance();
	
	/**
		@brief ����������
	*/
	void init(ID3D11Device* i_pDevice);

	/**
		@brief �X�V����
	*/
	void update(float i_fElapsd);

	/**
		@brief �`�揈��
	*/
	void render();
		
	/**
		@brief DirectX�f�o�C�X�̎擾
	*/
	ID3D11Device* getD3D11Device() const { return m_pd3dDevice; }

	/**
		@brief�C�~�f�B�G�[�g�R���e�L�X�g�̎擾
	*/
	ID3D11DeviceContext* getImmediateContext() { return m_pImmediateContext; }

#if 0
	/**
		@brief �t���[���o�b�t�@�̎擾
		@note draw()�Ԃ̂ݗL���Ȓl���A��
	*/
	IDirect3DTexture9* getFrameBuffer() { return m_pFrameBuffrerTex; }
	IDirect3DTexture9* getDepthBuffer() { return m_pDepthBufferTex; }
#endif
	/**
		@brief �J�����̃}�g���b�N�X����
	*/
    const D3DXMATRIX*  getWorldMatrix() const { return &m_mWorld; }
    const D3DXMATRIX*  getViewMatrix() const { return &m_mView; }
    const D3DXMATRIX*  getProjMatrix() const { return &m_mProj; }
	void setWorldMatrix(const D3DXMATRIX* i_pMat) { m_mWorld = *i_pMat; }
	void setViewMatrix(const D3DXMATRIX* i_pMat) { m_mView = *i_pMat; }
    void setProjMatrix(const D3DXMATRIX* i_pMat) { m_mProj = *i_pMat; }
	
	/**
		@brief �f�B���N�V���i�����C�g�̕����̑���
	*/
	const D3DXVECTOR3* getDirectionalLightDir() const { return &m_vDirectionalLightDir; }
	void getDirectionalLightDir(const D3DXVECTOR3* i_pDir);

	/**
		@brief �J�����̎擾
	*/
	const CModelViewerCamera* getCamera() const { return &m_Camera; }
	CModelViewerCamera* getCamera() { return &m_Camera; }

	/**
		@brief �X�V�^�C���̎擾
	*/
	inline float getElapsdTime() const { return m_fElapsd; }
	
	/**
		@brief �V�F�[�_�p�����[�^�̎擾
	*/
	const SShaderParam* getShaderParam() const { return &m_ShaderParam; }
	SShaderParam* getShaderParam() { return &m_ShaderParam; }
	
	/**
		@brief �V�F�[�_�p�����[�^�̐ݒ�
	*/
	void setShaderParam( const SShaderParam* i_pParam );
	
	/**
		@brief �W���u�Ǘ��N���X�̎擾
	*/
	CJobManager* getJobManager() { return m_pJob; }
	
	/**
		@brief �`��Ǘ��N���X�̎擾
	*/
	CRenderManager* getRenderManager() { return m_pRender; }
	
	/**
		@brief �X���b�h�̒��p�Ǘ��N���X�̎擾
	*/
	CThreadChannel* getThreadChannel() { return m_pThreadChannel; }

	/**
		@brief ���T�C�Y���ɌĂ�
	*/
	void onResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc );

	/**
		@brief �����[�X���ɌĂ�
	*/
	void onReleasingSwapChain();
	
	/**
		@brief ���b�Z�[�W���������ɌĂ�
	*/
	void onMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing );

	/**
		@brief ���T�C�Y���ɌĂ΂��CB�o�^
	*/
	size_t addResizedSwapChainCB(ResizedSwapChainArg);
	void deleteResizedSwapChainCB(size_t i_nHandle);
	
	/**
		@brief �����[�X���ɌĂ΂��CB�o�^
	*/
	size_t addReleasingSwapChainCB(ReleasingSwapChainArg);
	void deleteReleasingSwapChainCB(size_t i_nHandle);
	
	/**
		@brief ���b�Z�[�W�������ɌĂ΂��CB�o�^
	*/
	size_t addMsgProcCB(MsgProcChainArg);
	void deleteMsgProcCB(size_t i_nHandle);
	
	/**
		@brief ���b�Z�[�W�������ɌĂ΂��CB�o�^
	*/
	unsigned int getCpuCoreNum() const { return m_nCpuCoreNum; }

private:
	/**
		@brief �R���X�g���N�^
	*/
	CAppContext();
		
	/**
		@brief �f�X�g���N�^
	*/
	~CAppContext();

private:
	static CAppContext*					m_pInstance;			//!< ���g�ւ̃C���X�^���X�|�C���^ 
	
	// �V�X�e������̃R�[���o�b�N�֐��z��
	std::vector<ResizedSwapChainArg>	m_fResizedSwapChain;
	std::vector<ReleasingSwapChainArg>	m_fReleasingSwapChain;
	std::vector<MsgProcChainArg>		m_fMsgProc;

	CJobManager*						m_pJob;					//!< �W���u�Ǘ�
	CRenderManager*						m_pRender;				//!< �`��Ǘ�
	
	ID3D11Device*						m_pd3dDevice;			//!< DirectX�f�o�C�X
	ID3D11DeviceContext*				m_pImmediateContext;	//!< �C�~�f�B�G�[�g�̃R���e�L�X�g

	ShaderManager						m_ShaderManager;
	SShaderParam						m_ShaderParam;
	CModelViewerCamera					m_Camera;
	D3DXMATRIX							m_mWorld;
	D3DXMATRIX							m_mView;
	D3DXMATRIX							m_mProj;
	D3DXVECTOR3							m_vDirectionalLightDir;
	
    IDirect3DVertexBuffer9*				m_pVB;					//!< ���_���
    IDirect3DVertexDeclaration9*		m_pVertexDecl;			//!< ���_�f�[�^�v�f
	
	IDirect3DTexture9*					m_pFrameBuffrerTex;		//!< �t���[���o�b�t�@�e�N�X�`��
	IDirect3DSurface9*					m_pFrameBuffrerSurf;	//!< �t���[���o�b�t�@�T�[�t�F�[�X
	IDirect3DTexture9*					m_pDepthBufferTex;		//!< �[�x�o�b�t�@�e�N�X�`��
	IDirect3DSurface9*					m_pDepthBufferSurf;		//!< �[�x�o�b�t�@�T�[�t�F�[�X

	CThreadChannel*						m_pThreadChannel;		//!< �X���b�h�̒��p�Ǘ�
	CStartJob*							m_pStartJob;			//!< �J�n�W���u

	unsigned int						m_nCpuCoreNum;			//!< cpu�̃R�A��
	float								m_fElapsd;				//!< �PF�Ԃ̎���
	bool								m_bIsInit;				//!< �������t���O
};

#endif // _APPLICATION_H_

