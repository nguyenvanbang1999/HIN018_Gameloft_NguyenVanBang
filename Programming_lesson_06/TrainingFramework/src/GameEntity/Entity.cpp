#include"Entity.h"
Entity::Entity(int locationX,int locationY) :m_locationX(locationX),m_locationY(locationY)
{

}

void Entity::Draw() {
	m_animation->Draw();
	
}
void Entity::Update(GLfloat deltatime) {
	m_animation->Update(deltatime);
}
