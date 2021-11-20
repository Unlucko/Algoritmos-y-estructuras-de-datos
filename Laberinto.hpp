#ifndef _LABERINTO_HPP_
#define _LABERINTO_HPP_

#include <iostream>
#include <stack>
#include <vector>
#include "Celula.hpp"

class Laberinto
{
private:
	int width;
	int height;
	
	std::vector<Cell> cells;
	std::stack<Cell *> history;
	Cell *cur;
	
	void createCells();
	int calculateIndex(int row, int column);
	std::vector<Cell *> getAvailableNeighbors();
	Cell *findNextCell();
	void render();
	
public:
	Laberinto(int Width, int Height);
	void generateMaze();
	void solveMaze();
};

#endif
