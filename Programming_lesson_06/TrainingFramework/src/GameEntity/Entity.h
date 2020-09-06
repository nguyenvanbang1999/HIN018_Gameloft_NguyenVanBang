#pragma once
#include<memory>
#include<cmath>

#include"Animation.h"

#define ENTITY_SIZE 40

class Entity
{
public:
	

	Entity(int locationX,int locationY);
	void Draw();
	void Update(GLfloat deltatime);
protected:
	int m_locationX;
	int m_locationY;
	bool m_isExist;
	std::shared_ptr<Animation> m_animation;
};
