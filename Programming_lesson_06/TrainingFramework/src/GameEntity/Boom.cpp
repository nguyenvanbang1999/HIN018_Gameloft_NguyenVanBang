#include"Boom.h"
#include"ResourceManagers.h"

Boom::Boom(std::shared_ptr<Vec2i> location,int power):Entity(location),m_time(2.5f),m_power(power),m_checkBang(false)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Bom");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_animation = std::make_shared<Animation>(model, shader, texture, 6, 0.4, TYPE_NORMAL, 1);
	m_animation->Set2DPosition(m_location->m_x, m_location->m_y);
	m_animation->SetSize(ENTITY_SIZE, ENTITY_SIZE);
}
void Boom::UpdateTime(float deltaTime)
{
	m_time -= deltaTime;
	if (m_time <= 0) m_isExist = false;
}