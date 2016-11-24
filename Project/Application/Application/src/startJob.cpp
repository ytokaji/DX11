/**
	@file startJob.cpp
	@brief 開始時の初期ジョブ
*/

#include "stdafx.h"

#include "startJob.h"
#include "appContext.h"
#include "hud.h"
#include "framework/processManager.h"
#include "framework/renderManager.h"
#include "framework/jobManager.h"


//---------------------------------------------------------------------
StartJob::StartJob()
	:	Job				("StartJob")
	,	_state			(STATE::INIT)
{
}

//---------------------------------------------------------------------
StartJob::~StartJob()
{
}

//---------------------------------------------------------------------
void StartJob::Update()
{
	switch( _state )
	{
	case STATE::INIT:
		AppContext::GetInstance()->GetRenderManager()->AddRender(new hud());
		_state = STATE::RUN;
		break;

	default:
		break;
	}
}


