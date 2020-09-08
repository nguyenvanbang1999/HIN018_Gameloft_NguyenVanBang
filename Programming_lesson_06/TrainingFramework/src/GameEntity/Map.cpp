#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include<memory>
#include "ResourceManagers.h"

#include"BlockCantDestroy1.h"
#include"Player.h"
#include"WoodBlock.h"
#include"Enemy.h"
#include"Block.h"


#define		MAP_WIDTH	21
#define		MAP_HEIGHT	12

class GSPlay;

static bool CheckHitBox(int x1, int y1, int size1, int x2, int y2, int size2) {
	bool check = false;
	x1 -= size1 / 2;
	y1 -= size1 / 2;
	x2 -= size2 / 2;
	y2 -= size2 / 2;
	int w1 = size1;
	int w2 = size2;

	return ((x1 + w1 >= x2) && (x2 + w2 >= x1) && (y1 + w1 >= y2) && (y2 + w2 >= y1));

}

Map::Map(GSPlay* gs) :m_GSPlay(gs)
{
	std::cout << "Start init map" << std::endl;
	std::fstream f;

	f.open(ResourceManagers::GetInstance()->GetMapData("lvl1"), std::ios::in);

	std::string line;
	int countLine = 0;
	while (!f.eof())
	{
		getline(f, line);
		for (int i = 0; i < line.size(); i++)
		{

			char e = line.at(i);
			switch (e)
			{
			case '_':
			{

				break;
			}
			case 'X':
			{
				std::shared_ptr<BlockCantDestroy1> block = std::make_shared<BlockCantDestroy1>(i*ENTITY_SIZE + ENTITY_SIZE / 2, countLine*ENTITY_SIZE + ENTITY_SIZE / 2 + MAP_TOP_GUI);
				m_blocks.push_back(block);
				m_GSPlay->AddAnim(block->m_animation);
				break;
			}
			case 'P':
			{
				std::shared_ptr<Player> player = std::make_shared<Player>(i*ENTITY_SIZE + ENTITY_SIZE / 2, countLine*ENTITY_SIZE + ENTITY_SIZE / 2+MAP_TOP_GUI);
				m_player = player;
				m_GSPlay->AddAnim(player->m_animation);
				break;
			}
			case 'W':
			{
				std::shared_ptr<WoodBlock> block = std::make_shared<WoodBlock>(i*ENTITY_SIZE + ENTITY_SIZE / 2, countLine*ENTITY_SIZE + ENTITY_SIZE / 2 + MAP_TOP_GUI);
				m_blocks.push_back(block);
				m_GSPlay->AddAnim(block->m_animation);
				break;
			}
			case 'E':
			{
				std::shared_ptr<Enemy> e = std::make_shared<Enemy>(i*ENTITY_SIZE + ENTITY_SIZE / 2, countLine*ENTITY_SIZE + ENTITY_SIZE / 2 + MAP_TOP_GUI);
				m_enemies.push_back(e);
				m_GSPlay->AddAnim(e->m_animation);
				break;
			}
			default:
				break;
			}
		}
		countLine++;
	}

	f.close();
	
}


void Map::Draw() {
	//std::cout << "Draw player" << std::endl;
	m_player->Draw();
	//std::cout << "Draw player xong" << std::endl;
	for (std::shared_ptr<Enemy> e : m_enemies) {
		e->Draw();
	}
	for (std::shared_ptr<Block> b : m_blocks) {
		b->Draw();
	}
	//std::cout << "Draw "<<m_blocks.size() << std::endl;

}
void Map::Update(float deltatime) {
	//std::cout << deltatime << std::endl;
	m_player->Update(deltatime);
	
	for (auto e : m_enemies) {
		e->Update(deltatime);
		e->Move(deltatime);
	}
	for (auto b : m_blocks) {
		b->Update(deltatime);
	}
}
bool Map::CheckCanMove(int x, int y, int size) 
{
	for (auto b : m_blocks) {
		if (CheckHitBox(x, y, size, b->m_locationX, b->m_locationY, b->m_size)) 
		{
			return false;
		}
	}
	return  true;
}