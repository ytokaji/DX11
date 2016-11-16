/**
	@file post_effect_task.h
	@brief ポストエフェクトの処理、表示
*/

#ifndef _POST_EFFECT_H_
#define _POST_EFFECT_H_

#include <D3D9.h>
#include <D3dx9math.h>
#include "task.h"
#include "shader_task.h"

/**
	@brief ポストエフェクトタスク
	@note ポストエフェクト管理
*/
class CPostEffectTask	: public CTask
{
public:
	CPostEffectTask();
	virtual ~CPostEffectTask();

	/**
		@brief 登録されているタスクの更新処理を実行する
	*/
	virtual void Run(void)
	{
		unsigned int n=getSubTask();
		_ASSERT( n<STATE_MAX );
		(this->*m_pRunFunc[n])();
	}

	/**
		@brief 登録されているタスクの描画処理を実行する
	*/
	virtual void draw(void)
	{
		unsigned int n=getSubTask();
		_ASSERT( n<STATE_MAX );
		(this->*m_pDrawFunc[n])();
	}

	/**
		@brief デバイスリセット時に実行
	*/
	virtual void deviceReset();
	
	/**
		@brief デバイスロスト時に実行
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
		@brief 描画バッファインデックス
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
	/// ステートごとの処理関数
	void _dummy(){};
	void _runInit();
	void _runMain();
	void _drawMain();
	
	/// 描画
	void drawSurface(IDirect3DSurface9* i_pRenderSurf,unsigned int i_nWindwW, unsigned int i_nWindwH, 
						CShaderTask::SHADER_INDEX i_eS_I, bool i_bClear, const char* i_pchTechnique );

private:
	/// 処理関数定義
    typedef void (CPostEffectTask::*ProcFunc)();
	static const ProcFunc			m_pRunFunc[];			//!< 更新処理実行
	static const ProcFunc			m_pDrawFunc[];			//!< 更新処理実行
	static const unsigned int		m_nBufferSize[BufferIndex_Max][2];		//!< バッファサイズ

    IDirect3DVertexBuffer9*			m_pVB;					//!< 頂点情報
    IDirect3DVertexDeclaration9*	m_pVertexDecl;			//!< 頂点データ要素

	/// 縮小バッファ
	IDirect3DTexture9*				m_pFilterTex[BufferIndex_Max];
	IDirect3DSurface9*				m_pFilterSurf[BufferIndex_Max];
};


#endif		// _POST_EFFECT_H_