#pragma once
#include "Game.hpp"

class Animation2 {
public:
    Animation2(const sf::Texture& texture, const sf::Vector2u& imageCount, const float& switchTime);

    void update(size_t& row, const float& deltaTime);
    void draw(sf::RenderWindow& window) const;
    void move(MoveDirec dir, const float& deltaTime, const float& speed);

    void setPosition(const sf::Vector2f& position);
    auto getPos()const { return m_sprite.getPosition(); }
private:
    float          m_totalTime
                  ,m_switchTime;
    sf::Sprite     m_sprite;
    sf::Vector2u   m_imageCount,
                   m_currentImage;
    sf::IntRect    m_rect;
};

