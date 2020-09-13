#pragma once
#include"AliveEntites.h"
#include"Enemy.h"
class Map;

class Enemy3 :public Enemy
{
public:
	Enemy3(std::shared_ptr<Vec2i> location,int hp);
	void  SetDestination();
	void SubHp();
	void Skill(Map* map);

};
