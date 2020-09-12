#include"PlayerData.h"

PlayerData::PlayerData()
{
	m_lvl = 1;
	m_player_numBom = 1;
	m_player_power = 1;
	m_player_speed = 200;
	m_player_hp = 3;

	m_lvlStastLVL = 1;
	m_player_numBomStastLVL = 1;
	m_player_powerStastLVL = 1;
	m_player_speedStastLVL = 200;
	m_player_hpStastLVL = 3;
}

void PlayerData::Reset()
{
	m_lvl = 1;
	m_player_numBom = 1;
	m_player_power = 1;
	m_player_speed = 200;
	m_player_hp = 3;
}
void PlayerData::Update()
{
	m_lvlStastLVL = m_lvl;
	m_player_numBomStastLVL = m_player_numBom;
	m_player_powerStastLVL = m_player_power;
	m_player_speedStastLVL = m_player_speed;
	m_player_hpStastLVL = m_player_hp;
}
void PlayerData::Restart()
{
	m_lvl = m_lvlStastLVL;
	m_player_numBom = m_player_numBomStastLVL;
	m_player_power = m_player_powerStastLVL;
	m_player_speed = m_player_speedStastLVL;
	m_player_hp = m_player_hpStastLVL;
}