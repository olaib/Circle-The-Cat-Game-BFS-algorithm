#include "Bfs.h"
#include <iostream>

/// This function will:
/// - Mark all the nodes as unvisited
/// - Initializes all of their predecessor as NULL
/// - Initializes all of distance from source node as infinity
static void reinitialize(GridArr& grid)
{
	for (auto& row : grid)
		for (auto& circle : row) {
			circle->update();
		}
}
//==================================================================
void Bfs::doBfs(GridArr& grid, Circle* source)
{
	reinitialize(grid);
	auto queue = CircleList();
	source->setAsSource();//the source node
	queue.emplace_back(source);
	//visiting all neighbors and update the distance
	while (!queue.empty()) {
		auto node = queue.front();
		queue.pop_front();

		for (auto &next : node->getNeighbors()) 
		{
			if (next->isValid()) {
				next->update(VISITED, node, node->getDistance() + 1);
				queue.emplace_back(next);
			}
		}
	}
}
//=======================================================================
//visit the shortest path and finding cats neighbor
Circle* Bfs::findNextMove(Circle* prev)
{
	if (!prev) 
		return nullptr;

	//go backward utill the predessor is a one of source's neighbors
	while (prev->getPred()->getPred()) {
		//push_front(prev);
		prev = prev->getPred();
	}
	//return next node in shortest path
	return prev;
}
//====================================================================
//finding the edge node circle with min dis from source
Circle* Bfs::minDisNode(const GridArr& grid)
{
	auto minDis = size_t(INT_MAX); // set to infinity
	Circle* minDisNode = nullptr;

	for (const auto& row : grid)
	{
		for (const auto& node : row)
		{
			if (node->isValidEdge())
			{
				if (node->getDistance() < minDis)
				{
					minDis = node->getDistance();
					// store min distance edge circle from source
					minDisNode = node.get();
				}
			}
		}
	}
	return minDisNode;
}
//==================================================================
Circle* Bfs::run(Circle* source, GridArr& grid)
{
	Circle* next(nullptr);

	{
		doBfs(grid, source);
		next = minDisNode(grid);
		next = findNextMove(next);
	}
	return next;
}
