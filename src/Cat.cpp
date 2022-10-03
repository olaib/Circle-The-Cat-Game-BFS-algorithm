#include "Cat.h"
#include <unordered_map>

//this func get a of a circle and return direction
std::pair<MoveDirec, size_t> serialNum2Dir(const int& value) {
	static const
		std::unordered_map<int, std::pair<MoveDirec, size_t>>
		serial2VecMapping =
		{
			{ -1 ,{ MoveDirec::Right     ,3 }},
			{  1 ,{ MoveDirec::Left      ,1 }},
			{ 10 ,{ MoveDirec::RightUp   ,2 }},
			{-12 ,{ MoveDirec::RightDown ,0 }},
			{ 11 ,{ MoveDirec::LeftUp    ,2 }},
			{-11 ,{ MoveDirec::LeftDown  ,0 }}
		};
	try 
	{
		return serial2VecMapping.at(value);
	}
	catch (const std::out_of_range& )
	{
		return std::pair< MoveDirec, size_t>{ MoveDirec::Stand, 5};
	}
}
//===========================================================
Cat::Cat(const sf::Texture& txtr) :
	m_animation(txtr, sf::Vector2u(4, 8), 0.3f)
{}
//============================================================
void Cat::draw(sf::RenderWindow& window)const
{
	m_circle->draw(window);
	m_animation.draw(window);
}
//=============================================================
void Cat::move(Circle* circle)
{
	m_animation.setPosition(circle->getPosition());
	m_circle = circle;
}
//==============================================================
Circle* Cat::getMyCircle()
{
	return m_circle;
}
//==============================================================
bool Cat::checkIfCatWon() const
{
	return m_circle->isEdge();
}