#include "GSHelp.h"
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

GSHelp::GSHelp()
{

}


GSHelp::~GSHelp()
{

}


void GSHelp::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("HelpBackground");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//quit button
	texture = ResourceManagers::GetInstance()->GetTexture("Backbutton");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth - 30, 30);
	button->SetSize(50, 50);
	button->SetOnClick([]() {

		GameStateMachine::GetInstance()->PopState();
		});
	m_BackButton = button;
}

void GSHelp::Exit()
{

}


void GSHelp::Pause()
{

}

void GSHelp::Resume()
{

}


void GSHelp::HandleEvents()
{

}

void GSHelp::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSHelp::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_BackButton->HandleTouchEvents(x, y, bIsPressed);

}

void GSHelp::Update(float deltaTime)
{
}

void GSHelp::Draw()
{
	m_BackGround->Draw();
	m_BackButton->Draw();
}

void GSHelp::SetNewPostionForBullet()
{
}