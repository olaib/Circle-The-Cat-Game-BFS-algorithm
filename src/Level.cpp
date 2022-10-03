#include "Level.h"

//c-tor
Level::Level() :
	m_restartBtn(Manager::instance().getTexture(Textures::RestartBtn), sf::Vector2f(50.f, 550.f))
{}
//===============================================================
void Level::saveLevel(const GridArr& grid)
{
	for (size_t i = 0; i < m_level.size(); i++)
	{
		for (size_t j = 0; j < m_level[0].size(); j++)
		{
			m_level[i][j] = grid[i][j]->isPressed();
		}
	}
}
//===============================================================
const std::array<std::array<bool, COLS_SIZE>, ROWS_SIZE>& Level::getLvlArr() const
{
	return m_level;
}
//===============================================================
void Level::setBlocCircNum(const size_t& value)
{
	m_numOfBlocked = value;
}
//===============================================================
void Level::randNumOfBlocked()
{
	//first lvl start with MAX_LIMIT
	if (Manager::instance().getLvlNum() == 1)
		return;
	//rand number between last blocked Circle and at least must be between 4 - 14;
	const auto num = rand() % (m_numOfBlocked - MIN_LIMIT + 1) + MIN_LIMIT;
	
	setBlocCircNum(num);
}
//===============================================================
void Level::randBlockedCells()
{
	auto counter = 0;
	std::pair<size_t, size_t> pair;
	do {
		pair.first = rand() % m_level.size();
		pair.second = rand() % m_level[0].size();
		if (!m_level[pair.first][pair.second] && getCatCoordinates() != pair) 
		{
			m_level[pair.first][pair.second] = true;
			counter++;
		}
	} while (counter < m_numOfBlocked);
}
//===============================================================
void Level::randLvl()
{
	m_level = { false };
	randNumOfBlocked();
	randBlockedCells();
}
//===============================================================
const Button& Level::getRstBtn() const
{
	return m_restartBtn;
}
//===============================================================
bool Level::restartbtnclicked(const sf::Vector2f& pos)
{
	return (m_restartBtn.clicked(pos));
}
//===============================================================
void Level::setCatCoordinates(const std::pair<size_t, size_t>& pair)
{
	m_catPos = pair;
}
//===============================================================
std::pair<size_t, size_t> Level::getCatCoordinates() const
{
	return m_catPos;
}
//===============================================================
void Level::draw(sf::RenderWindow& window)
{
	window.draw(m_clickCount);
	window.draw(m_restartBtn.getBtn());
}
//===============================================================
bool Level::isLvlWon() const
{
	return m_lvlWon;
}
//===============================================================
bool Level::isLvllose() const
{
	return m_lvlose;
}