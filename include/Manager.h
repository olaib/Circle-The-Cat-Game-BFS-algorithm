#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Manager.hpp"
#include <array>

//description of teh funcs is on cpp
class Manager {
public:
	static Manager& instance();

	const sf::Font& getFont(Fonts indx)const;
	const sf::Texture& getTexture(Textures indx)const;

	void play_stop(Sounds sound, const bool& isPlay);
	void setLoop(Sounds sound,const bool& isLoop);
	bool isSoundStopped(Sounds sound)const;

	void initText(sf::Text& text, const size_t& charSize,
		const std::string& str, const sf::Font& font, const sf::Color& color, const sf::Vector2f& pos);
	auto getLvlNum()const { return m_lvlNum; }
	auto lvlUp() { return ++m_lvlNum; }
private:
	Manager();
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;

	std::array         <sf::Font, NUM_OF_FONTS>           m_fonts;
	std::array         <sf::Sound, NUM_OF_SOUND>          m_sounds;
	std::array         <sf::Texture, NUM_OF_TEXTURES>     m_textures;
	std::array         <sf::SoundBuffer, NUM_OF_SOUND>    m_soundsBuffer;
	size_t			    m_lvlNum = 1;

	void initTextures();
	void initSounds();
	void initFonts();
};