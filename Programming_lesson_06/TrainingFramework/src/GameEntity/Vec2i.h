#pragma once
#include<memory>


class Vec2i
{
public:
	Vec2i(int x,int y);
	int m_x;
	int m_y;
	bool Equal(Vec2i vec);
	bool Equal1(std::shared_ptr<Vec2i> vec);
};
