#pragma once
#include <string>
#include <array>
#include "Button.h"
#include "Game.hpp"

const auto MAX_NUMBER_OF_ITEMS = 3;
using string = std::string;

//description of teh funcs is on cpp
class Menu
{
public:
	Menu(const sf::Vector2u& windowSize, const sf::Font& font);
	void run(sf::RenderWindow& window);
	void setFrame(const sf::Text& text);
	const Menu_t& menuStatus()const;
	const Button& getRstBtn() const;
	bool resetbtnclicked(const sf::Vector2f& pos);
	void drawBackGround(sf::RenderWindow& window) const;
private:
	Menu_t              m_menuStatus  =  Menu_t::MENU;
	sf::Text            m_About;
	sf::RectangleShape  m_AboutRect,
	                    m_rect;
	sf::Text            m_menu[MAX_NUMBER_OF_ITEMS],  // main menu
						m_menuTitle;
	Button				m_resetBtn;
	sf::Sprite          m_background;

	void initAbout();
	void getAboutText();

	void draw(sf::RenderWindow& window)const;
	void init(const sf::Vector2u& windowSize, const sf::Font& font);
	void update(sf::RenderWindow& window);
	void checkIfMouseHovered(const sf::Vector2f& mousePos);
};

void initText(sf::Text&, const size_t&, const std::string&, const sf::Font&, const sf::Color&, const sf::Vector2f&);