#ifndef	_LABERINTO_HPP_
#define _LABERINTO_HPP_
#include <vector>
#include <fstream>
#include <iostream>
#include <time.h>

class Laberinto
{
private:
	int length, width, in, out;
	char** maze = new char*[length];
	
	void extractMaze();
	
public:
	Laberinto(unsigned a, unsigned b);
	void generateMaze();
	void printMaze();
};

#endif
