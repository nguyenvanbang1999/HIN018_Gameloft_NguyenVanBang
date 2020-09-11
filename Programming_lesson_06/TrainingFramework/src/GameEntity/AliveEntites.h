#pragma once
#include"Entity.h"


#define		DOWN_DIRECTION	4 
#define		LEFT_DIRECTION	3 
#define		RIGHT_DIRECTION	2 
#define		TOP_DIRECTION	1
#define		STUN			0 


#define		PLAYER_SPEED	200
#define		NUM_FRAME_ALIVE		3
#define		ANIM_SPEED_ALIVE	0.2f
#define		NUM_LINE_ALIVE		5
class Map;
class AliveEnties :public Entity
{
public:
	
	AliveEnties(std::shared_ptr<Vec2i> location, int speed,int hp);
	void ChangedDirection(int dir);
	void Running();
	void Stop();
	void Stun();
	void UpdateTime(float deltaTime);
	void SubHp();
	

	int m_direction;
	bool m_running;
	int m_speed;
	int m_hp;
	float m_stunTime;
protected:
	
	


};