#include"Enemy2.h"
#include"ResourceManagers.h"
#include "Map.h"


#define		ENEMY1_SPEED	120

Enemy2::Enemy2(std::shared_ptr<Vec2i> location) : Enemy(location,2)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("enemy2Anim");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_animation = std::make_shared<Animation>(model, shader, texture, NUM_FRAME_ALIVE, ANIM_SPEED_ALIVE, TYPE_LOOP, NUM_LINE_ALIVE);
	m_animation->Set2DPosition(m_location->m_x, m_location->m_y);
	m_animation->SetSize(ENTITY_SIZE, ENTITY_SIZE);
}
void Enemy2::SetDestination()
{
	RandDir();
}
void Enemy2::SubHp() 
{
	std::cout << "Sub Ene 2" << std::endl;
	Enemy::SubHp();
	m_usingSkill = true;
}
void Enemy2::Skill(Map* map)
{
	if (m_usingSkill)
	{
		m_speed = 170;
		m_usingSkill = false;
	}
}

