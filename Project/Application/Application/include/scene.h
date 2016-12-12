/**
	@file scene.h
	@brief シーンの処理、表示
*/

#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include "framework/render.h"

namespace DirectX {
	class GeometricPrimitive;
}

/**
	@brief シーン
	@note シーン管理
*/
class Scene
{
public:
	Scene();
	virtual ~Scene();

private:
	void Init();
	void Exec();
	void RenderAsync();

private:
	RenderProcess									_render;
	std::unique_ptr<DirectX::GeometricPrimitive>    _teapod;	//!< ティーポッド
	std::unique_ptr<DirectX::GeometricPrimitive>    _torus;		//!< トーラス
};


#endif		// _SCENE_H_