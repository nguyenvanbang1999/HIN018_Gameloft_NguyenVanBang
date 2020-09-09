#include"AliveEntites.h"

class Map;

AliveEnties::AliveEnties(std::shared_ptr<Vec2i> location, int speed):Entity(location),m_speed(speed),m_direction(DOWN_DIRECTION)
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



