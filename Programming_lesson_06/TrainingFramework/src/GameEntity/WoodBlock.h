#pragma once
#include"Block.h"

class WoodBlock :public Block
{
public:

	WoodBlock(std::shared_ptr<Vec2i> location);
};
