#include "GSPause.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "PlayerData.h"
#include "SoundManager.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPause::GSPause()
{

}


GSPause::~GSPause()
{

}


void GSPause::Init()
{
	SoundManager::GetInstance()->PlayMenuBG();
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("PauseBackground");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//ResumeButton
	texture = ResourceManagers::GetInstance()->GetTexture("ResumeButton");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth/2, 200);
	button->SetSize(200, 50);
	button->SetOnClick([]() {

		GameStateMachine::GetInstance()->PopState();
		});
	m_ResumeButton = button;
	//Options button
	texture = ResourceManagers::GetInstance()->GetTexture("OptionsButton");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 280);
	button->SetSize(200, 50);
	button->SetOnClick([]() {

		// changed GSOptions
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Options);
		});
	m_OptionsButton = button;

	//Restart button
	texture = ResourceManagers::GetInstance()->GetTexture("RestartButton");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 360);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		PlayerData::GetInstance()->Restart();
		GameStateMachine::GetInstance()->PushState(STATE_Play);
		
		});
	m_RestartButton = button;
	//ExitButton
	texture = ResourceManagers::GetInstance()->GetTexture("Exitbutton");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 440);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		PlayerData::GetInstance()->Restart();
		});
	m_ExitButton = button;
}

void GSPause::Exit()
{

}


void GSPause::Pause()
{

}

void GSPause::Resume()
{
	SoundManager::GetInstance()->PlayMenuBG();
}


void GSPause::HandleEvents()
{

}

void GSPause::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPause::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_ResumeButton->HandleTouchEvents(x, y, bIsPressed);
	m_OptionsButton->HandleTouchEvents(x, y, bIsPressed);
	m_RestartButton->HandleTouchEvents(x, y, bIsPressed);
	m_ExitButton->HandleTouchEvents(x, y, bIsPressed);

}

void GSPause::Update(float deltaTime)
{
}

void GSPause::Draw()
{
	m_BackGround->Draw();
	m_ResumeButton->Draw();
	m_OptionsButton->Draw();
	m_RestartButton->Draw();
	m_ExitButton->Draw();
}

void GSPause::SetNewPostionForBullet()
{
}