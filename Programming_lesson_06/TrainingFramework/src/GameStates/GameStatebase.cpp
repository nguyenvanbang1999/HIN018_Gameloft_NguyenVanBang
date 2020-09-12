/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSCredits.h"
#include "GSLose.h"
#include"GSWin.h"
#include"GSHelp.h"
#include"GSPause.h"
#include"GSOptions.h"

#include "GameStatebase.h"
#include "GameManager/PlayerData.h"

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateTypes stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case STATE_INVALID:
		break;
	case STATE_Intro:
		gs = std::make_shared<GSIntro>();
		break;
	case STATE_Menu:
		gs = std::make_shared<GSMenu>();
		break;
	case STATE_Play:
		gs = std::make_shared<GSPlay>(PlayerData::GetInstance()->m_lvl);
		break;
	case STATE_Credits:
		gs = std::make_shared<GSCredits>();
		break;
	case STATE_Lose:
		gs = std::make_shared<GSLose>();
		break;
	case STATE_Win:
		gs = std::make_shared<GSWin>();
		break;
	case STATE_Help:
		gs = std::make_shared<GSHelp>();
		break;
	case STATE_Pause:
		gs = std::make_shared<GSPause>();
		break;
	case STATE_Options:
		gs = std::make_shared<GSOptions>();
		break;
	default:
		break;
	}
	return gs;
}