#pragma once
#include "SFML/Graphics.hpp"
#include <list>

static const  auto UNPRESSED_CLR = sf::Color(204, 255, 0);
static const auto PRESSED_CLR = sf::Color(130, 162, 0);
static const auto HOVERED_CELL = sf::Color(204, 204, 204);
static const auto PRESSED = true;
static const auto UNPRESSED = false;
static const auto UNVISITED = false;
static const auto VISITED = true;
const auto RADIOUS = 25.f;

//description of teh funcs is on cpp
class Circle {
public:
	Circle();
	Circle(const size_t& serialNum,const sf::Vector2f& pos);
	Circle(const Circle&);

	void setEdge(const bool& isEdge) {m_isEdge = isEdge; }
	void setAsSource();
	bool isValid()const;
	auto getGlobalBounds()const { return m_circle.getGlobalBounds(); }

	auto isPressed()const { return m_isPressed; }

	std::list<Circle*> getNeighbors() { return m_neigbors; }

	void update(const bool& isVisited = UNVISITED, Circle* pred = nullptr,
		const size_t distance = size_t(INT_MAX));

	auto getDistance()const { return m_distance; }

	auto getPred()const { return (m_pred?m_pred:nullptr); }

	auto isValidEdge()const {return m_pred && m_isEdge;}


	void setOutlineThickness(const float& thick);
	void setPred(Circle* pred);
	void setClicked(const bool& isBlocked);

	auto getshape()const { return m_circle; }
	auto getSerialNum()const { return m_serialNum; }
	auto getPosition()const { return m_circle.getPosition(); }
	bool isEdge()const { return m_isEdge; }

	void draw(sf::RenderWindow& window)const;

	void addNeighbors(Circle* neighbor);
private:
	sf::CircleShape        m_circle;
	bool                   m_isPressed =			UNPRESSED,
		                   m_visited   =			UNVISITED,
		                   m_isEdge    =			false;
	size_t                 m_distance  =			INT_MAX,
						   m_serialNum =			0;
	Circle*				   m_pred      =			nullptr;
	std::list<Circle*>     m_neigbors;

	void init();
};

bool operator==(const Circle& c1, const Circle& c2);
bool operator!=(const Circle& c1, const Circle& c2);