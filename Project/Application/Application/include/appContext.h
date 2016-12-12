/**
	@file appContext.h
	@brief �A�v���P�[�V�����Ǘ�
*/
#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "shader_param.h"
#include "shader/shaderManager.h"


class JobManager;
class RenderManager;
class StartJob;
class ThreadChannel;

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
	inline const DirectX::SimpleMath::Matrix  GetCameraWorldMatrix() const { return _camera.GetWorldMatrix(); }
	inline const DirectX::SimpleMath::Matrix  GetViewMatrix() const { return _camera.GetViewMatrix(); }
	inline const DirectX::SimpleMath::Matrix  GetProjMatrix() const { return _camera.GetProjMatrix(); }

	/**
		@brief �f�B���N�V���i�����C�g�̕����̑���
	*/
	const DirectX::SimpleMath::Vector3* GetDirectionalLightDir() const { return &_directionalLightDir; }
	void SetDirectionalLightDir(const DirectX::SimpleMath::Vector3& dir);

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
	@brief �V�F�[�_�[�}�l�[�W���̎擾
	*/
	const ShaderManager* GetShaderManager() const { return &_shaderManager; }
	ShaderManager* GetShaderManager() { return &_shaderManager; }

	/**
		@brief �W���u�Ǘ��N���X�̎擾
	*/
	JobManager* GetJobManager() { return _job; }
	
	/**
		@brief �`��Ǘ��N���X�̎擾
	*/
	RenderManager* GetRenderManager() { return _render; }
	
	/**
		@brief �X���b�h�̒��p�Ǘ��N���X�̎擾
	*/
	ThreadChannel* GetThreadChannel() { return _threadChannel; }

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
	uintptr_t AddResizedSwapChainCB(ResizedSwapChainArg);
	void DeleteResizedSwapChainCB(uintptr_t handle);
	
	/**
		@brief �����[�X���ɌĂ΂��CB�o�^
	*/
	uintptr_t AddReleasingSwapChainCB(ReleasingSwapChainArg);
	void DeleteReleasingSwapChainCB(uintptr_t handle);
	
	/**
		@brief ���b�Z�[�W�������ɌĂ΂��CB�o�^
	*/
	uintptr_t AddMsgProcCB(MsgProcChainArg);
	void DeleteMsgProcCB(uintptr_t handle);
	
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

	JobManager*							_job;					//!< �W���u�Ǘ�
	RenderManager*						_render;				//!< �`��Ǘ�
	
	ID3D11Device*						_device;				//!< DirectX�f�o�C�X
	ID3D11DeviceContext*				_immediateContext;		//!< �C�~�f�B�G�[�g�̃R���e�L�X�g

	ShaderManager						_shaderManager;			//!< �V�F�[�_�[�}�l�[�W��
	SShaderParam						_shaderParam;			//!< �V�F�[�_�[�p�����[�^
	CModelViewerCamera					_camera;				//!< �J����
	DirectX::SimpleMath::Vector3		_directionalLightDir;	//!< �f�B���N�V���i�����C�g����

	ThreadChannel*						_threadChannel;			//!< �X���b�h�̒��p�Ǘ�
	StartJob*							_startJob;				//!< �J�n�W���u

	unsigned int						_cpuCoreNum;			//!< cpu�̃R�A��
	float								_elapsd;				//!< �PF�Ԃ̎���
	bool								_isInit;				//!< �������t���O
};

#endif // _APPLICATION_H_

