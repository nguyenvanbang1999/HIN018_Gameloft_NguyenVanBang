#include"PlayerData.h"

PlayerData::PlayerData()
{
	m_lvl = 1;
	m_player_numBom = 1;
	m_player_power = 1;
	m_player_speed = 200;
	m_player_hp = 3;
}

void PlayerData::Reset()
{
	m_lvl = 1;
	m_player_numBom = 1;
	m_player_power = 1;
	m_player_speed = 200;
	m_player_hp = 3;
}