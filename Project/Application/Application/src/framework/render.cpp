/**
	@file render.cpp
	@brief •`‰æˆ—‹K’èƒNƒ‰ƒX
*/

#include "stdafx.h"
#include "framework/render.h"
#include "appContext.h"

using namespace cpplinq;

//---------------------------------------------------------------------
RenderProcess::RenderProcess(const char* id
	, std::function<void()> pre
	, std::function<void()> render
	, std::function<void()> post
	, RENDER_PRIORITY priority
	)
	: Process<RenderProcess, RENDER_PRIORITY>(id, priority)
	, _pre(pre)
	, _render(render)
	, _post(post)
	, _context(nullptr)
{
	ID3D11Device* device = AppContext::GetInstance()->GetD3D11Device();
	HRESULT hr = device->CreateDeferredContext(0, &_context);
	_ASSERT(SUCCEEDED(hr));
}

//---------------------------------------------------------------------
RenderProcess::~RenderProcess()
{
	SAFE_RELEASE(_context);
}
