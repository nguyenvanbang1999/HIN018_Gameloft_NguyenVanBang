#pragma once
#include "Entity.h"
class Boom :public Entity 
{
public:
	Boom(std::shared_ptr<Vec2i> location,int power);
	float m_time;
	void UpdateTime(float deltaTime);
	int m_power;
	bool m_checkBang;
};