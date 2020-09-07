#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include"Animation.h"
#include "GameEntity/Map.h"


#define PRESS_S 1<<1
#define PRESS_A 1<<2
#define PRESS_D 1<<3
#define PRESS_W 1<<4


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
	
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	m_map = std::make_shared<Map>();
	std::cout << "Init GSPlay" << std::endl;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);
	// quit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth - 120, 30);
	button->SetSize(200, 50);
	button->SetOnClick([]() {

		GameStateMachine::GetInstance()->PopState();
		});
	m_QuitButton = button;
	//animation
	texture = ResourceManagers::GetInstance()->GetTexture("playerAnim");
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_animation = std::make_shared<Animation>(model, shader, texture,3,0.15f,2,5);
	m_animation->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_animation->SetSize(40, 40);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	std::cout << "Init xong" << std::endl;
	
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case 'S':
		{
			
			m_keyListener |= PRESS_S;

			
			break;
		}
		case 'A':
		{
			
			m_keyListener |= PRESS_A;

			
			break;
		}
		case 'D':
		{
			
			m_keyListener |= PRESS_D;

			
			break;
		}
		case 'W':
		{
			
			m_keyListener |= PRESS_W;

			
			break;
		}
		default:
		{
			
			break;
		}
		}
	}
	else
	{
		switch (key)
		{
		case 'S':
		{
			m_keyListener &= ~PRESS_S;
			break;
		}
		case 'A':
		{
			
			m_keyListener &= ~PRESS_A;
			break;
		}
		case 'D':
		{
			
			m_keyListener &= ~PRESS_D;
			
			break;
		}
		case 'W':
		{
			
			m_keyListener &= ~PRESS_W;
			
			break;
		}
		default:
		{
			break;
		}
		}
	}
	

		
	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_QuitButton->HandleTouchEvents(x, y, bIsPressed);
}

void GSPlay::Update(float deltaTime)
{
	m_animation->Update(deltaTime);
	m_map->Update(deltaTime);
	bool checkMove = false;
	if (m_keyListener&PRESS_S) {
		m_map->m_player->ChangedDirection(DOWN_DIRECTION);
		checkMove = true;
	}
	if (m_keyListener&PRESS_A) {
		m_map->m_player->ChangedDirection(LEFT_DIRECTION);
		
		checkMove = true;
	}
	if (m_keyListener&PRESS_D) {
		m_map->m_player->ChangedDirection(RIGHT_DIRECTION);
		
		checkMove = true;
	}
	if (m_keyListener&PRESS_W) {
		m_map->m_player->ChangedDirection(TOP_DIRECTION);
		
		checkMove = true;
	}

	if (!checkMove) 
	{
		m_map->m_player->Stop();
	}
	else
	{
		m_map->m_player->Running();
	}


	
}

void GSPlay::Draw()
{
	//std::cout << "Start Draw" << std::endl;
	m_BackGround->Draw();
	//m_score->Draw();
	m_QuitButton->Draw();
	//m_animation->Draw();
	
	m_map->Draw();
	//std::cout << "Draw xong" << std::endl;
}

void GSPlay::SetNewPostionForBullet()
{
}