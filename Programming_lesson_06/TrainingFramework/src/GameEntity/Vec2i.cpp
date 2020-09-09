#include"Vec2i.h"



Vec2i::Vec2i(int x, int y) :m_x(x), m_y(y)
{

}
bool Vec2i::Equal(Vec2i vec) {
	return m_x == vec.m_x && m_y == vec.m_y;
}