#pragma once
#include "AliveEntites.h"
#include<memory>
#include"Boom.h"
class Player : public AliveEnties 
{
public:
	Player(std::shared_ptr<Vec2i> location);
	int m_numBooms;
	int m_checkExitBom = 0;
	void SetCheck(std::shared_ptr<Boom> bom);
	void UpdateTimeProtected(float deltatime);
	void Protected();
	int m_boomPower;
	float m_protectedTime;
	
};