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
	void Update(float deltatime);
	int m_locationX;
	int m_locationY;
	int m_size;
	std::shared_ptr<Animation> m_animation;
protected:
	
	bool m_isExist;
	
};
