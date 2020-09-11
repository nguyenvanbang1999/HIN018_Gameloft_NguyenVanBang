#include"Entity.h"

Entity::Entity(std::shared_ptr<Vec2i> location) :m_location(location),m_size(ENTITY_SIZE),m_isExist(true)
{

}

void Entity::Draw() {
	m_animation->Draw();
	
}
void Entity::Update(float deltatime) {
	if (!m_animation->m_isExist) m_isExist = false;
	m_animation->Update(deltatime);
	m_animation->Set2DPosition(m_location->m_x, m_location->m_y);
}
