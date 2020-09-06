#pragma once
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Block.h"

#include<vector>
#include <memory>
#define		MAP_TOP_GUI		100
class Map 
{
public:
	Map();
	
	void Draw();
	void Update(GLfloat deltatime);
protected:
	std::shared_ptr<Player> m_player;
	std::vector<std::shared_ptr<Enemy>> m_enemies;
	std::vector<std::shared_ptr<Block>> m_blocks;
	
};