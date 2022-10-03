#include "Board.h"
#include <iostream>

//func to caalculate rand num
int randNum(const int& max = MAX, const int& min = MIN)
{
	return rand() % (max - min + 1) + min;
}
//=============================================================
//checking if there is atlst neighr that not pressed
auto is_any_neighbr_valid(const CircleList& neigbors) {
	return std::any_of(neigbors.cbegin(), neigbors.cend()
		, [](Circle* neighbor) { return !neighbor->isPressed(); });
}
//==============================================================
//c-tor
Board::Board(const size_t& rows, const size_t& cols) :
	m_cat(Manager::instance().getTexture(Textures::Cat_t)),
	m_bfs(Bfs()), m_lvl(Level())
{
	initGrid(rows, cols);
	startNewLvl(true);
	//initalizd the click counter txt
	Manager::instance().initText(m_clickCount, 40, "0", Manager::instance().getFont(Fonts::font5),
		sf::Color::Black, sf::Vector2f(620.f, 550.f));
}
//=================================================================
//store the 2 circls of the cat and the player
void Board::pushEvent(Circle* event1, Circle* event2)
{
	m_eventsHolder.emplace_back(event1);
	m_eventsHolder.emplace_back(event2);
	m_clickCount.setString("Clicks: " + std::to_string(++m_clickCounter));
}
//==================================================================
//pop the 2 circls of the cat and the player for 
Circle* Board::popEvent()
{
	auto lastEvnt = m_eventsHolder.back();
	m_eventsHolder.pop_back();
	return lastEvnt;
}
//====================================================================
void Board::draw(sf::RenderWindow& window)
{
	for (auto& rows : m_grid)
		for (auto& cols : rows) {
			cols->draw(window);
			cols->setOutlineThickness(0); // reset to unhovered
		}
	m_lvl.draw(window);
	m_cat.draw(window);
	window.draw(m_clickCount);
}
//=======================================================================
void Board::handle(const bool& leftBtnRealeased, bool& isDrawFlyText, const sf::Vector2f& mousePos, const bool& isResetBtnClicked, const float& time)
{
	runLoopHanle(mousePos, leftBtnRealeased, isDrawFlyText, time);
	checkButtons(leftBtnRealeased, isResetBtnClicked, mousePos);
}
//=======================================================================
void Board::runLoopHanle(const sf::Vector2f& mousePos, const bool& leftBtnRealeased, bool& isDrawFlyText, const float& time)
{
	for (auto& row : m_grid)
	{
		for (auto& circle : row)
		{
			if (ismouseOnCircle(*circle, mousePos)) {
				circle->setOutlineThickness(2);
				if (m_cat.checkIfCatWon()) {
					m_lvl.setLvlose(true);
				}
				if (leftBtnRealeased && !ismouseOnCircle(*m_cat.getMyCircle(), mousePos))
				{
					if (*circle != *m_cat.getMyCircle()) {
							if (notEndOfLvl())
							{
								circle->setClicked(PRESSED);
								if(!m_cat.checkIfCatWon())
									pushEvent(circle.get(), m_cat.getMyCircle());
								isDrawFlyText = true; // draw
							}
							moveCat(time);
						return;
					}
				}
			}
		}
	}
}
//========================================================================
//check the bottons
void Board::checkButtons(const bool& leftBtnRealeased, const bool& isResetBtnClicked, const sf::Vector2f& mousePos)
{
	if (leftBtnRealeased && !islvlWon() && !isLvlose())
	{
		if (isResetBtnClicked)
			if (!m_eventsHolder.empty())
			{
				auto catCircle = popEvent();
				auto mouseCircle = popEvent();
				mouseCircle->setClicked(UNPRESSED);
				m_clickCount.setString("Clicks: " + std::to_string(--m_clickCounter));
				m_cat.move(catCircle);
			}
		if (m_lvl.restartbtnclicked(mousePos)) {
			resetLvl();
			reset2start();
		}
	}
}
//================================================================
void Board::startNewLvl(const bool& isNewLvl)
{
	m_clickCounter = 0;
	if (isNewLvl) {
		m_lvl.setCatCoordinates(randomCircle());
		buildLvl();
	}
	else {
		resetLvl();
	}
	reset2start();
}
//===============================================================
void Board::setLvlLose()
{
	m_lvl.setLvlose(false);
}
//================================================================
//the func make a move for cat by doing bfs algo
void Board::moveCat(const float&)
{
	auto source = m_cat.getMyCircle();

	Circle* next(nullptr);
	//check if there are a valid neighbors to move
	if (!is_any_neighbr_valid(source->getNeighbors())) {
		m_lvl.setLvlWon(true);
		return;
	}
	//run bfs 
	next = m_bfs.run(source, m_grid);
	if (next)
		m_cat.move(next);
	//if there are no shortest path (non of edge circls unpressd so we take first valid nibr)
	else
		for (const auto& neighbor : m_cat.getMyCircle()->getNeighbors())
			if (!neighbor->isPressed())
				m_cat.move(neighbor);
}
//=================================================================
void Board::buildLvl()
{
	m_lvl.randLvl();
	resetLvl();
}
//=================================================================
//this func initialzied the circls of the board
void Board::initGrid(const size_t& rows, const size_t& cols)
{
	auto num = 0;
	for (auto row = 0; row < rows; ++row) 
	{
		for (auto col = 0; col < cols; ++col) 
		{
			m_grid[row][col] = std::make_unique<Circle>(num++, 
				sf::Vector2f(RADIOUS + (float)(row % 2 == 0 ? col : col + 0.5f) * FACTOR_X
				, RADIOUS + row * FACTOR_Y));

			if (col == 0 || col == cols - 1 || row == 0 || row == rows - 1)
				m_grid[row][col]->setEdge(true);
		}
	}
	for (auto row = 1; row < SIZE-1; row++)
		for (auto col = 1; col < SIZE - 1; col++)
			initMyList(row, col, *m_grid[row][col]);
}
//===================================================================
//this func initialzed nibrs list for the bfs
void Board::initMyList(const int& row, const int& col, Circle& circle)
{
	const auto value = (row % 2 ? col : col - 1);
	const std::initializer_list<std::pair<size_t, size_t>>
		row_col =
	{
		{ row - 1, value },
		{ row - 1, value + 1 },
		{ row, col - 1 },
		{ row, col + 1 },
		{ row + 1, value },
		{ row + 1, value + 1 }
	};
	for (const auto &pair : row_col) {
		circle.addNeighbors(m_grid[pair.first][pair.second].get());
	}
}
//====================================================================
//this func rand unpressed circle for the cat
std::pair<size_t,size_t> Board::randomCircle()
{
	auto circleCoord = std::pair<size_t, size_t>();
	do 
	{
		circleCoord = { randNum(),randNum() };
	} while (m_grid[circleCoord.first][circleCoord.second]->isPressed());
	return circleCoord;
}
//====================================================================
void Board::resetLvl()
{
	m_lvl.setLvlWon(false);
	m_lvl.setLvlose(false);
	const auto Lvl = m_lvl.getLvlArr();

	for (size_t i = 0; i < m_grid.size(); ++i)
	{
		for (size_t j = 0; j < m_grid[0].size(); ++j)
		{
			m_grid[i][j]->setClicked(Lvl[i][j]);
			m_grid[i][j]->setPred(nullptr);
		}
	}
}
//====================================================================
void Board::reset2start()
{
	auto catCoord = m_lvl.getCatCoordinates();
	m_cat.move(m_grid[catCoord.first][catCoord.second].get());
	m_clickCounter = 0;
	m_clickCount.setString("Clicks: 0");
	m_eventsHolder.clear();
}


