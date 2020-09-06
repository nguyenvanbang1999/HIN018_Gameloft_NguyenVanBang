#include"AliveEntites.h"



AliveEnties::AliveEnties(int x, int y, int speed):Entity(x,y),m_speed(speed),m_direction(DOWN_DIRECTION)
{

}
void AliveEnties::ChangedDirection(int dir) {
	m_animation->ChangedLine(dir);
}