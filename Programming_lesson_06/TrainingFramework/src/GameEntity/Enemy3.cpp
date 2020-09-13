#include"Enemy3.h"
#include"ResourceManagers.h"
#include "Map.h"
#include<memory>
#include<vector>


#define		ENEMY1_SPEED	120

Enemy3::Enemy3(std::shared_ptr<Vec2i> location,int hp) : Enemy(location,hp)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("enemy3Anim");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_animation = std::make_shared<Animation>(model, shader, texture, NUM_FRAME_ALIVE, ANIM_SPEED_ALIVE, TYPE_LOOP, NUM_LINE_ALIVE);
	m_animation->Set2DPosition(m_location->m_x, m_location->m_y);
	m_animation->SetSize(ENTITY_SIZE, ENTITY_SIZE);
}
void Enemy3::SetDestination()
{
	RandDir();
}
void Enemy3::SubHp()
{
	std::cout << "Sub Ene 2" << std::endl;
	Enemy::SubHp();
	m_usingSkill = true;
}
void Enemy3::Skill(Map* map)
{
	if (m_usingSkill)
	{
		if (m_hp > 0)
		{
			map->m_enemies.push_back(std::make_shared<Enemy3>(std::make_shared<Vec2i>(m_location->m_x, m_location->m_y),1));
		}
		m_usingSkill = false;
	}
}

