#pragma once
#include <array>
#include "Game.hpp"
#include "Button.h"
#include "Manager.h"

//description of teh funcs is on cpp
class Level {
public:
	Level();
	void saveLevel(const GridArr&);

	const std::array<std::array<bool, COLS_SIZE>, ROWS_SIZE>& getLvlArr()const;
	void randLvl();
	bool restartbtnclicked(const sf::Vector2f& pos);

	void setBlocCircNum(const size_t& value);
	void setCatCoordinates(const std::pair<size_t, size_t>& pair);
	void setLvlWon(const bool& val) {m_lvlWon= val;}
	void setLvlose(const bool& val) { m_lvlose = val; }

	const Button& getRstBtn() const;
	std::pair<size_t, size_t> getCatCoordinates()const;

	void draw(sf::RenderWindow& window);
	bool isLvlWon()const;
	bool isLvllose()const;
private:
	Button                    m_restartBtn;
	size_t                    m_numOfBlocked  =  MAX_LIMIT;
	sf::Text m_clickCount;
	std::pair<size_t, size_t> m_catPos;
	bool					  m_lvlWon        =  false
			                , m_lvlose        =  false;
	std::array<std::array<bool,COLS_SIZE>,ROWS_SIZE> m_level = {UNPRESSED};

	void randNumOfBlocked();
	void randBlockedCells();
};