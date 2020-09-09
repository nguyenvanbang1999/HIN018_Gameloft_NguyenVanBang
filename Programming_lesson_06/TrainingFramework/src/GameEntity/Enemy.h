#pragma once
#include"AliveEntites.h"
class Map;

class Enemy :public AliveEnties
{
public:
	Enemy(std::shared_ptr<Vec2i> location);
	void Move(GLfloat deltatime, Map *map);
	void RandDir();
};
