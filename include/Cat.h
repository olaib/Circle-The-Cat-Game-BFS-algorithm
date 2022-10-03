#pragma once
#include "Game.hpp"
#include "Animation2.h"
#include "Circle.h"

//description of teh funcs is on cpp
class Cat {
public:
	Cat(const sf::Texture&);

	void draw(sf::RenderWindow&) const;
	void move(Circle* circle);

	Circle* getMyCircle();
	bool checkIfCatWon()const;
private:
	Animation2     m_animation;
	Circle*        m_circle     =   nullptr;
};