/**
	@file startJob.cpp
	@brief 開始時の初期ジョブ
*/

#include "stdafx.h"

#include "startJob.h"
#include "appContext.h"
#include "hud.h"
#include "framework/processManager.h"


//---------------------------------------------------------------------
CStartJob::CStartJob()
	:	CJob				("CStartJob")
	,	m_pHub				( nullptr )
	,	m_nState			( STATE_INIT )
{
}

//---------------------------------------------------------------------
CStartJob::~CStartJob()
{
	SAFE_TERMINATE(m_pHub);
}

//---------------------------------------------------------------------
void CStartJob::update()
{
	switch( m_nState )
	{
	case STATE_INIT:
		CAppContext::getInstance()->getRenderManager()->addRender(m_pHub = new CHud());
		m_nState = STATE_RUN;
		break;

	default:
		break;
	}
}


