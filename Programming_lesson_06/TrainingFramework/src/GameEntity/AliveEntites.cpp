#include"AliveEntites.h"

class Map;

AliveEnties::AliveEnties(std::shared_ptr<Vec2i> location, int speed,int hp):Entity(location),m_speed(speed),m_direction(DOWN_DIRECTION),m_hp(hp),m_stunTime(0.0f)
{

}
void AliveEnties::ChangedDirection(int dir) 
{
	if (dir != m_direction) {
		m_direction = dir;
		m_animation->ChangedLine(dir);
	}
}
void AliveEnties::Running() 
{
	if (!m_running) m_running = true;
	if (m_animation->m_typeAnim != TYPE_LOOP) m_animation->ChangedType(TYPE_LOOP);

}
void AliveEnties::Stop() 
{
	m_running = false;
	m_animation->ChangedType(TYPE_SPRITE);
	m_animation->StopAnim();
}
void AliveEnties::Stun()
{
	m_stunTime = 1.0f;
	m_animation->StopAnim();
	
	m_animation->ChangedLine(STUN);
	
}
void AliveEnties::UpdateTime(float deltaTime)
{
	if (m_stunTime <= deltaTime)
	{
		m_stunTime = 0;
		m_animation->ChangedLine(m_direction);
		m_animation->m_frameTime = ANIM_SPEED_ALIVE;
	}
	else
	{
		m_stunTime -= deltaTime;
	}
}
void AliveEnties::SubHp() {
	m_hp--;
	if (m_hp <= 0)
	{
		
		m_isExist = false;
	}
}


