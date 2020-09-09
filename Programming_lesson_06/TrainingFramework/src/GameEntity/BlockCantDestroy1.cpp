#include"BlockCantDestroy1.h"
#include"ResourceManagers.h"
#include "Map.h"




BlockCantDestroy1::BlockCantDestroy1(std::shared_ptr<Vec2i> location):Block(location)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BlockCantDestroy");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_animation = std::make_shared<Animation>(model, shader, texture, NUM_FRAME, ANIM_SPEED, TYPE_SPRITE, NUM_LINE);
	m_animation->Set2DPosition(m_location->m_x, m_location->m_y);
	m_animation->SetSize(ENTITY_SIZE, ENTITY_SIZE);
}