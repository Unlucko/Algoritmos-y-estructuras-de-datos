#include <iostream>
#include <vector>
#include <fstream>

#include "Laberinto.hpp"

using namespace std;

int main()
{
    Laberinto lab(30, 30);
    lab.generateMaze();
    lab.printMaze();
    
   
    return 0;
}
