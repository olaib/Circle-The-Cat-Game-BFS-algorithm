#pragma once
#include "Game.hpp"
#include <array>


class Bfs {
public:
    //c-tor
	Bfs() = default;
	//function to run bfs
	Circle* run(Circle*, GridArr&);

private:
	void doBfs(GridArr&, Circle*);
	Circle* findNextMove(Circle*);
	Circle* minDisNode(const GridArr&);

};