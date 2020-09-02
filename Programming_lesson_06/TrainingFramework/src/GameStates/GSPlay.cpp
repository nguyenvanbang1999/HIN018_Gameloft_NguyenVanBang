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

		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_QuitButton = button;
	//animation
	texture = ResourceManagers::GetInstance()->GetTexture("baby1");
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_animation = std::make_shared<Animation>(model, shader, texture,4,0.2f);
	m_animation->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_animation->SetSize(83, 104);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");

	
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
	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_QuitButton->HandleTouchEvents(x, y, bIsPressed);
}

void GSPlay::Update(float deltaTime)
{
	m_animation->Update(deltaTime);
}

void GSPlay::Draw()
{
	
	m_BackGround->Draw();
	m_score->Draw();
	m_QuitButton->Draw();
	m_animation->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}