#include "Laberinto.hpp"

Laberinto::Laberinto(unsigned a, unsigned b) 
{	
	length = a;//Declaración de las variables iniciales del laberinto tales como el ancho, el alto, la entrada y las sailda
	width = b;
	in = (rand() % length);
	out = (rand() % length);
	for(int i = 0; i < length; i++){//Inicialización de cada uno de los arrays como un array de carácteres
		maze[i] = new char[width];
	}	
}

void Laberinto::generateMaze(){ //Creación de la clase laberinto para poder visualizar el laberinto en consola representado con caracteres, donde el carácter número 219 de la tabla ascii son las paredes y los caminos libres son carácteres nulos o iguales a cero.
	for(int i = 0; i < length; i++){
		for(int j = 0; j < width; j++){
			if(i == 0 && j == in){
				maze[i][j] = 'e';
				maze[i+1][j] = 0;
			}else if(i == width-1 && j == out){
				maze[i][j] = 's';
				maze[i-1][j] = 0;
			}else{
				maze[i][j] = 219;
			}
		}
	}
	
	for(int i = 1; i < length-1; i++){ //Algoritmo que genera el laberinto
		for(int j = 1; j < width-1; j++){
			if((rand()%2) == 0){
				maze[i][j] = 0;
			}else if(maze[i-1][j] == 0 && maze[i+1][j] == 0){
				maze[i][j] = 219;
			}else if(maze[i][j-1] == 0 && maze[i][j+1] == 0){
				maze[i][j] = 219;
			}
		}
	}
	
	
	std::ofstream file("maze.txt"); //Creamos el archivo maze para almecenar y acceder al laberinto que se va a crear
	
	if(file.is_open()){	
		for(int i = 0; i < length; i++){ 	//Se pasa la información arraydel que ya tenemos al archivo
			for(int j = 0; j < width; j++){
				file << maze[i][j];
			}
			file << std::endl;
		}
	}else{
		std::cout << "No está abierto" << std::endl; //En caso de no poder abrir el archivo maze imprime El mensaje de error.
	}
	file.close();
}

void Laberinto::extractMaze()
{
	std::fstream file("maze.txt");
	std::string line;
	int row = 0;
	
	if(file.is_open()){
		while(getline(file, line)){
			for(unsigned i = 0; i < line.size(); i++){
				if(line[i] == '0'){
					maze[row][i] = 0;
				}else{
					maze[row][i] = line[i];
				}
			}
			row++;
		}
	}else{
		std::cout << "No se puede abrir el archivo";
	}
	file.close();
}

void Laberinto::printMaze()
{
	extractMaze();
	for(int i = 0; i < length; i++){
		for(int j = 0; j < width; j++){
			std::cout << maze[i][j];
		}
		std::cout << std::endl;
	}
}

