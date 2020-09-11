#pragma once
#include"Entity.h"
#define ITEM_ADDHP 0
#define ITEM_ADDBOM 1
#define ITEM_ADDPOWER 2
#define ITEM_ADDSPEED 3

class Item :public Entity
{
public:
	Item(std::shared_ptr<Vec2i> location, int type);
	int m_type;
};
