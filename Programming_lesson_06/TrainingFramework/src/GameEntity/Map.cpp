#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include<memory>
#include<chrono>
#include<vector>

#include "ResourceManagers.h"

#include"BlockCantDestroy1.h"
#include"Player.h"
#include"WoodBlock.h"
#include"Enemy.h"
#include"Enemy1.h"
#include"Enemy2.h"
#include"Enemy3.h"
#include"Block.h"

#include"GameManager/PlayerData.h"

#include"SoundManager.h"


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

Map::Map(GSPlay* gs,int lvl) :m_GSPlay(gs)
{
	std::cout << "Start init map" << std::endl;
	std::fstream f;
	std::string file = "";
	if (lvl == 1) {
		file = "lvl1";
	}
	if (lvl == 2) {
		file = "lvl2";
	}
	f.open(ResourceManagers::GetInstance()->GetMapData(file), std::ios::in);

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
				//m_GSPlay->AddAnim(block->m_animation);
				break;
			}
			case 'P':
			{
				std::shared_ptr<Player> player = std::make_shared<Player>(loc);
				m_player = player;
				//m_GSPlay->AddAnim(player->m_animation);
				break;
			}
			case 'W':
			{
				std::shared_ptr<WoodBlock> block = std::make_shared<WoodBlock>(loc);
				//m_blocks.push_back(block);
				m_blocks2.push_back(block);
				//m_GSPlay->AddAnim(block->m_animation);
				break;
			}
			case 'E':
			{
				std::shared_ptr<Enemy1> e = std::make_shared<Enemy1>(loc);
				m_enemies.push_back(e);
				//m_GSPlay->AddAnim(e->m_animation);
				break;
			}
			case 'e':
			{
				std::shared_ptr<Enemy2> e = std::make_shared<Enemy2>(loc);
				m_enemies.push_back(e);
				//m_GSPlay->AddAnim(e->m_animation);
				break;
			}case 'S':
			{
				std::shared_ptr<Enemy3> e = std::make_shared<Enemy3>(loc,2);
				m_enemies.push_back(e);
				//m_GSPlay->AddAnim(e->m_animation);
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
	/*
	for (std::shared_ptr<Block> b : m_blocks) {
		b->Draw();
	}*/
	//std::cout << "Draw player" << std::endl;
	m_player->Draw();
	//std::cout << "Draw player xong" << std::endl;
	for (std::shared_ptr<Enemy> e : m_enemies) {
		e->Draw();
	}
	for (std::shared_ptr<Boom> b : m_booms) {
		b->Draw();
	}
	for (std::shared_ptr<Item> i : m_listItems) {
		i->Draw();
	}
	
	
	
	
	

}
void Map::Update(float deltatime) 
{
	//std::cout << m_player->m_checkExitBom << std::endl;
	m_player->Update(deltatime);
	m_player->UpdateTimeProtected(deltatime);
	if(m_player->m_protectedTime<=0.0f)
	for (std::shared_ptr<Vec2i> loc : m_listFireLocation)
	{
		if (CheckHitBox(m_player->m_location->m_x, m_player->m_location->m_y, m_player->m_size, loc->m_x, loc->m_y, ENTITY_SIZE))
		{
			//Player Stun +protected
			m_player->SubHp();
			PlayerData::GetInstance()->m_player_hp--;
			if (m_player->m_hp <= 0)
			{
				m_player->m_isExist = false;

				auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
				auto texture = ResourceManagers::GetInstance()->GetTexture("playerDeath");
				auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
				std::shared_ptr<Animation> anim = std::make_shared<Animation>(model, shader, texture, NUM_FRAME, ANIM_SPEED, TYPE_NORMAL, NUM_LINE);
				anim->Set2DPosition(m_player->m_location->m_x, m_player->m_location->m_y);
				anim->SetSize(ENTITY_SIZE, ENTITY_SIZE);
				m_GSPlay->AddAnim(anim);
			}
			m_player->m_protectedTime = 2.0f;
			SoundManager::GetInstance()->Protected();
			m_player->m_animation->m_isProtected = true;
			break;
		}
	}
	
	for (auto e : m_enemies)
	{
		for (std::shared_ptr<Vec2i> loc : m_listFireLocation)
		{
			if (CheckHitBox(e->m_location->m_x, e->m_location->m_y, e->m_size, loc->m_x, loc->m_y, ENTITY_SIZE))
			{
				//Player  protected
				e->Stun();
				SoundManager::GetInstance()->EnemyStun();
				e->SubHp();
				break;
			}
		}
		if (CheckHitBox(e->m_location->m_x, e->m_location->m_y, e->m_size, m_player->m_location->m_x, m_player->m_location->m_y, m_player->m_size))
		{
			if (m_player->m_protectedTime <= 0.0f)
			{
				m_player->SubHp();
				PlayerData::GetInstance()->m_player_hp--;
				if (m_player->m_hp <= 0)
				{
					m_player->m_isExist = false;

					auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
					auto texture = ResourceManagers::GetInstance()->GetTexture("playerDeath");
					auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
					std::shared_ptr<Animation> anim = std::make_shared<Animation>(model, shader, texture, NUM_FRAME, ANIM_SPEED, TYPE_NORMAL, NUM_LINE);
					anim->Set2DPosition(m_player->m_location->m_x, m_player->m_location->m_y);
					anim->SetSize(ENTITY_SIZE, ENTITY_SIZE);
					m_GSPlay->AddAnim(anim);
				}
				m_player->m_protectedTime = 2.0f; 
				SoundManager::GetInstance()->Protected();
				m_player->m_animation->m_isProtected = true;
			}
		}
		

	}

	m_listFireLocation.clear();
	for (std::shared_ptr<Item> i : m_listItems)
	{
		if (CheckHitBox(m_player->m_location->m_x, m_player->m_location->m_y, m_player->m_size, i->m_location->m_x, i->m_location->m_y, i->m_size))
		{
			SoundManager::GetInstance()->EatItem();
			switch (i->m_type)
			{
			case ITEM_ADDHP:
				if (m_player->m_hp < 3)
				{
					m_player->m_hp++;
					PlayerData::GetInstance()->m_player_hp++;
				}
				i->m_isExist = false;
				break;
			case ITEM_ADDBOM:
				
				
				m_player->m_numBooms++;
				PlayerData::GetInstance()->m_player_numBom++;
				
				i->m_isExist = false;
				break;
			case ITEM_ADDSPEED:
				if (m_player->m_speed < 400)
				{
					m_player->m_speed +=50;
					PlayerData::GetInstance()->m_player_speed+=50;
				}
				i->m_isExist = false;
				break;
			case ITEM_ADDPOWER:
				
				
				m_player->m_boomPower++;
				PlayerData::GetInstance()->m_player_power++;
;
				
				i->m_isExist = false;
				break;
			default:
				break;
			}
		}
	}

	for (int i = 0; i < m_listItems.size();)
	{
		std::shared_ptr<Item> b = m_listItems.at(i);
		if (b->m_isExist)
		{
			i++;
		}
		else
		{
			m_listItems.erase(m_listItems.begin() + i);

		}
	}
	//std::cout << "player update" << std::endl;
	for (int i = 0; i < m_enemies.size();)
	{
		std::shared_ptr<Enemy> e = m_enemies.at(i);
		if (e->m_isExist)
		{
			i++;
		}
		else
		{
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
			auto texture = ResourceManagers::GetInstance()->GetTexture("enemyDeathAnim");
			auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
			std::shared_ptr<Animation> anim = std::make_shared<Animation>(model, shader, texture, NUM_FRAME, ANIM_SPEED, TYPE_NORMAL, NUM_LINE);
			anim->Set2DPosition(e->m_location->m_x, e->m_location->m_y);
			anim->SetSize(ENTITY_SIZE, ENTITY_SIZE);
			m_GSPlay->AddAnim(anim);
			m_enemies.erase(m_enemies.begin() + i);

		}
	}
	for (auto e : m_enemies) 
	{
		e->Move(deltatime,this);
		e->Skill(this);
		e->Update(deltatime);
		e->UpdateTime(deltatime);
		
	}
	//std::cout << "enemy update" << std::endl;
	for (int i = 0; i < m_blocks2.size();)
	{
		std::shared_ptr<Block> b = m_blocks2.at(i);
		if (b->m_isExist)
		{
			b->Update(deltatime);
			i++;
		}
		else
		{
			m_blocks2.erase(m_blocks2.begin() + i);

			// spawn item
			SpawnItem(b->m_location);
		}
	}
	//std::cout << "wood block update" << std::endl;

	

	for (int i=0;i<m_booms.size();)
	{
		std::shared_ptr<Boom> b = m_booms.at(i);
		b->UpdateTime(deltatime);
		b->Update(deltatime);
		if(!b->m_isExist)
		{
			
			if (!b->m_checkBang)
			{
				
				//std::cout << "Update  " <<b->m_location->m_x<<" "<<b->m_location->m_y<< std::endl;
				BomBang(b);
				m_booms.erase(m_booms.begin() + i);
				
			}
		}
		else
		{
			i++;
		}
	}
	
	//std::cout << "boom update" << std::endl;
}
bool Map::CheckCanMove(int x, int y, int size,int countBom) 
{
	
	for (auto b : m_blocks) {
		if (CheckHitBox(x, y, size, b->m_location->m_x, b->m_location->m_y, b->m_size)) 
		{
			return false;
		}
	}
	for (auto b : m_blocks2) {
		if (CheckHitBox(x, y, size, b->m_location->m_x, b->m_location->m_y, b->m_size))
		{
			return false;
		}
	}
	int n = m_booms.size() ;
	
	
	

	

	for (int i = 0; i < n-countBom;i++) {
		std::shared_ptr<Boom> b = m_booms.at(i);
		if (CheckHitBox(x, y, size, b->m_location->m_x, b->m_location->m_y, b->m_size))
		{
			return false;
		}
	}
	

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
	//std::cout << "Spawn ";
	
	int x1 = (x / ENTITY_SIZE)*ENTITY_SIZE + ENTITY_SIZE / 2;




	int y1 = ((y-MAP_TOP_GUI) / ENTITY_SIZE)*ENTITY_SIZE + ENTITY_SIZE / 2+ MAP_TOP_GUI;
	if (!CheckHasBoom(x1, y1)&& m_player->m_numBooms>0)
	{
		m_booms.push_back(std::make_shared<Boom>(std::make_shared<Vec2i>(x1,y1), m_player->m_boomPower));
		SoundManager::GetInstance()->SpawnBom();
		m_player->m_numBooms--;
		m_player->m_checkExitBom ++;
		
	}
}

void Map::BomBang(std::shared_ptr<Boom> bom)









{
	m_listFireLocation.push_back(bom->m_location);
	m_player->m_numBooms++;
	bom->m_checkBang = true;
	int x = bom->m_location->m_x;
	int y = bom->m_location->m_y;
	bool addRight = true;
	bool addLeft = true;
	bool addBot = true;
	bool addTop = true;
	for (int i = 1; i <= bom->m_power; i++) 
	{
		
		std::shared_ptr<Vec2i> vec1 = std::make_shared<Vec2i>(x + i*ENTITY_SIZE, y);
		std::shared_ptr<Vec2i> vec2 = std::make_shared<Vec2i>(x -i * ENTITY_SIZE, y);
		std::shared_ptr<Vec2i> vec3 = std::make_shared<Vec2i>(x , y+i * ENTITY_SIZE);
		std::shared_ptr<Vec2i> vec4 = std::make_shared<Vec2i>(x , y-i * ENTITY_SIZE);
		bool add1 = addRight;
		bool add2 = addLeft;
		bool add3 = addBot;
		bool add4 = addTop;
		for (std::shared_ptr<Vec2i> lf : m_listFireLocation)
		{
			
			if (addRight)
			{
				if (CheckCanMove(vec1->m_x, vec1->m_y, ENTITY_SIZE))
				{
					//std::cout << "right = true " << std::endl;
					if (lf->Equal1(vec1))
					{
						add1 = false;
					}
				}
				else
				{
					
					Destroy(vec1);
					addRight = false;
					add1 = false;
					//add destroy;
				}
			}
				
			
			if (addLeft)
			{
				if (CheckCanMove(vec2->m_x, vec2->m_y, ENTITY_SIZE))
				{
					
					if (lf->Equal1(vec2))
					{
						add2 = false;
					}
				}
				else
				{
					
					Destroy(vec2);
					addLeft = false;
					add2 = false;
					//add destroy;
				}
			}
			if (addBot)
			{
				if (CheckCanMove(vec3->m_x, vec3->m_y, ENTITY_SIZE))
				{
					
					if (lf->Equal1(vec3))
					{
						add3 = false;
					}
				}
				else
				{
					
					Destroy(vec3);
					addBot = false;
					add3 = false;
					
				}
			}
			if (addTop)
			{
				if (CheckCanMove(vec4->m_x, vec4->m_y, ENTITY_SIZE
))
				{
					
					if (lf->Equal1(vec4))
					{
						add4 = false;
					}
				}
				else
				{
					
					Destroy(vec4);
					addTop = false;
					add4 = false;
					
				}
			}
		}
		if (add1) {
			m_listFireLocation.push_back(vec1);
		}
		if (add2) {
			m_listFireLocation.push_back(vec2);
		}
		if (add3) {
			m_listFireLocation.push_back(vec3);
		}
		if (add4) {
			m_listFireLocation.push_back(vec4);
		}
	}
	SoundManager::GetInstance()->BomBang();
}

void Map::Destroy(std::shared_ptr<Vec2i> location)
{
	//std::cout << "		Destroy " << location->m_x<<" "<< location->m_y<< std::endl;
	for (std::shared_ptr<Block> b : m_blocks2)
	{
		if (b->m_location->Equal1(location))
		{
			b->m_animation->ChangedType(TYPE_NORMAL);
		}
	}
	for (int i=0;i<m_booms.size();i++)
	{
		// ERR lap
		//std::cout << "LOOP " << std::endl;
		std::shared_ptr<Boom> b = m_booms.at(i);
		if (b->m_location->Equal1(location))
		{
			//b->m_animation->ChangedType(TYPE_NORMAL);
			b->m_isExist = false;
		}
		
	}
	//std::cout << "		Destroy  xong " << location->m_x << " " << location->m_y << std::endl;
}

void Map::SpawnItem(std::shared_ptr<Vec2i> location)
{
	int ran = rand() % 5;
	if (ran < 1)
	{
		int type = rand() % 4;
		m_listItems.push_back(std::make_shared<Item>(location, type));
	}
}
void Map::UpdateMatrix()
{
	

}