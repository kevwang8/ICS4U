/*****************************************************************************
 *	Name:   Kevin Wang
 *	File:   maze.cpp
 *	Course: ICS4U
 *	Date:   May 11, 2018
 *
 *	Purpose: Scans in a maze with a start and a goal and it moves along the maze
 *           until it finds the goal or looks everywhere and there is no goal
 *
 *	Usage: Enter in a valid maze file with the dimensions at the top. Then watch the
 *         maze search itself
 *
 *	Revision History: N/A
 *
 *	Known Issues: Start has to only have one path out from it. Eg. can't have open
 *                paths on both side of start. Probably easy to fix but no more time and
 *                honestly not that important
 *****************************************************************************/
#include <iostream>
#include <fstream>
#include <apmatrix.h>
#include <queue>
#include <windows.h>

using namespace std;
//this code including all the rest of its kind was inspired from a post in dreamincode.net
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//used in printing in colour and printing at a specific place

void fileLoad(int dimension[], apmatrix<char> &maze); //loads in the maze from a file
void findStart(apmatrix<char> &maze, int &x, int &y); //finds the position if the start of the maze
bool findPath(apmatrix<char> &maze, int &x_pos, int &y_pos); //recursive algorithm that finds the path to the goal if there is one


int main(){

    int start_x = -1; //x position of start
    int start_y = -1; //y position of start
    int dimension[2] = {0}; //dimensions of the maze
    apmatrix<char> maze(20, 20); //holds the contents of the maze

    fileLoad(dimension, maze); //loads file

    findStart(maze, start_x, start_y); //finds start

    int positionX = start_x; //declares the actual position the path
    int positionY = start_y;

    //if goal is found, it returns true
    if (findPath(maze, positionX, positionY)){
        cout << endl << "Goal Found!" << endl;

        //for printing to console
        COORD coord;
        DWORD count;

        //changes all the unused open paths to X and updates it to the console
        for (int i = 0; i < maze.numrows(); i++){
            for (int j = 0; j < maze.numcols(); j++){
                if (maze[i][j] == '.'){
                    coord = {j, i};
                    maze[i][j] = 'x';
                    FillConsoleOutputCharacter(hStdOut, maze[i][j], 1, coord, &count);
                    FillConsoleOutputAttribute(hStdOut, FOREGROUND_RED, 1, coord, &count);
                    Sleep(5);
                }
            }
        }
    }
    else
        cout << endl << "No Path Found!" << endl;


    return 0;
}

void fileLoad(int dimension[], apmatrix<char> &maze){

    char fileName[50];
    cout << "Enter your maze file" << endl;
    cin >> fileName;

    system("CLS");

    ifstream loadFile;
    loadFile.open(fileName);

    if (!loadFile)   //checks if file was found and displays error message if not
        cout << "File not found" << endl;
    //scans in the mazes dimensions
    for (int i = 0; i < 2; i++)
        loadFile >> dimension[i];
    //resizes the maze with the right dimensions
    maze.resize(dimension[0], dimension[1]);

    //scans in the maze and prints it to the screen
    for (int i = 0; i < dimension[0]; i++){
        for (int j = 0; j < dimension[1]; j++){
            loadFile >> maze[i][j];
            cout << maze[i][j];
        }
        cout << endl;
    }

    loadFile.close();
}

void findStart(apmatrix<char> &maze, int &x, int &y){
    //goes through the maze and finds the start position
    for (int i = 0; i < maze.numrows(); i++){
        for (int j = 0; j < maze.numcols(); j++){
            if(maze[i][j] == 'S'){
                y = i;
                x = j;
                break;
            }
        }
    }
}

bool findPath(apmatrix<char> &maze, int &x_pos, int &y_pos){

    COORD coord;
    DWORD count;

    //checks if the position is on the goal
    if (maze[y_pos][x_pos] == 'G'){
                return true;
    }

    //checks north
    if ((y_pos - 1) >= 0 && (maze[y_pos - 1][x_pos] == '.' || maze[y_pos - 1][x_pos] == 'G')){
            //moves the position
            y_pos -= 1;
            coord = {x_pos, y_pos}; //for printing

            //checks for goal
            if (maze[y_pos][x_pos] == 'G'){
                return true;
            }
            maze[y_pos][x_pos] = '+'; //changes character to +
            //prints the 1 path
            FillConsoleOutputCharacter(hStdOut, maze[y_pos][x_pos], 1, coord, &count);
            FillConsoleOutputAttribute(hStdOut, FOREGROUND_GREEN, 1, coord, &count);
            Sleep(75);

            //recursively calls the function again and if it returns false, backtrack
            if (!findPath(maze, x_pos, y_pos)){
                maze[y_pos][x_pos] = 'x';
                FillConsoleOutputCharacter(hStdOut, maze[y_pos][x_pos], 1, coord, &count);
                FillConsoleOutputAttribute(hStdOut, FOREGROUND_RED, 1, coord, &count);
                Sleep(10);
                y_pos++; //move position back
            }
    }//checks east
    else if ((x_pos + 1) < maze.numcols() && (maze[y_pos][x_pos + 1] == '.' || maze[y_pos][x_pos + 1] == 'G')){
            //moves the position
            x_pos += 1;
            coord = {x_pos, y_pos};//for printing
            //checks for goal
            if (maze[y_pos][x_pos] == 'G'){
                return true;
            }
            maze[y_pos][x_pos] = '+'; //changes character to +

            //prints the 1 path
            FillConsoleOutputCharacter(hStdOut, maze[y_pos][x_pos], 1, coord, &count);
            FillConsoleOutputAttribute(hStdOut, FOREGROUND_GREEN, 1, coord, &count);
            Sleep(75);
            //recursively calls the function again and if it returns false, backtrack
            if (!findPath(maze, x_pos, y_pos)){
                maze[y_pos][x_pos] = 'x';
                FillConsoleOutputCharacter(hStdOut, maze[y_pos][x_pos], 1, coord, &count);
                FillConsoleOutputAttribute(hStdOut, FOREGROUND_RED, 1, coord, &count);
                Sleep(10);
                x_pos--; //move position back
            }
    }//checks south
    else if ((y_pos + 1) < maze.numrows() && (maze[y_pos + 1][x_pos] == '.' || maze[y_pos + 1][x_pos] == 'G')){
            //moves the position
            y_pos += 1;
            coord = {x_pos, y_pos};//for printing
            //checks for goal
            if (maze[y_pos][x_pos] == 'G'){
                return true;
            }
            maze[y_pos][x_pos] = '+';//changes character to +
            //prints the 1 path
            FillConsoleOutputCharacter(hStdOut, maze[y_pos][x_pos], 1, coord, &count);
            FillConsoleOutputAttribute(hStdOut, FOREGROUND_GREEN, 1, coord, &count);
            Sleep(75);

            if (!findPath(maze, x_pos, y_pos)){
                maze[y_pos][x_pos] = 'x';
                FillConsoleOutputCharacter(hStdOut, maze[y_pos][x_pos], 1, coord, &count);
                FillConsoleOutputAttribute(hStdOut, FOREGROUND_RED, 1, coord, &count);
                Sleep(10);
                y_pos--;//move position back
            }
    }//checks west
    else if ((x_pos - 1) >= 0 && (maze[y_pos][x_pos - 1] == '.' || maze[y_pos][x_pos - 1] == 'G')){
            //moves the position
            x_pos = x_pos - 1;
            coord = {x_pos, y_pos};//for printing
            //checks for goal
            if (maze[y_pos][x_pos] == 'G'){
                return true;
            }
            maze[y_pos][x_pos] = '+';//changes character to +
            //prints the 1 path
            FillConsoleOutputCharacter(hStdOut, maze[y_pos][x_pos], 1, coord, &count);
            FillConsoleOutputAttribute(hStdOut, FOREGROUND_GREEN, 1, coord, &count);
            Sleep(75);

            //recursively calls the function again and if it returns false, backtrack
            if (!findPath(maze, x_pos, y_pos)){
                maze[y_pos][x_pos] = 'x';
                FillConsoleOutputCharacter(hStdOut, maze[y_pos][x_pos], 1, coord, &count);
                FillConsoleOutputAttribute(hStdOut, FOREGROUND_RED, 1, coord, &count);
                Sleep(10);
                x_pos++;//move position back
            }
    }
    else{ //if there is no direction to go
      return false;
    }
    //returns false if the position is back at the start which means there are no paths to the goal
    if (maze[y_pos][x_pos] == 'S')
        return false;
    //calls the function again
    findPath(maze, x_pos, y_pos);
}




