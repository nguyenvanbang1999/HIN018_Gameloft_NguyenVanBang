#pragma once
#include"AliveEntites.h"
class Map;

class Enemy :public AliveEnties
{
public:
	Enemy(std::shared_ptr<Vec2i> location,int hp);
	std::shared_ptr<Vec2i> m_destination;

	bool m_usingSkill;

	void Move(GLfloat deltatime, Map *map);
	void virtual SetDestination();
	void virtual SubHp();
	void RandDir();

	void virtual Skill(Map* map);
};
