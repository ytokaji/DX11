/**
	@file startJob.cpp
	@brief �J�n���̏����W���u
*/

#include "stdafx.h"

#include "startJob.h"
#include "appContext.h"
#include "hud.h"
#include "framework/processManager.h"


//---------------------------------------------------------------------
StartJob::StartJob()
	:	Job				("StartJob")
	,	_hub			( nullptr )
	,	_state			(STATE::STATE_INIT)
{
}

//---------------------------------------------------------------------
StartJob::~StartJob()
{
	SAFE_TERMINATE(_hub);
}

//---------------------------------------------------------------------
void StartJob::Update()
{
	switch( _state )
	{
	case STATE::STATE_INIT:
		AppContext::GetInstance()->GetRenderManager()->AddRender(_hub = new CHud());
		_state = STATE::STATE_RUN;
		break;

	default:
		break;
	}
}


