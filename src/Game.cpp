#include "Game.h"
#include <iostream>


bool isKeyPressed(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}
//===============================================================
sf::Color getColor(const size_t& indx) {
	static const std::unordered_map<Colors, sf::Color> colors = {
			{ Black   ,sf::Color::Black} ,
			{ White   ,sf::Color::White },
			{ Red     ,sf::Color::Red },
			{ Green   ,sf::Color::Green },
			{ Blue    ,sf::Color::Blue },
			{ Yellow  ,sf::Color::Yellow },
			{ Magenta ,sf::Color::Magenta },
			{ Cyan    ,sf::Color::Cyan } 
	};
	try
	{
		return colors.at(static_cast<Colors>(indx));
	}

	catch (const std::out_of_range&)
	{
		return { sf::Color::White }; 
	}
}
//===============================================================
Game::Game() :
	m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), TITLE, sf::Style::Titlebar | sf::Style::Close),
	m_menu(WINDOW_SIZE, Manager::instance().getFont(Fonts::menu_font)),
	m_board(ROWS_SIZE, COLS_SIZE)
{
	initText(m_flyText, 30, INC_CLICKS, Manager::instance().getFont(Fonts::font5), getColor(Colors::Red),
		DRAW_TEXT_POS);
	m_background2.setTexture(Manager::instance().getTexture(Textures::Messages));
	m_msgText.setFont(Manager::instance().getFont(Fonts::some_font));
	initText(m_msgText, 25, "", Manager::instance().getFont(Fonts::some_font), getColor(White),
		sf::Vector2f(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2));

	m_window.setFramerateLimit(60);
	m_window.setVerticalSyncEnabled(true);
	srand(static_cast<unsigned>(std::time(nullptr)));
	Manager::instance().setLoop(Sounds::PlaySound, true);
}
//==================================================================
void Game::run()
{
	static auto gameClock = sf::Clock();
	auto time = sf::Time();
	auto mousePos = sf::Vector2f();
	auto mousePressed = false;
	auto isdrawFlyText = false;

	Manager::instance().play_stop(Sounds::PlaySound, PLAY);
	while (m_window.isOpen()) {
		draw(isdrawFlyText);
		handleEvents(mousePos, mousePressed, gameClock);
		updateGameObjects(mousePos, mousePressed, isdrawFlyText, gameClock, time);
	}
	Manager::instance().setLoop(Sounds::PlaySound, STOP);
}
//===================================================================
void Game::draw(const bool& isDrawText)
{
	m_window.clear(getColor(Colors::White));
	//if (m_gameStatus == GameStatus::PLAYING) 
	{
		m_board.draw(m_window);
		m_menu.getRstBtn().draw(m_window);
		if (isDrawText)
			m_window.draw(m_flyText);
	}
	m_window.display();
}
//===============================================================
void Game::handleEvents(sf::Vector2f& mousePos, bool& mousePressed, sf::Clock& gameClock)
{
	auto leftBtn = mousePressed = false;// set to false
	auto event = sf::Event();
	while (m_window.pollEvent(event)) 
	{
		runMain(gameClock);
		if (event.mouseButton.button == sf::Mouse::Left) { leftBtn = true; }

		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::MouseMoved:
			mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
			break;
		case sf::Event::MouseButtonPressed:
			if (leftBtn)
				mousePressed = true;
			Manager::instance().play_stop(Sounds::Click, PLAY);
			break;
		case sf::Event::MouseButtonReleased:
			mousePressed = false;
			break;
		}
	}
}
//===============================================================
void Game::runMain(sf::Clock& gameClock)
{
	while (m_menu.menuStatus() == Menu_t::MENU || m_gameStatus == GameStatus::MENU)
	{
		m_menu.run(m_window);
		if (m_menu.menuStatus() == Menu_t::PLAY) 
		{
			m_gameStatus = GameStatus::START_GAME;
		}
		if (m_menu.menuStatus() == Menu_t::EXIT) {
			m_gameStatus = GameStatus::EXIT;
			break;
		}
	}
}
//===============================================================
void Game::printScreen(const std::string& msg)
{
	setMsgText(msg + CONTINUE + EXIT);
	m_window.clear();
	m_window.draw(m_background2);
	m_window.draw(m_msgText);
	m_window.display();
	auto flag = false;
	do {
		for (auto event = sf::Event(); m_window.pollEvent(event);)
		{
			if ( isKeyPressed(sf::Keyboard::Escape))
			{
				m_gameStatus = GameStatus::END_GAME;
				return;
			}
			else if (isKeyPressed(sf::Keyboard::Space)) {
				flag = true;
				break;
			}
		}
	} while (!flag);
	m_gameStatus = GameStatus::PLAYING;
}
//===============================================================
void Game::setMsgText(const std::string& msg)
{
	m_msgText.setString(msg );
	m_msgText.setOrigin(m_msgText.getGlobalBounds().width / 2, m_msgText.getGlobalBounds().height / 2);
}
//===============================================================
void Game::updateGameObjects(const sf::Vector2f& mousePos, const bool& mouseReleased, bool& isDrawFlyText,
	sf::Clock& gameClock, sf::Time& time)
{
	const auto deltaTime = gameClock.restart();
	if (m_flyText.getPosition().y == 0) {
		isDrawFlyText = false;
		m_flyText.setPosition(DRAW_TEXT_POS);
	}{
	}
	m_board.handle(mouseReleased, isDrawFlyText, mousePos, m_menu.resetbtnclicked(mousePos), deltaTime.asSeconds());


	if (m_board.islvlWon()){
		m_gameStatus = GameStatus::LEVEL_UP;
		isDrawFlyText = false;
	}
	else if (m_board.isLvlose()) {
		isDrawFlyText = false;
		m_gameStatus = GameStatus::RESTART_LEVEL;
	}
	checkGameStatus(gameClock);
	if (isDrawFlyText) {
		time += deltaTime; // fly to void
		if (time.asSeconds() > 0.2 && m_flyText.getPosition().y != 0) {
			m_flyText.setPosition(m_flyText.getPosition() - sf::Vector2f(0, FLY_TEXT));
			time = sf::seconds(0);
		}
	}
}
//===============================================================
void Game::checkGameStatus(sf::Clock& gameClock)
{
	//=======test===========
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_gameStatus = GameStatus::END_GAME;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		m_gameStatus = GameStatus::LEVEL_UP;
	//====================
	switch (m_gameStatus) {
	case GameStatus::EXIT:
		m_window.close();
		return ;
	case  GameStatus::END_GAME:
		Manager::instance().play_stop(Sounds::EndGame, PLAY);
		goodBye(gameClock);
		break;
	case GameStatus::LEVEL_UP:
		m_board.startNewLvl(true);
		printScreen(WON_MSG + std::to_string(Manager::instance().lvlUp()));
		break;
	case  GameStatus::START_GAME:
		printScreen("Are you ready ?");
		break;
	case GameStatus::RESTART_LEVEL:
		m_board.startNewLvl(false);
		printScreen(LOSE_MSG);
		break;
	}
}
//===============================================================
void Game::goodBye(sf::Clock& gameClock)
{
	auto goodBye = sf::Text();
	initText(goodBye, 80, GOODBYE, Manager::instance().getFont(Fonts::font5),
		getColor(Colors::White), { WINDOW_SIZE.x / 2.f - 30.f, WINDOW_SIZE.y / 2.f });
	setMsgText(CONTINUE);
	auto time = float(0);
	gameClock.restart();
	auto indx = 0;
	auto color = sf::Color(getColor(indx));
	Manager::instance().play_stop(Sounds::PlaySound, STOP);

	Manager::instance().setLoop(Sounds::EndGame, true);
	draw2(goodBye);
	auto flag = false;
	do {
		for (auto event = sf::Event(); m_window.pollEvent(event);)
		{
			if (isKeyPressed(sf::Keyboard::Space)) {
				flag = true;    break;
			}
		}
		runLoop(time, gameClock, goodBye, color, indx);
	} while (!flag);
		Manager::instance().play_stop(Sounds::EndGame, STOP);
	Manager::instance().play_stop(Sounds::PlaySound, PLAY);
	m_gameStatus = GameStatus::MENU;
}
//===============================================================
void Game::runLoop(float& time, sf::Clock& gameClock, sf::Text& goodBye, sf::Color& color, int& indx)
{
	time += gameClock.getElapsedTime().asSeconds();

	if (time >= 15) {
		indx = (indx < 7 ? indx + 1 : 0);
		color = getColor(indx);
		goodBye.setFillColor(color);
		time = 0;
		draw2(goodBye);

		gameClock.restart();
	}
}
//===============================================================
void Game::draw2(sf::Text& goodBye)
{
	m_window.clear();
	m_menu.drawBackGround(m_window);
	m_window.draw(m_msgText);
	m_window.draw(goodBye);
	m_window.display();
}
