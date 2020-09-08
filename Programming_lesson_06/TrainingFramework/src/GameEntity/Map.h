#pragma once
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Block.h"

#include<vector>
#include <memory>
#include"GameStates/GSPlay.h"
#define		MAP_TOP_GUI		100

class Map 
{
public:
	Map(GSPlay* gs);
	
	void Draw();
	void Update(float deltatime);
	std::shared_ptr<Player> m_player;
	bool CheckCanMove(int x, int y, int size);
protected:
	
	std::vector<std::shared_ptr<Enemy>> m_enemies;
	std::vector<std::shared_ptr<Block>> m_blocks;

	GSPlay* m_GSPlay;
};