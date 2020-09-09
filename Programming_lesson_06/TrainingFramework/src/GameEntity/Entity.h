#pragma once
#include<memory>
#include<cmath>

#include"Animation.h"
#include"Vec2i.h"



#define ENTITY_SIZE 40

class Entity
{
public:
	

	Entity(std::shared_ptr<Vec2i> location);

	void Draw();
	void Update(float deltatime);
	std::shared_ptr<Vec2i> m_location;
	int m_size;
	bool m_isExist;
	
	std::shared_ptr<Animation> m_animation;
protected:
	
	
	
};
