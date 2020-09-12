#include"SoundManager.h"
SoundManager::SoundManager() {
	//printf("goi");
	m_SoundON=true;
	m_MusicON=true;
	m_soloud.init();

	m_MenuBackgroundSound.load("..\\Data\\Audio\\Funnybackground.wav");
	m_MenuBackgroundSound.setLooping(true);
	m_PlayBackgroundSound.load("..\\Data\\Audio\\GamePlaysound.wav");
	m_PlayBackgroundSound.setLooping(true);


	m_BomBang.load("..\\Data\\Audio\\BomBang.wav");
	m_eatItem.load("..\\Data\\Audio\\ItemDing.wav");
	m_Lose.load("..\\Data\\Audio\\Death.wav");
	m_SpawnBom.load("..\\Data\\Audio\\Bit.wav");
}
void SoundManager::OnMusic()
{
	printf("OnMusic\n");
	m_MusicON = true;
}
void SoundManager::OffMusic()
{
	printf("OffMusic\n");
	m_MusicON = false;

}
void SoundManager::OnSound()
{
	printf("OnSound\n");
	m_SoundON = true;
}
void SoundManager::OffSound()
{
	printf("OffSound\n");
	m_SoundON = false;
}

void SoundManager::Clear()
{
	m_soloud.stopAll();
}

void SoundManager::BomBang()
{
	if (!m_SoundON) return;
	m_soloud.play(m_BomBang);
}
void SoundManager::EatItem()
{
	if (!m_SoundON) return;
	m_soloud.play(m_eatItem);
}
void SoundManager::SpawnBom()
{
	if (!m_SoundON) return;
	m_soloud.play(m_SpawnBom);
}
void SoundManager::PlayDeath()
{
	if (!m_MusicON) return;
	m_soloud.play(m_Lose);
}
void SoundManager::PlayMenuBG()
{
	if (!m_MusicON) return;
	else
	{
		m_soloud.play(m_MenuBackgroundSound);
	}
}
void SoundManager::PlayGamePlayBG()
{
	if (!m_MusicON) return;
	m_soloud.play(m_PlayBackgroundSound);
}