#pragma once
#include "AliveEntites.h"
#include<memory>
#include"Boom.h"
class Player : public AliveEnties 
{
public:
	Player(std::shared_ptr<Vec2i> location);
	int m_numBooms;
	bool m_checkExitBom = true;
	void SetCheck(std::shared_ptr<Boom> bom);
	int m_boomPower;
	
};