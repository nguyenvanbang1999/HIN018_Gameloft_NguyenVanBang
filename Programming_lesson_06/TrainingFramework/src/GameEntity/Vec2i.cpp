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