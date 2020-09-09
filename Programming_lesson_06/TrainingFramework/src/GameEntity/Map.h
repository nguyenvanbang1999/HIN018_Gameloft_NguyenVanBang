#pragma once
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Block.h"
#include"Boom.h"

#include<vector>
#include <memory>
#include"GameStates/GSPlay.h"
#define		MAP_TOP_GUI		100

static bool CheckHitBox(int x1, int y1, int size1, int x2, int y2, int size2)
{
	bool check = false;
	x1 -= size1 / 2;
	y1 -= size1 / 2;
	x2 -= size2 / 2;
	y2 -= size2 / 2;
	int w1 = size1;
	int w2 = size2;

	return ((x1 + w1 > x2) && (x2 + w2 > x1) && (y1 + w1 > y2) && (y2 + w2 > y1));

}
class Map 
{
public:
	Map(GSPlay* gs);
	
	void Draw();
	void Update(float deltatime);
	std::shared_ptr<Player> m_player;
	bool CheckCanMove(int x, int y, int size,bool isPlayer);
	bool CheckHasBoom(int x, int y);
	void SpawnBoom(int x, int y);

	std::vector<std::shared_ptr<Boom>> m_booms;
protected:
	
	std::vector<std::shared_ptr<Enemy>> m_enemies;
	std::vector<std::shared_ptr<Block>> m_blocks;
	std::vector<std::shared_ptr<Block>> m_blocks2;
	
	GSPlay* m_GSPlay;
};