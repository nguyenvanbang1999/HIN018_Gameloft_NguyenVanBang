#include "GSHighScore.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSHighScore::GSHighScore()
{

}


GSHighScore::~GSHighScore()
{

}


void GSHighScore::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//quit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(120, 30);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_BackButton = button;
}

void GSHighScore::Exit()
{

}


void GSHighScore::Pause()
{

}

void GSHighScore::Resume()
{

}


void GSHighScore::HandleEvents()
{

}

void GSHighScore::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSHighScore::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_BackButton->HandleTouchEvents(x, y, bIsPressed);
	
}

void GSHighScore::Update(float deltaTime)
{
}

void GSHighScore::Draw()
{
	m_BackGround->Draw();
	m_BackButton->Draw();
}

void GSHighScore::SetNewPostionForBullet()
{
}