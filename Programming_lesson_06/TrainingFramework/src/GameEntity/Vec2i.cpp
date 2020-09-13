#include"Vec2i.h"
#include<memory>



Vec2i::Vec2i(int x, int y) :m_x(x), m_y(y)
{

}
bool Vec2i::Equal(Vec2i vec) {
	return m_x == vec.m_x && m_y == vec.m_y;
}
bool Vec2i::Equal1(std::shared_ptr<Vec2i> vec) {

	return m_x == vec->m_x && m_y == vec->m_y;

}
float Vec2i::Range(int x, int y)
{
	return 0.0f;
}
Vec2i Vec2i::GetLogicLocation(int x, int y)
{
	int r_x = (x - 20) / 40;
	int r_y= (y - 20-100) / 40;
	return Vec2i(r_x, r_y);
}