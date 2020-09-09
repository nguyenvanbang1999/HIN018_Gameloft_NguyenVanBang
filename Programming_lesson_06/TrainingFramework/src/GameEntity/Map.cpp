#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include<memory>
#include<chrono>

#include "ResourceManagers.h"

#include"BlockCantDestroy1.h"
#include"Player.h"
#include"WoodBlock.h"
#include"Enemy.h"
#include"Block.h"


#define		MAP_WIDTH	21
#define		MAP_HEIGHT	12

class GSPlay;

using namespace std::chrono;




Vec2i Getlocation(Vec2i vec)
{

	int x = (vec.m_x / ENTITY_SIZE)*ENTITY_SIZE + ENTITY_SIZE / 2;
	int y= ((vec.m_y - MAP_TOP_GUI) / ENTITY_SIZE)*ENTITY_SIZE + ENTITY_SIZE / 2 + MAP_TOP_GUI;

	return Vec2i(x, y);
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
			std::shared_ptr<Vec2i> loc = std::make_shared<Vec2i>(i*ENTITY_SIZE + ENTITY_SIZE / 2, countLine*ENTITY_SIZE + ENTITY_SIZE / 2 + MAP_TOP_GUI);
			char e = line.at(i);
			switch (e)
			{
			case '_':
			{

				break;
			}
			case 'X':
			{
				std::shared_ptr<BlockCantDestroy1> block = std::make_shared<BlockCantDestroy1>(loc);
				m_blocks.push_back(block);
				m_GSPlay->AddAnim(block->m_animation);
				break;
			}
			case 'P':
			{
				std::shared_ptr<Player> player = std::make_shared<Player>(loc);
				m_player = player;
				m_GSPlay->AddAnim(player->m_animation);
				break;
			}
			case 'W':
			{
				std::shared_ptr<WoodBlock> block = std::make_shared<WoodBlock>(loc);
				m_blocks.push_back(block);
				m_blocks2.push_back(block);
				m_GSPlay->AddAnim(block->m_animation);
				break;
			}
			case 'E':
			{
				std::shared_ptr<Enemy> e = std::make_shared<Enemy>(loc);
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
	
	for (std::shared_ptr<Block> b : m_blocks2) {
		b->Draw();
	}
	//std::cout << "Draw player" << std::endl;
	m_player->Draw();
	//std::cout << "Draw player xong" << std::endl;
	for (std::shared_ptr<Enemy> e : m_enemies) {
		e->Draw();
	}
	for (std::shared_ptr<Boom> b : m_booms) {
		b->Draw();
	}
	
	
	
	
	

}
void Map::Update(float deltatime) 
{
	//std::cout << deltatime << std::endl;
	m_player->Update(deltatime);
	
	for (auto e : m_enemies) 
	{
		e->Move(deltatime,this);
		e->Update(deltatime);
		
	}
	for (auto b : m_blocks) 
	{
		b->Update(deltatime);
	}
	for (int i=0;i<m_booms.size();)
	{
		std::shared_ptr<Boom> b = m_booms.at(i);
		b->UpdateTime(deltatime);
		b->Update(deltatime);
		if(!b->m_isExist)
		{
			m_player->m_numBooms++;
			m_booms.erase(m_booms.begin() + i);
		}
		else
		{
			i++;
		}
	}
}
bool Map::CheckCanMove(int x, int y, int size,bool isPlayer) 
{
	
	for (auto b : m_blocks) {
		if (CheckHitBox(x, y, size, b->m_location->m_x, b->m_location->m_y, b->m_size)) 
		{
			return false;
		}
	}
	/*int n = m_booms.size() - 1;
	if (isPlayer)
	{
		n -= 1;
		std::cout << "chua exit" << std::endl;
	}
	else
	{
		//std::cout << "exit r " <<n<<std:: endl;
	}
	for (int i = 0; i < n;i++) {
		std::shared_ptr<Boom> b = m_booms.at(i);
		if (CheckHitBox(x, y, size, b->m_location->m_x, b->m_location->m_y, b->m_size))
		{
			return false;
		}
	}*/
	return  true;
}

bool Map::CheckHasBoom(int x, int y)
{
	for (std::shared_ptr<Boom> b : m_booms)
	{
		if (b->m_location->m_x == x && b->m_location->m_y == y)
		{
			return true;
		}
	}
	return false;
}


void Map::SpawnBoom(int x, int y)
{
	std::cout << "Spawn ";
	
	int x1 = (x / ENTITY_SIZE)*ENTITY_SIZE + ENTITY_SIZE / 2;




	int y1 = ((y-MAP_TOP_GUI) / ENTITY_SIZE)*ENTITY_SIZE + ENTITY_SIZE / 2+ MAP_TOP_GUI;
	std::cout << x<<" "<<y<<std::endl;
	std::cout << x1 << " " << y1 << std::endl;
	if (!CheckHasBoom(x1, y1)&& m_player->m_numBooms>0)
	{
		m_booms.push_back(std::make_shared<Boom>(std::make_shared<Vec2i>(x1,y1)));
		m_player->m_numBooms--;
		std::cout << "xong "<<std::endl;
	}
}