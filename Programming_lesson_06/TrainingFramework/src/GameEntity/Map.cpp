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

#define		MAP_WIDTH	21
#define		MAP_HEIGHT	12


Map::Map()
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
				std::shared_ptr<BlockCantDestroy1> block = std::make_shared<BlockCantDestroy1>(i, countLine);
				m_blocks.push_back(block);
				break;
			}
			case 'P':
			{
				std::shared_ptr<Player> player = std::make_shared<Player>(i, countLine);
				m_player = player;
				break;
			}
			case 'W':
			{
				std::shared_ptr<WoodBlock> block = std::make_shared<WoodBlock>(i, countLine);
				m_blocks.push_back(block);
				break;
			}
			case 'E':
			{
				std::shared_ptr<Enemy> e = std::make_shared<Enemy>(i , countLine );
				m_enemies.push_back(e);
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
	for (auto e : m_enemies) {
		e->Draw();
	}
	for (auto b : m_blocks) {
		b->Draw();
	}

}
void Map::Update(GLfloat deltatime) {
	m_player->Update(deltatime);
	
	for (auto e : m_enemies) {
		e->Update(deltatime);
	}
	for (auto b : m_blocks) {
		b->Update(deltatime);
	}
}