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

#include"GameManager/PlayerData.h"


#define PRESS_S 2
#define PRESS_A 4
#define PRESS_D 8
#define PRESS_W 16
#define PRESS_SPACE 32


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine



GSPlay::GSPlay(int lvl):m_lvl(lvl)
{
	if (m_lvl == 1)
	{
		m_backgroundFile = "Playbackground1";
		
	}
	if (m_lvl == 2) m_backgroundFile = "Playbackground2";
	else
	{
		m_backgroundFile = "Playbackground1";
	}
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	if (PlayerData::GetInstance()->m_lvl > NUM_LVL)
	{
		PlayerData::GetInstance()->Reset();
	}
	m_map = std::make_shared<Map>(this, PlayerData::GetInstance()->m_lvl);
	std::cout << "Init GSPlay" << std::endl;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture(m_backgroundFile);

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	
	

	// quit button
	texture = ResourceManagers::GetInstance()->GetTexture("Backbutton");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth - 30, 30);
	button->SetSize(50, 50);
	button->SetOnClick([]() {

		GameStateMachine::GetInstance()->PopState();
		});
	m_QuitButton = button;
	//animation
	texture = ResourceManagers::GetInstance()->GetTexture("playerAnim");
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	//m_animation = std::make_shared<Animation>(model, shader, texture,3,0.15f,2,5);
	//m_animation->Set2DPosition(screenWidth / 2, screenHeight / 2);
	//m_animation->SetSize(40, 40);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	std::cout << "Init xong" << std::endl;

	// GUI
	
	std::string hp = std::to_string(PlayerData::GetInstance()->m_player_hp);

	m_PlayerHp = std::make_shared< Text>(shader, font, std::to_string(PlayerData::GetInstance()->m_player_hp), TEXT_COLOR::RED, 1.0);
	m_PlayerNumBom = std::make_shared< Text>(shader, font, std::to_string(PlayerData::GetInstance()->m_player_numBom), TEXT_COLOR::RED, 1.0);
	m_PlayerPower = std::make_shared< Text>(shader, font, std::to_string(PlayerData::GetInstance()->m_player_power), TEXT_COLOR::RED, 1.0);
	m_PlayerSpeed = std::make_shared< Text>(shader, font, std::to_string((PlayerData::GetInstance()->m_player_speed -150)/50), TEXT_COLOR::RED, 1.0);
	
	m_PlayerHp->Set2DPosition(240, 35);
	m_PlayerNumBom->Set2DPosition(380,75 );
	m_PlayerPower->Set2DPosition(240, 75);
	m_PlayerSpeed->Set2DPosition(380, 30);
	m_score->Set2DPosition(Vector2(5, 25));
	
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{
	std::cout << "Pause" << std:: endl;
}

void GSPlay::Resume()
{
	std::cout << "Resum" << std::endl;
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
			m_map->m_player->ChangedDirection(DOWN_DIRECTION);
			break;
		}
		case 'A':
		{
			
			m_keyListener |= PRESS_A;
			m_map->m_player->ChangedDirection(LEFT_DIRECTION);
			
			break;
		}
		case 'D':
		{
			
			m_keyListener |= PRESS_D;
			m_map->m_player->ChangedDirection(RIGHT_DIRECTION);
			
			break;
		}
		case 'W':
		{
			
			m_keyListener |= PRESS_W;
			m_map->m_player->ChangedDirection(TOP_DIRECTION);
			
			break;
		}
		case ' ':
		{

			m_map->SpawnBoom(m_map->m_player->m_location->m_x, m_map->m_player->m_location->m_y);\
			

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
			
			m_keyListener = m_keyListener &~PRESS_W;
			
			
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
	
	if (m_map->m_player->m_hp <= 0&&m_listAnim.size()<=0)
	{
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Lose);
	}
	if (m_map->m_enemies.size() <= 0)
	{
		//std::cout << m_map->m_enemies.size() << std::endl;
		PlayerData::GetInstance()->m_lvl++;
		if (PlayerData::GetInstance()->m_lvl <= NUM_LVL)
		{
			GameStateMachine::GetInstance()->PopState();
			GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Play);
		}
		else
		{
			// Win GS
			GameStateMachine::GetInstance()->PopState();
			GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Win);
		}
	}
	else
	{
		//std::cout << m_map->m_enemies.size() << std::endl;
	}
	int moveRange = 0;
	int lastBomindex = m_map->m_booms.size() - 1;
	if (m_keyListener != 0) {
		moveRange= deltaTime * m_map->m_player->m_speed;
	}
	int tempX = m_map->m_player->m_location->m_x;
	int tempY = m_map->m_player->m_location->m_y;
	int playerSize = m_map->m_player->m_size;
	bool checkMove = false;
	if (m_keyListener&PRESS_S) {
		m_map->m_player->ChangedDirection(DOWN_DIRECTION);
		tempY += moveRange;
		if (m_map->CheckCanMove(tempX, tempY, playerSize, m_map->m_player->m_checkExitBom))
		{
			m_map->m_player->m_location->m_y = tempY;
			if (lastBomindex >= 0)
			{
				m_map->m_player->SetCheck(m_map->m_booms.at(m_map->m_booms.size() - 1));
			}
		}
		else
		{
			tempY -= moveRange;
		}
		checkMove = true;
	}
	if (m_keyListener&PRESS_A) {
		m_map->m_player->ChangedDirection(LEFT_DIRECTION);
		tempX -= moveRange;
		if (m_map->CheckCanMove(tempX, tempY, playerSize, m_map->m_player->m_checkExitBom))
		{
			m_map->m_player->m_location->m_x = tempX;
			if (lastBomindex >= 0)
			{
				m_map->m_player->SetCheck(m_map->m_booms.at(m_map->m_booms.size() - 1));
			}
		}
		else
		{
			tempX += moveRange;
		}
		checkMove = true;

	}
	if (m_keyListener&PRESS_D) {
		m_map->m_player->ChangedDirection(RIGHT_DIRECTION);
		tempX += moveRange;
		if (m_map->CheckCanMove(tempX, tempY, playerSize, m_map->m_player->m_checkExitBom))
		{

			m_map->m_player->m_location->m_x = tempX;
			if (lastBomindex >= 0)
			{
				m_map->m_player->SetCheck(m_map->m_booms.at(m_map->m_booms.size() - 1));
			}
		}
		else
		{
			tempX -= moveRange;
		}
		checkMove = true;

	}
	if (m_keyListener&PRESS_W) {
		m_map->m_player->ChangedDirection(TOP_DIRECTION);
		tempY -= moveRange;
		if (m_map->CheckCanMove(tempX, tempY, playerSize, m_map->m_player->m_checkExitBom))
		{
			m_map->m_player->m_location->m_y = tempY;
			if (lastBomindex >= 0)
			{
				m_map->m_player->SetCheck(m_map->m_booms.at(m_map->m_booms.size() - 1));
			}
		}
		else
		{
			tempY += moveRange;
		}
		checkMove = true;
	}
	
	//std::cout << m_map->m_player->m_locationY << std::endl;

	if (!checkMove) 
	{
		m_map->m_player->Stop();
	}
	else
	{
		m_map->m_player->Running();
	}
	/*for (auto a : m_listAnim) {
		a->Update(deltaTime);
	}*/
	m_map->Update(deltaTime);
	//std::cout << m_listAnim.size() << std::endl;
	int i = 0;
	for (std::shared_ptr<Animation> a : m_listAnim)
	{

		//std::cout << "up " <<i<< std::endl;
		a->Update(deltaTime);
		i++;
	}
	for(int i=0;i<m_listAnim.size();)
	{
		if (m_listAnim.at(i)->m_isExist==false)
		{
			m_listAnim.erase(m_listAnim.begin() + i);
		}
		else i++;
	}
	
	for (std::shared_ptr<Vec2i> v : m_map->m_listFireLocation)
	{
		
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto texture = ResourceManagers::GetInstance()->GetTexture("fireAnim");
		auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
		std::shared_ptr<Animation> anim = std::make_shared<Animation>(model, shader, texture, NUM_FRAME, ANIM_SPEED, TYPE_NORMAL, NUM_LINE);
		anim->Set2DPosition(v->m_x, v->m_y);
		//std::cout << v->m_x<<" "<<v->m_y << std::endl;
		anim->SetSize(ENTITY_SIZE, ENTITY_SIZE);
		m_listAnim.push_back(anim);
		//std::cout << "xong "   << std::endl;
		
	}
	

	
	
	


	
}

void GSPlay::Draw()
{
	//std::cout << "Start Draw" << std::endl;
	m_BackGround->Draw();
	//m_score->Draw();
	m_QuitButton->Draw();
	//m_animation->Draw();


	m_PlayerHp->setText(std::to_string(PlayerData::GetInstance()->m_player_hp));
	m_PlayerNumBom -> setText(std::to_string(PlayerData::GetInstance()->m_player_numBom));
	m_PlayerPower->setText(std::to_string(PlayerData::GetInstance()->m_player_power));
	m_PlayerSpeed->setText(std::to_string((PlayerData::GetInstance()->m_player_speed - 150) / 50));
	m_map->Draw();
	m_PlayerHp->Draw();
	m_PlayerNumBom->Draw();
	m_PlayerPower->Draw();
	m_PlayerSpeed->Draw();
	//std::cout << "Draw xong" << std::endl;
	for (auto a : m_listAnim)
	{
		a->Draw();
	}
}

void GSPlay::AddAnim(std::shared_ptr<Animation> anim)
{
	m_listAnim.push_back(anim);
}

void GSPlay::SetNewPostionForBullet()
{
}