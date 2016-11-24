/**
	@file startJob.cpp
	@brief 開始時の初期ジョブ
*/

#include "stdafx.h"

#include "startJob.h"
#include "appContext.h"
#include "hud.h"
#include "grid.h"


//---------------------------------------------------------------------
StartJob::StartJob()
	:	Job				("StartJob")
	,	_state			(STATE::INIT)
	,	_hub			(nullptr)
	,	_grid			(nullptr)
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
		_hub.reset(new Hud());
		_grid.reset(new Grid());

		_state = STATE::RUN;
		break;

	default:
		break;
	}
}


