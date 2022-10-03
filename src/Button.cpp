#include "Button.h"

//c-tor
Button::Button(const sf::Texture& txtr, const sf::Vector2f& pos)
{
	m_sprite.setTexture(txtr);
	m_sprite.setPosition(sf::Vector2f(pos));
}
//=================================================================
bool Button::hovered(const sf::Vector2f& pos)
{
	auto buttonPressed = ishovered( pos, m_sprite.getGlobalBounds());
	m_sprite.setColor(buttonPressed ? sf::Color::Cyan :sf::Color::White);
	return buttonPressed;
}
//=================================================================
void Button::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}
//=================================================================
const sf::Sprite& Button::getBtn() const
{
	return m_sprite;
}
//=================================================================
bool Button::clicked(const sf::Vector2f& pos)
{
	return hovered(pos) && ButtonClicked();
}
//==================================================================
bool ishovered(const sf::Vector2f& pos, const sf::FloatRect& rect)
{
	return rect.contains(pos);
}
//===================================================================
bool ButtonClicked()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		Manager::instance().play_stop(Sounds::Click, PLAY);
		return true;
	}
	return false;
}
