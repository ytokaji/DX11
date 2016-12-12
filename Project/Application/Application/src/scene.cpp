/**
	@file scene.h
	@brief シーンの処理、表示
*/

#include "stdafx.h"
#include "scene.h"
#include "appContext.h"
#include "framework/renderManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//---------------------------------------------------------------------
Scene::Scene()
	: _render("Scene", nullptr, std::bind(&Scene::RenderAsync, this), nullptr, RENDER_PRIORITY::DEFAULT)
	, _teapod(nullptr)
	, _torus(nullptr)
{
	Init();
}

//---------------------------------------------------------------------
Scene::~Scene()
{
	_teapod.reset();
	_torus.reset();
}

//---------------------------------------------------------------------
void Scene::Init()
{
	// シェイプの構築
	_teapod = GeometricPrimitive::CreateTeapot(_render.GetDeviceContext());
	_torus = GeometricPrimitive::CreateTorus(_render.GetDeviceContext());

	// 登録
	AppContext::GetInstance()->GetRenderManager()->AddRender(&_render);
}

//---------------------------------------------------------------------
void Scene::Exec()
{
}

//---------------------------------------------------------------------
void Scene::RenderAsync()
{
	DirectX::SimpleMath::Matrix world = AppContext::GetInstance()->GetCameraWorldMatrix();
	DirectX::SimpleMath::Matrix view = AppContext::GetInstance()->GetViewMatrix();
	DirectX::SimpleMath::Matrix proj = AppContext::GetInstance()->GetProjMatrix();
	_teapod->Draw(Matrix::CreateTranslation(5.f, 0.f, 3.f)*world, view, proj, Colors::Goldenrod);
	_torus->Draw(Matrix::CreateTranslation(-3.f, 3.f, -3.f)*world, view, proj, Colors::Gray, nullptr, true);
}

