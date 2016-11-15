/**
	@file scene_task.h
	@brief シーンの処理、表示
*/

#ifndef _SCENE_TASK_H_
#define _SCENE_TASK_H_

#include "task.h"
#include <D3D9.h>

class CSkyBox;
class CObject;
class CWaterSurFace;

/**
	@brief シーンタスク
	@note シーン管理
*/
class CSceneTask	: public CTask
{
public:
	CSceneTask();
	virtual ~CSceneTask();

	/**
		@brief 登録されているタスクの更新処理を実行する
	*/
	virtual void run(void)
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

private:
	/// ステートごとの処理関数
	void _dummy(){};
	void _runInit();
	void _runMain();
	void _drawMain();

private:
	/// 処理関数定義
    typedef void (CSceneTask::*ProcFunc)();

	static const ProcFunc	m_pRunFunc[];			//!< 更新処理実行
	static const ProcFunc	m_pDrawFunc[];			//!< 更新処理実行
	
	IDirect3DTexture9*		m_pReflectMap;		//!< 反射テクスチャ
	IDirect3DSurface9*		m_pReflectSurf;		//!< 反射サーフェース

	std::vector<CObject*>	m_pObject;		//!< オブジェクト
	CObject*				m_pFurObject;	//!< オブジェクト
	CObject*				m_pBG;			//!< 背景
	CWaterSurFace*			m_pWater;		//!< 水面
};


#endif		// _SCENE_TASK_H_