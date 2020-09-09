#pragma once
#include"Block.h"

class BlockCantDestroy1 :public Block 
{
public:
	BlockCantDestroy1(std::shared_ptr<Vec2i> location);
};
