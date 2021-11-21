#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <stack>
 
#define SIZE 9  //Numero de ancho y alto de el laberinto
 
// CELL STRUCTURE
struct Cell
{
    bool visited; 		//Celula base para el laberinto
    bool top_wall;
    bool bot_wall;
    bool left_wall;
    bool right_wall;
    char display;
};
 
// FUNCTION DECLARATIONS
void Initialize(Cell Level[][SIZE]);
void ClearScreen();
void Redraw(Cell Level[][SIZE]);
void GenerateMaze(Cell Level[][SIZE], int &posX, int &posY, int &goalX, int &goalY);
 
// MAIN
int main() {
    Cell maze[SIZE][SIZE];
    int posX = 0;
    int posY = 0;
    int goalX = 0;
    int goalY = 0;
    bool game_over = false;
 
    while(!game_over) {
        system("cls");		//Da la posibilidad de generar tantos laberintos como quiera el usuario
        Initialize(maze);
        Redraw(maze);
        GenerateMaze(maze, posX, posY, goalX, goalY);
 
        char input;
        std::cout << "Create a new Maze? (Y)/(N): ";
        std::cin >> input;
 
        if((input != 'n') && (input != 'N') && (input != 'y') && (input != 'Y'))
            std::cout << "Invalid option" << std::endl;
        else if((input == 'n') || (input == 'N')) {
            game_over = true;
            std::cout << "Good bye!" << std::endl;
        }
    }
 
    _getch();
    return 0;
}
 
// INITIALIZE MAZE
void Initialize(Cell Level[][SIZE]) {
    for(int i=0; i < SIZE; i++) {
        for(int j=0; j < SIZE; j++) {
            Level[i][j].display = '#';
            Level[i][j].visited = false;	//Llena el array bidimensional con celulas y incializa cada uno de sus valores
            Level[i][j].top_wall = true;
            Level[i][j].bot_wall = true;
            Level[i][j].left_wall = true;
            Level[i][j].right_wall = true;
        }
    }
    for(int i = 1; i < SIZE - 1; i++) {
        for(int j = 1; j < SIZE - 1; j++) {
            Level[1][j].top_wall = false;		//Hace que las paredes del laberinto no se puedan cambiar para que siempre se tengan paredes fijas
            Level[SIZE-2][j].bot_wall = false;
            Level[i][1].left_wall = false;
            Level[i][SIZE-2].right_wall = false;
        }
    }
}
 
// CLEAR SCREEN
void ClearScreen()//Limpia la pantalla de impresión
{
    HANDLE hOut;			
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}
 
// REDRAW MAZE
void Redraw(Cell Level[][SIZE]) //Función que dibuja el laberinto en pantalla
{
    for(int i=0; i<SIZE; i++) {
        std::cout << std::endl;
        for(int j=0; j< SIZE; j++)
            std::cout << " " << Level[i][j].display;
    }
}
 
// GENERATE MAZE
void GenerateMaze(Cell Level[][SIZE], int &posX, int &posY, int &goalX, int &goalY) //Función de generación del laberinto
{
    srand((unsigned)time(NULL));//Selección de una casilla aleatoria dentro de la matriz de celulas que tenemos                                            
    int random = 0;
    int randomX = ((2 * rand()) + 1) % (SIZE - 1);//Genera un numero impar entre 1 y SIZE                      
    int randomY = ((2 * rand()) + 1) % (SIZE - 1);   //Genera un numero impar entre 1 y SIZE                    
    posX = randomX;//Guarda la posicion incial X                                           
    posY = randomY;//Guarda la posicion incial Y                                             
    int visitedCells = 1;  //Contador de celulas visitadas
    int totalCells = ((SIZE - 1) / 2) * ((SIZE - 1) / 2);
    int percent = 0;
    std::stack<int> back_trackX, back_trackY;//Stacks para mantener cuenta del camino reverso                        
 
    Level[randomY][randomX].display = 'S';//Convierte a S en la celula inicial                     
    Level[randomY][randomX].visited = true;//Convierte a la celula inicial en una celula visitada                    
 
    while(visitedCells < totalCells)
    {
        if(((Level[randomY - 2][randomX].visited == false) && (Level[randomY][randomX].top_wall == true && Level[randomY - 2][randomX].bot_wall == true)) ||
           ((Level[randomY + 2][randomX].visited == false) && (Level[randomY][randomX].bot_wall == true && Level[randomY + 2][randomX].top_wall == true)) ||
           ((Level[randomY][randomX - 2].visited == false) && (Level[randomY][randomX].left_wall == true && Level[randomY][randomX - 2].right_wall == true)) ||
           ((Level[randomY][randomX + 2].visited == false) && (Level[randomY][randomX].right_wall == true && Level[randomY][randomX + 2].left_wall == true)))
        {
            random = (rand() % 4) + 1;     
 
             // GO UP
            if((random == 1) && (randomY > 1)) {
                if(Level[randomY - 2][randomX].visited == false) {  //Si no ha sido visitada aun 
                    Level[randomY - 1][randomX].display = ' ';   //Convierte en camino
                    Level[randomY - 1][randomX].visited = true;   //Marca la celula como visitada
                    Level[randomY][randomX].top_wall = false;   //Quita el muro de arriba de la celula
 
                    back_trackX.push(randomX);   //Ingresa X al backtrack       
                    back_trackY.push(randomY);     //Ingresa Y en el backtrack  
 
                    randomY -= 2;     //Se mueve a la celula              
                    Level[randomY][randomX].visited = true;     //Marca la celula a la que se movio como visitada
                    Level[randomY][randomX].display = ' ';//Actualiza el camino    
                    Level[randomY][randomX].bot_wall = false;   //Cambia la informacion del muro del lado inferior de la celula visitada
                    visitedCells++;  //Incrementa el contador de celuas visitadas                
                }
                else
                    continue;
            }
 
            // GO DOWN
            else if((random == 2) && (randomY < SIZE - 2)) {
                if(Level[randomY + 2][randomX].visited == false) {   //Si no ha sido visitada aun 
                    Level[randomY + 1][randomX].display = ' ';    //Convierte en camino
                    Level[randomY + 1][randomX].visited = true;   //Marca la celula como visitada
                    Level[randomY][randomX].bot_wall = false;   //Quita el muro de arriba de la celula
 
                    back_trackX.push(randomX); //Ingresa X al backtrack        
                    back_trackY.push(randomY); //Ingresa Y en el backtrack         
 
                    randomY += 2;      //Se mueve a la celula             
                    Level[randomY][randomX].visited = true;     //Marca la celula a la que se movio como visitada
                    Level[randomY][randomX].display = ' ';//Actualiza el camino     
                    Level[randomY][randomX].top_wall = false;    //Cambia la informacion del muro del lado superior de la celula visitada
                    visitedCells++;  //Incrementa el contador de celuas visitadas                
                }
                else
                    continue;
            }
 
            // GO LEFT
            else if((random == 3) && (randomX > 1)) {
                if(Level[randomY][randomX - 2].visited == false) {    //Si no ha sido visitada aun 
                    Level[randomY][randomX - 1].display = ' ';  //Convierte en camino
                    Level[randomY][randomX - 1].visited = true;  //Marca la celula como visitada
                    Level[randomY][randomX].left_wall = false;  //Quita el muro de arriba de la celula
 
                    back_trackX.push(randomX); //Ingresa X al backtrack         
                    back_trackY.push(randomY); //Ingresa Y en el backtrack       
 
                    randomX -= 2;     //Se mueve a la celula             
                    Level[randomY][randomX].visited = true;  //Marca la celula a la que se movio como visitada
                    Level[randomY][randomX].display = ' ';//Actualiza a camino la celula      
                    Level[randomY][randomX].right_wall = false;     //Cambia la informacion del muro del lado derecho de la celula visitada
                    visitedCells++;      //Incrementa el contador de celuas visitadas           
                }
                else
                    continue;
            }
 
            // GO RIGHT
            else if((random == 4) && (randomX < SIZE - 2)) {
                if(Level[randomY][randomX + 2].visited == false) {   //Si no ha sido visitada
                    Level[randomY][randomX + 1].display = ' ';    //Convierte en camino
                    Level[randomY][randomX + 1].visited = true;   //Marca la celula como visitada
                    Level[randomY][randomX].right_wall = false;  //Quita el muro de arriba de la celula
 
                    back_trackX.push(randomX);  //Ingresa X al backtrack      
                    back_trackY.push(randomY);  //Ingresa Y en el backtrack       
 
                    randomX += 2;   //Se mueve a la celula              
                    Level[randomY][randomX].visited = true;   //Marca la celula a la que se movió como visitada
                    Level[randomY][randomX].display = ' ';//Actualiza el camino    
                    Level[randomY][randomX].left_wall = false;  //Cambia la informacion del muro del lado izquierdo de la celula visitada
                    visitedCells++;     //Aumenta el contador de las celulas visitadas         
                }
                else
                    continue;
            }
 
            percent = (visitedCells * 100 / totalCells * 100) / 100;   //Porcentaje de avance en la creación del laberinto    
            std::cout << std::endl << "   Generating a Random Maze... " << percent << "%" << std::endl;
        }
        else {
            randomX = back_trackX.top();
            back_trackX.pop();
 
            randomY = back_trackY.top();
            back_trackY.pop();
        }
 
        ClearScreen();
        Redraw(Level);
    }
 
    goalX = randomX;   //Encuentra una celula aleatoria la cual va a ser la salida de el laberinto
    goalY = randomY;
    Level[goalY][goalX].display = 'E';
    system("cls");
    ClearScreen();
    Redraw(Level);
    std::cout << std::endl << "\a\t   Complete!" << std::endl;
}
