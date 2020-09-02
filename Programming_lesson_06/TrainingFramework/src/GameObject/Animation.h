#pragma once
#include"Sprite2D.h"
class Animation :public Sprite2D 
{
public:
	Animation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,int numFrames,float frameTime);
	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;
protected:
	int m_numFrames;
	float m_frameTime;
	int m_currentFrame;
	float m_currentTime;
};