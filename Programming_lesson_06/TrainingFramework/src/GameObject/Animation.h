#pragma once
#include"Sprite2D.h"
#define		TYPE_SPRITE		0
#define		TYPE_NORMAL		1
#define		TYPE_LOOP		2

class Animation :public Sprite2D 
{
public:
	Animation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,int numFrames,float frameTime,int type,int numLines);
	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;
	void		ChangedLine(int line);
	void		ChangedType(int type);
	void		StopAnim();
	bool		m_isExist;

	bool		isPlayer=false;

	bool		m_isProtected;

	int			m_typeAnim;

	float		m_frameTime;
	float		m_currentTime;
protected:
	int			m_numFrames;
	
	int			m_currentFrame;
	
	int			m_numLines;
	int			m_currentLine;
};