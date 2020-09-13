#pragma once
#include"AliveEntites.h"
#include"Enemy.h"
class Map;

class Enemy1 :public Enemy
{
public:
	Enemy1(std::shared_ptr<Vec2i> location);
	void SetDestination();
	
	
};
