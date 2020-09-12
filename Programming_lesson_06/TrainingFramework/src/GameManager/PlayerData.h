#pragma once
#include"Singleton.h"
class PlayerData :public CSingleton<PlayerData> {
public:
	PlayerData();

	int m_lvl ;
	int m_player_numBom ;
	int m_player_power ;
	int m_player_speed ;
	int m_player_hp ;

	int m_lvlStastLVL;
	int m_player_numBomStastLVL;
	int m_player_powerStastLVL;
	int m_player_speedStastLVL;
	int m_player_hpStastLVL;

	void Reset();
	void Update();
	void Restart();
};