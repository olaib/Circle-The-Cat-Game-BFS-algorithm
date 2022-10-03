#pragma once

const auto NUM_OF_FONTS = 6;
const auto NUM_OF_SOUND = 4;
const auto NUM_OF_TEXTURES = 6;
const auto PLAY = true;//play music
const auto STOP = false;//stop music

//description of teh funcs is on cpp
enum class Textures :size_t {
	Cat_t,
	Reset_btn,
	Background,
	Cats_t,
	RestartBtn,
	Messages
};

enum class Sounds :size_t {
	PlaySound,
	Click,
	Selected,
	EndGame
};

enum class Fonts :size_t {
	menu_font,
	some_font,
	font3,
	font1,
	font4,
	font5
};

enum Colors :size_t {
	Black,
	White,
	Red,
	Green,
	Blue,
	Yellow,
	Magenta,
	Cyan
};

enum class Menu_t :size_t
{
	MENU,
	PLAY,
	REPLAY,
	INTRO,
	EXIT
};

enum class Buttons :size_t {
	Play,
	About,
	Exit
};