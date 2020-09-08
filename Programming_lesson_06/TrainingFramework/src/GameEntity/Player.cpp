#include"Player.h"
#include"ResourceManagers.h"
#include "Map.h"





Player::Player(int locationX,int locationY) :AliveEnties(locationX, locationY, PLAYER_SPEED)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("playerAnim");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_animation = std::make_shared<Animation>(model,shader,texture,NUM_FRAME_ALIVE, ANIM_SPEED_ALIVE, TYPE_SPRITE, NUM_LINE_ALIVE);
	m_animation->Set2DPosition(m_locationX, m_locationY);
	m_animation->SetSize(ENTITY_SIZE, ENTITY_SIZE);
	m_size *= 0.6f;
	
}



