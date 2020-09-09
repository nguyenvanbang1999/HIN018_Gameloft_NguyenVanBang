#include"Player.h"
#include"ResourceManagers.h"
#include "Map.h"





Player::Player(std::shared_ptr<Vec2i> location) :AliveEnties(location, PLAYER_SPEED),m_numBooms(3)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("playerAnim");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_animation = std::make_shared<Animation>(model,shader,texture,NUM_FRAME_ALIVE, ANIM_SPEED_ALIVE, TYPE_SPRITE, NUM_LINE_ALIVE);
	m_animation->Set2DPosition(m_location->m_x, m_location->m_y);
	m_animation->SetSize(ENTITY_SIZE, ENTITY_SIZE);
	m_size *= 0.6f;
	
}
void Player::SetCheck(std::shared_ptr<Boom> bom)
{
	m_checkExitBom = CheckHitBox(m_location->m_x, m_location->m_y, m_size, bom->m_location->m_x, bom->m_location->m_y, bom->m_size);
}



