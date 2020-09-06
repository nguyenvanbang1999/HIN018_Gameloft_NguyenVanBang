#pragma once
#include"Entity.h"

#define		DOWN_DIRECTION	4 
#define		LEFT_DIRECTION	3 
#define		RIGHT_DIRECTION	2 
#define		TOP_DIRECTION	1
#define		STUN			0 


#define		PLAYER_SPEED	20
#define		NUM_FRAME_ALIVE		3
#define		ANIM_SPEED		0.15f
#define		NUM_LINE_ALIVE		5

class AliveEnties :public Entity
{
public:
	
	AliveEnties(int x, int y, int speed);
	void ChangedDirection(int dir);
protected:
	int m_direction;
	int m_speed;


};