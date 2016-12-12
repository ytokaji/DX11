/**
	@file scene.h
	@brief �V�[���̏����A�\��
*/

#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include "framework/render.h"

namespace DirectX {
	class GeometricPrimitive;
}

/**
	@brief �V�[��
	@note �V�[���Ǘ�
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
	std::unique_ptr<DirectX::GeometricPrimitive>    _teapod;	//!< �e�B�[�|�b�h
	std::unique_ptr<DirectX::GeometricPrimitive>    _torus;		//!< �g�[���X
};


#endif		// _SCENE_H_