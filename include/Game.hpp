#pragma once
#include "Circle.h"
#include <unordered_map>

//description of teh funcs is on cpp
enum class CatPosInTxtr :size_t {
	Down,
	Right,
	Up,
	Left,
	Stand = 5
};

enum class MoveDirec {
	Right,
	Left,
	RightUp,
	RightDown,
	LeftUp,
	LeftDown,
	Stand
};

static const auto ROWS_SIZE = (size_t)11;
static const auto SIZE = (size_t)11;
static const auto COLS_SIZE = ROWS_SIZE;
const auto MAX_LIMIT = 14;
const auto MIN_LIMIT = 4;

using GridArr = std::array<std::array<std::unique_ptr<Circle>, ROWS_SIZE>, COLS_SIZE>;
using CircleList = std::list<Circle*>;


static const auto FACTOR_X = 65.f;
static const auto FACTOR_Y = 50.f;

 
static const auto WINDOW_SIZE = sf::Vector2u(800, 600);
static const auto TITLE = "Circle the cat";
static const auto FLY_TEXT = 30.f;
static const auto DRAW_TEXT_POS = sf::Vector2f(WINDOW_SIZE.x - 100.f, 60.f);
static const auto MIN = 3;
static const auto MAX = SIZE-4;
 
static const auto GOODBYE = "Good Bye (:";
static const auto INC_CLICKS = "Clicks--";
static const auto LOSE_MSG = "Losing a game is not a big deal, except you've got\n"
	  					     "To make sure that you move on and get the next one";
static const auto CONTINUE = "\n**Press SPACE to continue**\n";
static const auto EXIT = "**Press ESC to exit**";

static const auto WON_MSG = "Take your game to the next level\n nice job you reached level :";