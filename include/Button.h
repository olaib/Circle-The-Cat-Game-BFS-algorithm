#pragma once
#include <SFML/Graphics.hpp>
#include "Manager.h"

//description of teh funcs is on cpp
class Button {
public:
	Button(const sf::Texture& txtr, const sf::Vector2f& pos);
	bool hovered(const sf::Vector2f& pos);
	void draw(sf::RenderWindow& window)const;
	const sf::Sprite& getBtn() const;
	bool clicked(const sf::Vector2f& pos);
private:
	sf::Sprite m_sprite;
};
bool ishovered(const sf::Vector2f& pos, const sf::FloatRect& rect);
bool ButtonClicked();