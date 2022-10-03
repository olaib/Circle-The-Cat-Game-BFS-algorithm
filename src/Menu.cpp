#include "Menu.h"
#include <iostream>
#include "Manager.h"
#include <fstream>

const auto FILE_NAME = "resources/About_text.txt";
const auto OPEN_FAILED = "Error in opening file!";


//------------------------------------------------------------------------------------------------
//c_tor of Menu
Menu::Menu(const sf::Vector2u& windowSize, const sf::Font& font) :
	m_resetBtn(Manager::instance().getTexture(Textures::Reset_btn), sf::Vector2f(750.f, 550.f))
{
	init(windowSize, font);
}
//------------------------------------------------------------------------------------------------
void Menu::init(const sf::Vector2u& windowSize, const sf::Font& font)
{
	const auto pos = sf::Vector2f(windowSize);
	m_background.setTexture(Manager::instance().getTexture(Textures::Background));
	initAbout();
	//Main Menu
	initText(m_menuTitle, 50, "Main Menu", font, sf::Color(214, 203, 129),
		{ pos.x / 2.f - 100, 0 });
	initText(m_menu[0], 30, "Play", font, sf::Color::White,
		{ pos.x / 2.f, pos.y / (MAX_NUMBER_OF_ITEMS + 1) });
	initText(m_menu[1], 30, "About", font, sf::Color(214, 203, 129),
		{ pos.x / 2.f, pos.y / (MAX_NUMBER_OF_ITEMS + 1) * 2 });
	initText(m_menu[2], 30, "Exit", font, sf::Color(214, 203, 129),
		{ pos.x / 2.f, pos.y / (MAX_NUMBER_OF_ITEMS + 1) * 3 });
}

//------------------------------------------------------------------------------------------------
//this func is main menu
void Menu::run(sf::RenderWindow& window)
{
	auto mousePressed = false;
	m_menuStatus = Menu_t::MENU;

	while (window.isOpen()){
		draw(window);
		update(window);
		
		for (auto event = sf::Event() ; window.pollEvent(event);)
		{
			switch (event.type) {
			case sf::Event::MouseButtonPressed:
				if (!mousePressed) {
					mousePressed = true;
					Manager::instance().play_stop(Sounds::Click, PLAY);
				}
				break;
			case sf::Event::MouseButtonReleased:
				mousePressed = false;
				Manager::instance().play_stop(Sounds::Click, PLAY);//button pressed sound
				if (m_menuStatus == Menu_t::PLAY || m_menuStatus == Menu_t::EXIT) { //Play selected
					return;
				}
				break;
			}
			break;
		}
	}
}
//==========================================================
void Menu::setFrame(const sf::Text& text)
{
	m_rect.setOrigin(text.getOrigin());
	m_rect.setPosition(text.getPosition());
	m_rect.setSize(sf::Vector2f(text.getGlobalBounds().width,
								text.getGlobalBounds().height));
}
//==========================================================
void Menu::update(sf::RenderWindow& window)
{
	const auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	checkIfMouseHovered(mousePos);
	if (m_menuStatus == Menu_t::INTRO)
	{
		if (resetbtnclicked((mousePos))) {
			m_menuStatus = Menu_t::MENU;
		};
	}
}
//==========================================================
void Menu::checkIfMouseHovered( const sf::Vector2f& mousePos)
{
	static const
		std::initializer_list<std::pair<const sf::String&, Menu_t>>
		btn2MenuState =
	{
		{ m_menu[static_cast<size_t>(Buttons::Play)].getString()  , Menu_t::PLAY},
		{ m_menu[static_cast<size_t>(Buttons::About)].getString() , Menu_t::INTRO},
		{ m_menu[static_cast<size_t>(Buttons::Exit)].getString()  , Menu_t::EXIT},
	};

	for (auto& btn : m_menu) {
		if (ishovered(mousePos ,btn.getGlobalBounds())) {
			btn.setFillColor(sf::Color::White);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				for (const auto& pair : btn2MenuState) {
					if (btn.getString() == pair.first) {
						m_menuStatus = pair.second;
						break;
					}
				}
			}
		}
		else
			btn.setFillColor(sf::Color(214, 203, 129));
	}
}
//==========================================================
const Menu_t& Menu::menuStatus() const
{
	return m_menuStatus;
}
//==========================================================
const Button& Menu::getRstBtn() const
{
	return m_resetBtn;
}
//------------------------------------------------------------------------------------------------
// this func is about About
void Menu::initAbout()
{
	getAboutText();
	m_About.setFont(Manager::instance().getFont(Fonts::some_font));
	m_About.setCharacterSize(24);
	m_About.setOutlineColor(sf::Color::White);
	auto textRec = sf::FloatRect(m_About.getLocalBounds());
	m_About.setOrigin(textRec.width / 2.f, textRec.height / 2.f);
	m_About.setPosition(sf::Vector2f(400.f, 300.f));
	m_About.setFillColor(sf::Color::Black);
	//init rectangle frame of About
	m_rect.setFillColor(sf::Color::White - sf::Color(0, 0, 0, 100));
	m_rect.setOutlineColor(sf::Color::Black);
	m_rect.setOutlineThickness(1.f);
	setFrame(m_About);
}
//------------------------------------------------------------------------------------------------
// reads from file about msg
void Menu::getAboutText()
{
	auto inpFile = std::ifstream(FILE_NAME);
	if (!inpFile) {
		std::cerr << OPEN_FAILED << std::endl;
		return;
	}
	string line ,msg ;
	//reading whole input file
	while (std::getline(inpFile, line)) { msg += line + "\n"; }
	inpFile.close();
	m_About.setString(msg);
}
//==========================================================
void Menu::draw(sf::RenderWindow& window) const
{
	window.clear();
	window.draw(m_background);

	if (m_menuStatus == Menu_t::INTRO)
	{
		window.draw(m_rect);
		window.draw(m_About);
		m_resetBtn.draw(window);
	}
	//if we still in menu
	else {
		window.draw(m_menuTitle);
		for (auto button : m_menu)
			window.draw(button);
	}
	window.display();
}
//==========================================================
void Menu::drawBackGround(sf::RenderWindow& window) const
{
	window.draw(m_background);
}
//==========================================================
bool Menu::resetbtnclicked(const sf::Vector2f& pos)
{
	return m_resetBtn.clicked(pos);
}
//==========================================================
void initText(sf::Text& text, const size_t& charSize, const std::string& str, const sf::Font& font,
					const sf::Color& color, const sf::Vector2f& pos)
{
	text.setFont(font);
	text.setFillColor(color);
	text.setString(str);
	text.setCharacterSize(charSize);
	text.setPosition(pos);
}