#include "Celula.hpp"
#include <iostream>

Cell::Cell(int Row, int Column)
{
	row = Row;
	column = Column;
	visited = false;
	setWalls();
}

void Cell::setWalls()
{
	for(int i = 0; i < 4; i++){
		walls[i] = true;
	}
}

void Cell::setVisited(bool a)
{
	visited = a;
}

bool Cell::isVisited()
{
	return visited;
}

int Cell::getRow()
{
	return row;
}

int Cell::getColumn()
{
	return column;
}

void Cell::removeWalls(Cell &next)
{
	int x = column - next.column;
	int y = row - next.row;
	
	if(x == 1){
		walls[LEFT] = false;
		next.walls[RIGHT] = false;
	}else if(x == -1){
		walls[RIGHT] = false;
		next.walls[LEFT] = false;
	}else if(y == 1){
		walls[TOP] = false;
		next.walls[BOTTOM] = false;
	}else if(y == -1){
		walls[BOTTOM] = false;
		next.walls[TOP] = false;
	}
}

void Cell::show()
{
	if(walls[1]){
		walls[0] = '|';
	}
	
	if(walls[0]){
		wallsc[1] = '_';
	}
		
	if(walls[2]){
		wallsc[2] = '|';
	}
	
	if(walls[3]){
		wallsc[3] = '_';
	}
}

void Cell::print()
{
	std::cout << "row: " << row << "|";
	std::cout << "column: " << column << std::endl;
}
