#include "Manager.h"
#include <iostream>

using std::cerr;

//==========================================================
Manager::Manager()
{
	initTextures();
	initSounds();
	initFonts();
}
//==========================================================
void Manager::initTextures()
{
	auto filesName = std::array<std::string, NUM_OF_TEXTURES>({
		"resources/blackCat.png",
		"resources/back.png",
		"resources/background.png",
		"resources/cats.png",
		"resources/restart.png",
		"resources/msg.png"
		});
	auto texture = sf::Texture();
	for (auto i = size_t(0); i < NUM_OF_TEXTURES; i++) {
		if (!texture.loadFromFile(filesName.at(i))) {
			cerr << "Could not load texture" << std::endl; return;
		}
		m_textures.at(i)=texture;
	}
	m_textures.at((size_t)Textures::Cats_t).setSmooth(true);
}
//==========================================================
void Manager::initSounds()
{
	auto filesName = std::array<std::string, NUM_OF_SOUND>({
		"resources/game-music.wav",
		"resources/mouse-click.wav",
		"resources/selected.wav",
		"resources/end-game.wav"
		});
	for (auto i = size_t(0); i < NUM_OF_SOUND; i++) {
		if (!m_soundsBuffer.at(i).loadFromFile(filesName.at(i))) 
		{
			cerr << "Could not load sound " <<i<< std::endl;  
			return;
		}
		m_sounds.at(i).setBuffer(m_soundsBuffer[i]);
		m_sounds.at(i).setVolume(35.f);
	}
	m_sounds.at(0).setVolume(15.f);
}
//==========================================================
void Manager::initFonts()
{
	auto filesName = std::array<std::string, NUM_OF_FONTS>({
		"resources/menu_font.ttf",
		"resources/some_font.ttf",
		"resources/font3.ttf",
		"resources/font1.ttf",
		"resources/font4.otf",
		"resources/font5.otf"
		});
	for (auto i = size_t(0); i < NUM_OF_FONTS; i++) {
		if (!m_fonts[i].loadFromFile(filesName.at(i)))
		{
			cerr << "Could not load font " << std::endl;  return;
		}
	}
}
//==========================================================
void Manager::initText(sf::Text& text, const size_t& charSize, const std::string& str, const sf::Font& font, const sf::Color& color, const sf::Vector2f& pos)
{
	text.setFont(font);
	text.setFillColor(color);
	text.setString(str);
	text.setCharacterSize(charSize);
	text.setPosition(pos);
}
//==========================================================
Manager& Manager::instance()
{
	static auto instance = Manager();
	return instance;
}
//==========================================================
const sf::Font& Manager::getFont(Fonts indx) const
{
	return m_fonts.at(static_cast<size_t>(indx));
}
//==========================================================
const sf::Texture& Manager::getTexture( Textures indx) const
{
	return m_textures.at(static_cast<size_t>(indx));
}
//==========================================================
void Manager::play_stop(Sounds sound, const bool& isPlay)
{
	isPlay ? m_sounds.at(static_cast<size_t>(sound)).play() : m_sounds.at(static_cast<size_t>(sound)).stop();
}
//==========================================================
void Manager::setLoop(Sounds sound, const bool& isLoop)
{
	m_sounds.at(static_cast<size_t>(sound)).setLoop(isLoop);
}
//==========================================================
bool Manager::isSoundStopped(Sounds sound) const
{
	return  m_sounds.at(static_cast<size_t>(sound)).getStatus() == sf::SoundSource::Status::Stopped;
}