#include "Animation2.h"
#include <unordered_map>

//this function recive enum val and then return the wanted pos of nxt move 
sf::Vector2f dirFromMove(MoveDirec move)
{
    static const
        std::unordered_map<MoveDirec, sf::Vector2f>
        movet2VecMapping =
    {
        { MoveDirec::Right,    {  1 , 0 }},
        { MoveDirec::Left ,    { -1 , 0 }},
        { MoveDirec::RightUp,  {  1 ,-1 }},
        { MoveDirec::RightDown,{  1 , 1 }},
        { MoveDirec::LeftUp,   { -1 ,-1 }},
        { MoveDirec::LeftDown, { -1 , 1 }}
    };
    try
    {
        return movet2VecMapping.at(move);
       
    }

    catch (const std::out_of_range&)
    {
        return { 0, 0 }; // no movement
    }
}
//==========================================================================
//c-tor for intializing a sprite sheet
Animation2::Animation2(const sf::Texture& texture, const sf::Vector2u& imageCount, const float& switchTime):
    m_totalTime(0.0f), m_imageCount(imageCount), m_switchTime(switchTime)
{
    m_currentImage.x = 0;
    m_rect.width  = int(texture.getSize().x / float(imageCount.x));
    m_rect.height = int(texture.getSize().y / float(imageCount.y));
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(m_rect);
    m_sprite.setOrigin(50,50);
}
//=============================================================================
//run animation
void Animation2::update(size_t& row, const float& deltaTime)
{
    m_currentImage.y = row;
    m_totalTime += deltaTime;

    if(m_totalTime >= m_switchTime)
    {
        m_totalTime -= m_switchTime;
        m_currentImage.x++;

        if(m_currentImage.x >= m_imageCount.x)
        {
            m_currentImage.x = 0;
        }
    }

    m_rect.left = m_currentImage.x * m_rect.width;
    m_rect.top = m_currentImage.y * m_rect.height;
    m_sprite.setTextureRect(m_rect);
}
//=====================================================================
void Animation2::setPosition(const sf::Vector2f& position)
{
    m_sprite.setPosition(position);
}
//======================================================================
void Animation2::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}
//======================================================================
void Animation2::move(MoveDirec dir, const float& deltaTime, const float& speed)
{
    const auto wantedPos = sf::Vector2f(dirFromMove(dir) * speed * deltaTime);
    m_sprite.move(wantedPos);
}
