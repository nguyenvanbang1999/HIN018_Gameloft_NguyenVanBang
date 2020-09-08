#pragma once
#include "gamestatebase.h"
#include"GameButton.h"


class Sprite2D;
class Sprite3D;
class Text;
class Animation;
class Map;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	void AddAnim(std::shared_ptr<Animation> anim);

	
	void SetNewPostionForBullet();

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::shared_ptr<GameButton>  m_QuitButton;
	std::vector< std::shared_ptr<Animation>> m_listAnim;
	std::vector< std::shared_ptr<Sprite2D>> m_listSprite;
	std::shared_ptr<Map> m_map;
	int m_keyListener = 0;

};

