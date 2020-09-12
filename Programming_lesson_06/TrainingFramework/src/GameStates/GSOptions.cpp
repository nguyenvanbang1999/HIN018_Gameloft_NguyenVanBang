#include "GSOptions.h"
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

GSOptions::GSOptions()
{

}


GSOptions::~GSOptions()
{

}


void GSOptions::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("OptionsBackground");

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

	//on sound button
	texture = ResourceManagers::GetInstance()->GetTexture("OnButton");
	 button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth /2+7, 380);
	button->SetSize(200, 80);
	button->SetOnClick([]() {

		std::cout << "Sound On" << std::endl;
		});
	m_OnSound = button;
	// off sound button
	texture = ResourceManagers::GetInstance()->GetTexture("OffButton");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2+220, 380);
	button->SetSize(200, 80);
	button->SetOnClick([]() {
		std::cout << "Sound Off" << std::endl;
		
		});
	m_OffSound = button;

	// on music button
	texture = ResourceManagers::GetInstance()->GetTexture("OnButton");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 7, 255);
	button->SetSize(200, 80);
	button->SetOnClick([]() {
		std::cout << "Music On" << std::endl;
		
		});
	m_OnMusic = button;
	// off music button
	texture = ResourceManagers::GetInstance()->GetTexture("offButton");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 220, 255);
	button->SetSize(200, 80);
	button->SetOnClick([]() {

		std::cout << "Music Off" << std::endl;
		});
	m_OffMusic = button;
}

void GSOptions::Exit()
{

}


void GSOptions::Pause()
{

}

void GSOptions::Resume()
{

}


void GSOptions::HandleEvents()
{

}

void GSOptions::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSOptions::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_BackButton->HandleTouchEvents(x, y, bIsPressed);
	m_OnMusic->HandleTouchEvents(x, y, bIsPressed);
	m_OffMusic->HandleTouchEvents(x, y, bIsPressed);
	m_OnSound-> HandleTouchEvents(x, y, bIsPressed);
	m_OffSound->HandleTouchEvents(x, y, bIsPressed);

}

void GSOptions::Update(float deltaTime)
{
}

void GSOptions::Draw()
{
	m_BackGround->Draw();
	m_BackButton->Draw();
	m_OnMusic->Draw();
	m_OffMusic->Draw();
	m_OnSound->Draw();
	m_OffSound->Draw();
}

void GSOptions::SetNewPostionForBullet()
{
}