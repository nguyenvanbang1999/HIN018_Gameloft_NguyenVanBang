#pragma once
#include "Entity.h"
class Boom :public Entity 
{
public:
	Boom(std::shared_ptr<Vec2i> location);
	float m_time;
	void UpdateTime(float deltaTime);
};