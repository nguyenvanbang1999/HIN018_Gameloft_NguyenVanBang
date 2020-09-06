#include"Enemy.h"
#include"ResourceManagers.h"
#include "Map.h"

#define		ENEMY1_SPEED	15


Enemy::Enemy(int locationX, int locationY) : AliveEnties(locationX, locationY, ENEMY1_SPEED)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("enemy1Anim");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_animation = std::make_shared<Animation>(model, shader, texture, NUM_FRAME_ALIVE, ANIM_SPEED, TYPE_LOOP, NUM_LINE_ALIVE);
	m_animation->Set2DPosition(m_locationX*ENTITY_SIZE + ENTITY_SIZE / 2, m_locationY*ENTITY_SIZE + ENTITY_SIZE / 2 +MAP_TOP_GUI);
	m_animation->SetSize(ENTITY_SIZE, ENTITY_SIZE);
}