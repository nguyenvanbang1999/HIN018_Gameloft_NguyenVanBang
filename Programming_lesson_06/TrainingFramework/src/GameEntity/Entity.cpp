#include"Entity.h"
#include "Map.h"
Entity::Entity(int locationX,int locationY) :m_locationX(locationX),m_locationY(locationY),m_size(ENTITY_SIZE)
{

}

void Entity::Draw() {
	m_animation->Draw();
	
}
void Entity::Update(float deltatime) {
	m_animation->Update(deltatime);
	m_animation->Set2DPosition(m_locationX, m_locationY);
}
