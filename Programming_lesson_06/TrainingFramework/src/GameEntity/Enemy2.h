#pragma once
#include"AliveEntites.h"
#include"Enemy.h"
class Map;

class Enemy2 :public Enemy
{
public:
	Enemy2(std::shared_ptr<Vec2i> location);
	void  SetDestination();
	void SubHp();
	void Skill(Map* map);

};
