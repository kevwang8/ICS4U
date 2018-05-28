//NOTE* Because of the way I learned queues, I ended up changing alot of variables and adding classes and stuff
//so this algorithm is very different from the first algorithm

/*****************************************************************************
 *	Name:   Kevin Wang
 *	File:   mazeBFS.cpp
 *	Course: ICS4U
 *	Date:   May 11, 2018
 *
 *	Purpose: Scans in a maze with a start and a goal and it moves along the maze
 *           until it finds the goal or looks everywhere and there is no goal.
 *           Instead of just one moving path this uses a queue and has several moving paths looking for the goal
 *
 *	Usage: Enter in a valid maze file with the dimensions at the top. Then watch the
 *         maze search itself
 *
 *	Revision History: N/A
 *
 *	Known Issues: N/A
 *
 *****************************************************************************/
#include <iostream>
#include <fstream>
#include <apmatrix.h>
#include <queue>
#include <windows.h>

using namespace std;
//this code including all the rest of its kind was inspired from a post in dreamincode.net
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //used in printing in colour and printing at a specific place

struct PathCoords{
    int x;
    int y;
};

struct Characteristics{
    char mazeCharacter; //the characters in the maze
    Characteristics* prev = nullptr; //allows for tracking of where the path goes
    bool used = false; //tells if the spot has already been used
    PathCoords position; //stores all the positions of the path for printing the correct at the end
};

void fileLoad(int dimension[], apmatrix<Characteristics> &maze); //loads maze file
void findStart(apmatrix<Characteristics> &maze, int &x, int &y); //finds the start position
//finds the path using a BFS algorithm with queues
bool bfsAlgorithm(apmatrix<Characteristics> &maze, queue<PathCoords> &mazePathsQueue, PathCoords &pos);
void printNotPath(apmatrix<Characteristics> &maze); //prints the spaces that arent the path x's
void printCorrectPath(apmatrix<Characteristics> &maze, PathCoords pos); //prints the path to the screen using pointers

int main(){

    int start_x = -1;
    int start_y = -1;
    int dimension[2] = {0};
    apmatrix<Characteristics> maze(20, 20);

    fileLoad(dimension, maze);

    findStart(maze, start_x, start_y);

    PathCoords pos; //the position of the current path

    pos.x = start_x;
    pos.y = start_y;

    queue<PathCoords> mazePathsQueue; //each item in the queue is kept as a pair of coordinates
    mazePathsQueue.push(pos); //pushes in the start position to the queue

    //calls the bfs function and if it returns true it means the goal was found
    if (bfsAlgorithm(maze, mazePathsQueue, pos)){
        cout << endl << "Goal Found!" << endl;
        printCorrectPath(maze, pos);
    }
    else
        cout << endl << "No Path Found!" << endl;

    printNotPath(maze);

    return 0;
}

void fileLoad(int dimension[], apmatrix<Characteristics> &maze){

    char fileName[50];
    cout << "Enter your maze file" << endl;
    cin >> fileName;

    system("CLS");
    ifstream loadFile;
    loadFile.open(fileName);


    if (!loadFile){ //checks if file was found and displays error message if not
        cerr << "File not found" << endl;

    }
    //scans in the dimensions on the maze
    for (int i = 0; i < 2; i++){
        loadFile >> dimension[i];
    }

    maze.resize(dimension[0], dimension[1]);

    //scans in the contents of the maze and prints it
    for (int i = 0; i < dimension[0]; i++){
        for (int j = 0; j < dimension[1]; j++){
            loadFile >> maze[i][j].mazeCharacter;
            cout << maze[i][j].mazeCharacter;
        }
        cout << endl;
    }

    loadFile.close();
}

void findStart(apmatrix<Characteristics> &maze, int &x, int &y){
//goes through the contents of the map and finds the position of the start
    for (int i = 0; i < maze.numrows(); i++){
        for (int j = 0; j < maze.numcols(); j++){
            if(maze[i][j].mazeCharacter == 'S'){
                y = i;
                x = j;
                break;
            }
        }
    }
}

bool bfsAlgorithm(apmatrix<Characteristics> &maze, queue<PathCoords> &mazePathsQueue, PathCoords &pos){
    //for printing to console
    COORD coord;
    DWORD count;

    //keep going if there is still something in the queue
   if (!mazePathsQueue.empty()){

        pos = mazePathsQueue.front();
        //checks for goal
        if (maze[pos.y][pos.x].mazeCharacter == 'G')
            return true;

        //changes the path to a * to show it visited there
        if (maze[pos.y][pos.x].mazeCharacter != 'S'){

            maze[pos.y][pos.x].mazeCharacter = '*';

            coord = {maze[pos.y][pos.x].position.x, maze[pos.y][pos.x].position.y};
            FillConsoleOutputCharacter(hStdOut, maze[pos.y][pos.x].mazeCharacter, 1, coord, &count);
            FillConsoleOutputAttribute(hStdOut, FOREGROUND_BLUE, 1, coord, &count);
            Sleep(50);
        }

        //keeps track of which spots were already used
        maze[pos.y][pos.x].used = true;
        //takes the top of the queue out because it will be finished with after the function goes through
        mazePathsQueue.pop();
        //north
        if ((pos.y - 1) >= 0 && !maze[pos.y-1][pos.x].used && maze[pos.y-1][pos.x].mazeCharacter != '#'){
            pos.y--; //moves position
            //keeps track of which spots were already used
            maze[pos.y][pos.x].used = true;
            //keeps track of the position of that path for the printing path part
            maze[pos.y][pos.x].position = pos;
            //pushes in the position into the queue
            mazePathsQueue.push(pos);
            //keeps track of the path by pointing back to the previous item
            maze[pos.y][pos.x].prev = &maze[pos.y + 1][pos.x];

            pos.y++; //increments it back so it can look at all the other possible directions from that one place
        }//east
        if ((pos.x + 1) < maze.numcols() && maze[pos.y][pos.x+1].mazeCharacter != '#' && !maze[pos.y][pos.x+1].used){
            pos.x++; //moves position

            //keeps track of which spots were already used
            maze[pos.y][pos.x].used = true;
            //keeps track of the position of that path for the printing path part
            maze[pos.y][pos.x].position = pos;
           //pushes in the position into the queue
            mazePathsQueue.push(pos);
            //keeps track of the path by pointing back to the previous item
            maze[pos.y][pos.x].prev = &maze[pos.y][pos.x - 1];

            pos.x--; //decrements it back so it can look at all the other possible directions from that one place
        }//south
        if ((pos.y + 1) < maze.numrows() && maze[pos.y+1][pos.x].mazeCharacter != '#' && !maze[pos.y+1][pos.x].used){
            pos.y++; //moves position
            //keeps track of which spots were already used
            maze[pos.y][pos.x].used = true;
            //keeps track of the position of that path for the printing path part
            maze[pos.y][pos.x].position = pos;
           //pushes in the position into the queue
            mazePathsQueue.push(pos);
            //keeps track of the path by pointing back to the previous item
            maze[pos.y][pos.x].prev = &maze[pos.y - 1][pos.x];

            pos.y--;//decrements it back so it can look at all the other possible directions from that one place
        }//west
        if ((pos.x - 1) >= 0 && maze[pos.y][pos.x-1].mazeCharacter != '#' && !maze[pos.y][pos.x-1].used){
            pos.x--; //moves position
            //keeps track of which spots were already used
            maze[pos.y][pos.x].used = true;
            //keeps track of the position of that path for the printing path part
            maze[pos.y][pos.x].position = pos;
           //pushes in the position into the queue
            mazePathsQueue.push(pos);
            //keeps track of the path by pointing back to the previous item
            maze[pos.y][pos.x].prev = &maze[pos.y][pos.x + 1];

            pos.x++;//increments it back so it can look at all the other possible directions from that one place
        }
        //keeps recalling the algorithm until it reaches the goal or there are no more items in the queue
        //which means that all paths have been searched and no goal is found
        if (bfsAlgorithm(maze, mazePathsQueue, pos)){
            return true;
        }
   }//return false meaning no goal was found
    return false;
}

void printNotPath(apmatrix<Characteristics> &maze){
    //used for printing to console
    COORD Coord;
    DWORD count;

    //prints the parts that aren't the real path x's
    for (int i = 0; i < maze.numrows(); i++){
        for (int j = 0; j < maze.numcols(); j++){
            if (maze[i][j].mazeCharacter == '*' || maze[i][j].mazeCharacter == '.'){

                maze[i][j].mazeCharacter = 'x';

                Coord = {j, i};
                FillConsoleOutputCharacter(hStdOut, 'x', 1, Coord, &count);
                FillConsoleOutputAttribute(hStdOut, FOREGROUND_RED, 1, Coord, &count);
                Sleep(1);
            }
        }
    }

}

void printCorrectPath(apmatrix<Characteristics> &maze, PathCoords pos){
    //for printing to console
    COORD coord;
    DWORD count;
    //points are pinter to the last maze position it was in
    //most likely that would be goal
    //if goal could not be found, it will be the start position
    Characteristics* currentPathItem = &maze[pos.y][pos.x];

    //run if there is at least 1 item in the path
    while (currentPathItem){
            //only change the *'s to + to better show where the start and goal are
        if (currentPathItem->mazeCharacter != 'G' && currentPathItem->mazeCharacter != 'S'){
            //change it to + to show the desired path
            currentPathItem->mazeCharacter = '+';
            //prints out each item of the path in green
            coord = {currentPathItem->position.x, currentPathItem->position.y};
            FillConsoleOutputCharacter(hStdOut, '+', 1, coord, &count);
            FillConsoleOutputAttribute(hStdOut, FOREGROUND_GREEN, 1, coord, &count);
            Sleep(50); //delays
        }
        currentPathItem = currentPathItem->prev; //once it is done print out the path, currentPathItem->prev will be nullptr
    }
}



