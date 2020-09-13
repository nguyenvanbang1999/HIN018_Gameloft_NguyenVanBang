#pragma once
#include"Singleton.h"
#include "soloud.h"
#include "soloud_speech.h"
#include "soloud_thread.h"
#include "soloud_Wav.h"
class SoundManager :public CSingleton<SoundManager>
{
public:
	SoundManager();

	bool m_SoundON;
	bool m_MusicON;

	SoLoud::Soloud m_soloud;

	SoLoud::Wav m_MenuBackgroundSound;
	SoLoud::Wav m_PlayBackgroundSound;
	SoLoud::Wav m_SpawnBom;
	SoLoud::Wav m_BomBang;
	SoLoud::Wav m_eatItem;
	SoLoud::Wav m_Lose;
	SoLoud::Wav m_Win;
	SoLoud::Wav m_EnemyStun;
	SoLoud::Wav m_Protected;

	void OnMusic();
	void OffMusic();
	void OnSound();
	void OffSound();
	void Clear();

	void BomBang();
	void EatItem();
	void SpawnBom();
	void PlayDeath();

	void EnemyStun();
	void Protected();
	void PlayWin();

	void PlayMenuBG();
	void PlayGamePlayBG();
	



};
