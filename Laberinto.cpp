#include "Laberinto.hpp" 
#include <time.h>

Laberinto::Laberinto(int Width, int Height)
{
	width = Width;
	height = Height;
	createCells();
	cur = &cells[0];
}

void Laberinto::createCells()
{
	for(int row = 0; row < height; row++){
		for(int column = 0; column < width; column++){
			cells.push_back(Cell(row, column));
		}
	}
}

void Laberinto::generateMaze()
{
	while(true){
		cur->setVisited(true);
		Cell *next = findNextCell();
		
		if(next != NULL){
			next->setVisited(true);
			history.push(cur);
			cur->removeWalls(*next);
			cur = next;
		}else if(history.size() > 0){
			cur = history.top();
			history.pop();
		}else if(history.size() == 0){
			break;
		}
	}	
	render();
}

int Laberinto::calculateIndex(int row, int column)
{
	if(row < 0 || column < 0 || column > width - 1 || row > height - 1){
		return -1;
	}else{
		return column + row * width;
	}
}


std::vector<Cell *> Laberinto::getAvailableNeighbors()
{
	std::vector<Cell *> neighbors;

	int currentRow = cur->getRow();
	int currentColumn = cur->getColumn();

	int neighborIndexes[4] = {
		calculateIndex(currentRow - 1, currentColumn),
		calculateIndex(currentRow, currentColumn + 1),
		calculateIndex(currentRow + 1, currentColumn),
		calculateIndex(currentRow, currentColumn - 1),
	};

	for (int i : neighborIndexes) {
		if (i != -1 && !cells[i].isVisited()) {
			neighbors.push_back(&cells[i]);
		}
	}

	return neighbors;
}

Cell* Laberinto::findNextCell()
{
	std::vector<Cell *> availableNeighbors = getAvailableNeighbors();
	
	if(availableNeighbors.size() > 0){
		return availableNeighbors.at(rand() % availableNeighbors.size());
	}
	
	return NULL;	
}

void Laberinto::render()
{
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			cells[i].show();
		}
	std::cout << std::endl;
	}
}


