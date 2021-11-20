#ifndef _CELULA_HPP_
#define _CELULA_HPP_

class Cell
{
private:
	int row, column;
	bool walls[4];
	bool visited;
	enum direction {TOP, RIGHT, BOTTOM, LEFT};
	

public:
	Cell(int i, int j);
	
	Cell *checkNeighbors();
	void print();
	void show();
	void removeWalls(Cell &);
	
	bool isVisited();	
	void setVisited(bool a);
	void setWalls();
	
	char wallsc[4];
	int getRow();
	int getColumn();
};

#endif
