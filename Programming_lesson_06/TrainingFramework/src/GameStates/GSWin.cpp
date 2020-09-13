#include "GSWin.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SoundManager.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSWin::GSWin()
{

}


GSWin::~GSWin()
{

}


void GSWin::Init()
{
	SoundManager::GetInstance()->PlayWin();
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("WinBackground");

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

void GSWin::Exit()
{

}


void GSWin::Pause()
{

}

void GSWin::Resume()
{

}


void GSWin::HandleEvents()
{

}

void GSWin::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSWin::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_BackButton->HandleTouchEvents(x, y, bIsPressed);

}

void GSWin::Update(float deltaTime)
{
}

void GSWin::Draw()
{
	m_BackGround->Draw();
	m_BackButton->Draw();
}

void GSWin::SetNewPostionForBullet()
{
}