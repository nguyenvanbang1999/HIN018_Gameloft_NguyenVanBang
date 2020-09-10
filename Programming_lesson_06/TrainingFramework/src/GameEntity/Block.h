#pragma once
#include "Entity.h"

#define NUM_FRAME 6
#define ANIM_SPEED 0.08f
#define DEFAULT_DIR 0
#define NUM_LINE 1

class Block :public Entity 
{
public:
	Block(std::shared_ptr<Vec2i> location);
	bool m_isCanMove;
	
};
