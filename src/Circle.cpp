#include "Circle.h"

//==================================================================
Circle::Circle() :m_circle(sf::CircleShape(RADIOUS))
{
	init();
}
//==================================================================
Circle::Circle(const size_t& serialNum, const sf::Vector2f& pos) :m_circle(sf::CircleShape(RADIOUS))
{
	init();
	m_serialNum = serialNum;
	m_circle.setPosition(pos);
}
//===================================================================
Circle::Circle(const Circle& other)
{
	*this = other;
}
//===================================================================
void Circle::setAsSource()
{
	m_distance = 0;
	m_visited = VISITED;
}
//====================================================================
bool Circle::isValid()const
{
	return !isPressed() && !m_visited;
}
//====================================================================
void Circle::update(const bool& isVisited, Circle* pred, const size_t distance)
{
	m_visited = isVisited;
	m_pred = pred;
	m_distance = distance;
}
//====================================================================
void Circle::setOutlineThickness(const float& thick)
{
	m_circle.setOutlineThickness(thick);
}
//====================================================================
void Circle::draw(sf::RenderWindow& window) const
{
	window.draw(m_circle);
}
//======================================================================
void Circle::setPred(Circle* pred)
{
	m_pred = pred;
}
//======================================================================
void Circle::setClicked(const bool& isBlocked)
{
	if (m_isPressed != isBlocked) {
		m_circle.setFillColor(isBlocked ? PRESSED_CLR : UNPRESSED_CLR);
		m_isPressed = isBlocked;
	}
}
//======================================================================
void Circle::addNeighbors(Circle* neighbor)
{
	m_neigbors.emplace_back(neighbor);
}
//======================================================================
void Circle::init() 
{
	setOutlineThickness(2);
	m_circle.setOutlineColor(HOVERED_CELL);
	m_circle.setFillColor(UNPRESSED_CLR);
	m_circle.setOrigin(RADIOUS, RADIOUS);
}
//======================================================================
//global operator
bool operator==(const Circle& c1, const Circle& c2)
{
	return c1.getSerialNum() == c2.getSerialNum();
}
//======================================================================
//global operator
bool operator!=(const Circle& c1, const Circle& c2)
{
	return !(c1 == c2);
}
