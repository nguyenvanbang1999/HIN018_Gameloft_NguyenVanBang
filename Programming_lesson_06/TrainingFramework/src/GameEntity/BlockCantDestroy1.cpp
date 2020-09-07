#include"BlockCantDestroy1.h"
#include"ResourceManagers.h"
#include "Map.h"




BlockCantDestroy1::BlockCantDestroy1(int x, int y):Block(x,y)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BlockCantDestroy");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_animation = std::make_shared<Animation>(model, shader, texture, NUM_FRAME, ANIM_SPEED, TYPE_SPRITE, NUM_LINE);
	m_animation->Set2DPosition(m_locationX, m_locationY);
	m_animation->SetSize(ENTITY_SIZE, ENTITY_SIZE);
}