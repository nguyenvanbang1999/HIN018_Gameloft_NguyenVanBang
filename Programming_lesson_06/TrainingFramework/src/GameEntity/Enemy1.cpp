#include"Enemy1.h"
#include"ResourceManagers.h"
#include "Map.h"


#define		ENEMY1_SPEED	120

Enemy1::Enemy1(std::shared_ptr<Vec2i> location) : Enemy(location,1)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("enemy1Anim");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_animation = std::make_shared<Animation>(model, shader, texture, NUM_FRAME_ALIVE, ANIM_SPEED_ALIVE, TYPE_LOOP, NUM_LINE_ALIVE);
	m_animation->Set2DPosition(m_location->m_x, m_location->m_y);
	m_animation->SetSize(ENTITY_SIZE, ENTITY_SIZE);
}
void Enemy1::SetDestination()
{
	RandDir();
}

