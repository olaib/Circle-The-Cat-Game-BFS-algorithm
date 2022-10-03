#pragma once 
#include "Menu.h"
#include "Board.h"
#include <unordered_map>

//description of teh funcs is on cpp
enum class GameStatus :unsigned
{
	MENU,
	START_GAME,
	GAME_OVER,
	RESTART_LEVEL,
	LEVEL_UP,
	PLAYING,
	END_GAME,
	EXIT
};

class Game {
public:
	Game();
	void run();
private:
	Menu						m_menu;
	Board						m_board;
	sf::RenderWindow			m_window;
	GameStatus m_gameStatus =	GameStatus::MENU;
	sf::Sprite					m_background2;
	sf::Text					m_flyText, // click --
								m_msgText;
	void printScreen(const std::string& msg);
	void setMsgText(const std::string& msg);
	void updateGameObjects(const sf::Vector2f& , const bool& , bool& ,sf::Clock& , sf::Time& );

	void draw(const bool& isDrawText);
	void handleEvents(sf::Vector2f& , bool& , sf::Clock& );
	void runMain(sf::Clock& );
	void checkGameStatus(sf::Clock& );
	void goodBye(sf::Clock& );

	void runLoop(float& , sf::Clock& , sf::Text& ,sf::Color& , int& );
	void draw2(sf::Text& goodBye);
};