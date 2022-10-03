#pragma once
#include "Manager.h"
#include "Cat.h"
#include "Bfs.h"
#include "Level.h"

//description of teh funcs is on cpp
class Board {
public:
	Board(const size_t&, const size_t&);
	void pushEvent(Circle*, Circle*);
	Circle* popEvent();
	void draw(sf::RenderWindow&);
	void handle(const bool&, bool&, const sf::Vector2f&, const bool&, const float&);

	void runLoopHanle(const sf::Vector2f&, const bool&, bool&, const float&);
	void checkButtons(const bool&, const bool&, const sf::Vector2f&);
	void moveCat(const float&);

	void startNewLvl(const bool&);

	auto islvlWon() const {
		return m_lvl.isLvlWon();
	}
	auto isLvlose()const {
		return m_lvl.isLvllose();
	};
	auto notEndOfLvl()const { return !islvlWon() && !isLvlose(); }
	
	void setLvlLose();
private:
	GridArr         m_grid;
	Cat             m_cat;
	bool			isAnimation      =   false;
	CircleList      m_eventsHolder = CircleList();
	Bfs             m_bfs;
	Level           m_lvl;
	bool            m_lvlWon = false;
	size_t		    m_clickCounter = 0;
	sf::Text        m_clickCount;


	void initGrid(const size_t&, const size_t&);
	void initMyList(const int&, const int&, Circle&);
	void buildLvl();

	std::pair<size_t,size_t> randomCircle();
	void resetLvl();
	void reset2start();
	auto ismouseOnCircle(const Circle& circle, const sf::Vector2f& mousePos) const 
	{ 
		return circle.getGlobalBounds().contains(mousePos);
	}
};