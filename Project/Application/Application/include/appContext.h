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
class AppContext
{
public:
	typedef std::function<void(ID3D11Device*, IDXGISwapChain*, const DXGI_SURFACE_DESC*)>	ResizedSwapChainArg;
	typedef std::function<void()>															ReleasingSwapChainArg;
	typedef std::function<void(HWND, UINT, WPARAM, LPARAM, bool*)>							MsgProcChainArg;

public:
	/**
		@brief AppContext�̍쐬
	*/
	static AppContext* CreateInstance();

	/**
		@brief AppContext�̎擾
	*/
	static AppContext* GetInstance();

	/**
		@brief AppContext�̔j��
	*/
	static void DisposeInstance();
	
	/**
		@brief ����������
	*/
	void Init(ID3D11Device* device);

	/**
		@brief �X�V����
	*/
	void Update(float elapsd);

	/**
		@brief �`�揈��
	*/
	void Render();
		
	/**
		@brief DirectX�f�o�C�X�̎擾
	*/
	ID3D11Device* GetD3D11Device() const { return _device; }

	/**
		@brief�C�~�f�B�G�[�g�R���e�L�X�g�̎擾
	*/
	ID3D11DeviceContext* GetImmediateContext() { return _immediateContext; }

	/**
		@brief �J�����̃}�g���b�N�X����
	*/
    const D3DXMATRIX*  GetWorldMatrix() const { return &_worldMatrix; }
    const D3DXMATRIX*  GetViewMatrix() const { return &_viewMatrix; }
    const D3DXMATRIX*  GetProjMatrix() const { return &_projMatrix; }
	void SetWorldMatrix(const D3DXMATRIX* mat) { _worldMatrix = *mat; }
	void SetViewMatrix(const D3DXMATRIX* mat) { _viewMatrix = *mat; }
	void SetProjMatrix(const D3DXMATRIX* mat) { _projMatrix = *mat; }
	
	/**
		@brief �f�B���N�V���i�����C�g�̕����̑���
	*/
	const D3DXVECTOR3* GetDirectionalLightDir() const { return &_directionalLightDir; }
	void GetDirectionalLightDir(const D3DXVECTOR3* dir);

	/**
		@brief �J�����̎擾
	*/
	const CModelViewerCamera* GetCamera() const { return &_camera; }
	CModelViewerCamera* GetCamera() { return &_camera; }

	/**
		@brief �X�V�^�C���̎擾
	*/
	inline float GetElapsdTime() const { return _elapsd; }
	
	/**
		@brief �V�F�[�_�p�����[�^�̎擾
	*/
	const SShaderParam* GetShaderParam() const { return &_shaderParam; }
	SShaderParam* GetShaderParam() { return &_shaderParam; }
	
	/**
		@brief �V�F�[�_�p�����[�^�̐ݒ�
	*/
	void SetShaderParam( const SShaderParam* param );
	
	/**
		@brief �W���u�Ǘ��N���X�̎擾
	*/
	CJobManager* GetJobManager() { return _job; }
	
	/**
		@brief �`��Ǘ��N���X�̎擾
	*/
	CRenderManager* GetRenderManager() { return _render; }
	
	/**
		@brief �X���b�h�̒��p�Ǘ��N���X�̎擾
	*/
	CThreadChannel* GetThreadChannel() { return _threadChannel; }

	/**
		@brief ���T�C�Y���ɌĂ�
	*/
	void OnResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc );

	/**
		@brief �����[�X���ɌĂ�
	*/
	void OnReleasingSwapChain();
	
	/**
		@brief ���b�Z�[�W���������ɌĂ�
	*/
	void OnMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing );

	/**
		@brief ���T�C�Y���ɌĂ΂��CB�o�^
	*/
	size_t AddResizedSwapChainCB(ResizedSwapChainArg);
	void DeleteResizedSwapChainCB(size_t handle);
	
	/**
		@brief �����[�X���ɌĂ΂��CB�o�^
	*/
	size_t AddReleasingSwapChainCB(ReleasingSwapChainArg);
	void DeleteReleasingSwapChainCB(size_t handle);
	
	/**
		@brief ���b�Z�[�W�������ɌĂ΂��CB�o�^
	*/
	size_t AddMsgProcCB(MsgProcChainArg);
	void DeleteMsgProcCB(size_t handle);
	
	/**
		@brief cpu���̎擾
	*/
	unsigned int GetCpuCoreNum() const { return _cpuCoreNum; }

private:
	/**
		@brief �R���X�g���N�^
	*/
	AppContext();
		
	/**
		@brief �f�X�g���N�^
	*/
	~AppContext();

private:
	static AppContext*					_instance;			//!< ���g�ւ̃C���X�^���X�|�C���^ 
	
	// �V�X�e������̃R�[���o�b�N�֐��z��
	std::vector<ResizedSwapChainArg>	_resizedSwapChain;
	std::vector<ReleasingSwapChainArg>	_releasingSwapChain;
	std::vector<MsgProcChainArg>		_msgProc;

	CJobManager*						_job;					//!< �W���u�Ǘ�
	CRenderManager*						_render;				//!< �`��Ǘ�
	
	ID3D11Device*						_device;				//!< DirectX�f�o�C�X
	ID3D11DeviceContext*				_immediateContext;		//!< �C�~�f�B�G�[�g�̃R���e�L�X�g

	ShaderManager						_shaderManager;			//!< �V�F�[�_�[�}�l�[�W��
	SShaderParam						_shaderParam;			//!< �V�F�[�_�[�p�����[�^
	CModelViewerCamera					_camera;				//!< �J����
	D3DXMATRIX							_worldMatrix;			//!< ���[���h�}�g���b�N�X
	D3DXMATRIX							_viewMatrix;			//!< �r���[�}�g���b�N�X
	D3DXMATRIX							_projMatrix;			//!< �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3							_directionalLightDir;	//!< �f�B���N�V���i�����C�g����
	
    IDirect3DVertexBuffer9*				_vb;					//!< ���_���
    IDirect3DVertexDeclaration9*		_vertexDecl;			//!< ���_�f�[�^�v�f

	CThreadChannel*						_threadChannel;			//!< �X���b�h�̒��p�Ǘ�
	CStartJob*							_startJob;				//!< �J�n�W���u

	unsigned int						_cpuCoreNum;			//!< cpu�̃R�A��
	float								_elapsd;				//!< �PF�Ԃ̎���
	bool								_isInit;				//!< �������t���O
};

#endif // _APPLICATION_H_

