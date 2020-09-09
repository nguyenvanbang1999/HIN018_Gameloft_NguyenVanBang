#include"Enemy.h"
#include"ResourceManagers.h"
#include "Map.h"


#define		ENEMY1_SPEED	120

Enemy::Enemy(std::shared_ptr<Vec2i> location) : AliveEnties(location, ENEMY1_SPEED)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("enemy1Anim");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_animation = std::make_shared<Animation>(model, shader, texture, NUM_FRAME_ALIVE, ANIM_SPEED_ALIVE, TYPE_LOOP, NUM_LINE_ALIVE);
	m_animation->Set2DPosition(m_location->m_x, m_location->m_y);
	m_animation->SetSize(ENTITY_SIZE, ENTITY_SIZE);
}
void Enemy::Move(GLfloat deltatime,Map* map)
{
	//std::cout << deltatime << std::endl;
	int moveRange= deltatime * m_speed;
	int tempX = m_location->m_x;
	int tempY= m_location->m_y;
	if (m_running)
		switch (m_direction)
		{
		case TOP_DIRECTION:
		{
			tempY -= moveRange;
			break;
		}
		case DOWN_DIRECTION:
		{
			tempY += moveRange;
			break;
		}
		case LEFT_DIRECTION:
		{

			tempX -= moveRange;
			break;
		}
		case RIGHT_DIRECTION:
		{

			tempX += moveRange;
			break;
		}
		default:
		{
			std::cout << "default" << std::endl;
			break;
		}
		}

		if (map->CheckCanMove(tempX, tempY,ENTITY_SIZE,false)) {
			m_location->m_x = tempX;
			m_location->m_y = tempY;
		}
		else RandDir();
}
void Enemy::RandDir() 
{
	
	m_direction = rand() % 4 + 1;
	m_animation->ChangedLine(m_direction);
}