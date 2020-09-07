#include"AliveEntites.h"



AliveEnties::AliveEnties(int x, int y, int speed):Entity(x,y),m_speed(speed),m_direction(DOWN_DIRECTION)
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

void AliveEnties::Move(GLfloat deltatime) 
{
	//std::cout << deltatime << std::endl;
	if(m_running)
	switch (m_direction) 
	{
	case TOP_DIRECTION:
	{
		m_locationY -= deltatime * m_speed;
		break;
	}
	case DOWN_DIRECTION:
	{
		
		m_locationY += deltatime * m_speed;
		break;
	}
	case LEFT_DIRECTION:
	{
		
		m_locationX -= deltatime * m_speed;
		break;
	}
	case RIGHT_DIRECTION:
	{
		
		m_locationX += deltatime * m_speed;
		break;
	}
	default:
	{
		std::cout << "default" << std::endl;
		break;
	}

	}

}