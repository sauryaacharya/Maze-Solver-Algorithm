#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_stack.h"

#define ROWSIZE 12
#define COLSIZE 12
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define DIRECTIONS 4

void solveMaze(Location l, char board[][COLSIZE]);

void findPath(Location l, char board[][COLSIZE]);

void lookUp(Location l, char board[][COLSIZE]);

void printMaze(char board[][COLSIZE]);

dynamic_stack* visitedLocation;

int main()
{
    //create a mazeboard 1
    char mazeBoard[ROWSIZE][COLSIZE] = {{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                                        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                                        {' ', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#'},
                                        {'#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
                                        {'#', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', '#', ' ', ' '},
                                        {'#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
                                        {'#', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
                                        {'#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
                                        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
                                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
                                        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
                                       };

//create a mazeboard 2
    char mazeBoard2[ROWSIZE][COLSIZE] = {{'#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#'},
                                         {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                                         {'#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#'},
                                         {'#', '#', '#', '#', '#', '#', ' ', ' ', ' ', '#', ' ', '#'},
                                         {'#', ' ', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
                                         {'#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
                                         {'#', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
                                         {'#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
                                         {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
                                         {'#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
                                         {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                                         {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
                                        };


    printf("Maze Board 1\n\n");

    //initialize the starting point of the maze
    Location initLocation = {5, 6, ' '};

    //create a stack to store visited location
    visitedLocation = create_stack();

    //solve the maze recursively and find the path
    solveMaze(initLocation, mazeBoard);

    printf("Solution path in stack: \n");

    //print the solution path that is in stack
    print_stack(visitedLocation);

    delete_stack(visitedLocation);

    printf("\n");

    printf("Maze Board 2\n\n");

    Location initLocation1 = {6, 1, ' '};

    visitedLocation = create_stack();

    solveMaze(initLocation1, mazeBoard2);

    printf("Solution path in stack: \n");

    print_stack(visitedLocation);

    return 0;
}

//move up from the current location
int moveUp(Location l)
{
    return l.row - 1;
}

//move down from the current location
int moveDown(Location l)
{
    return l.row + 1;
}

//move left from the current location
int moveLeft(Location l)
{
    return l.column - 1;
}

//move right from the current location
int moveRight(Location l)
{
    return l.column + 1;
}

//check whether the given location is an exit or not
int isExit(Location l)
{
    return (l.row == 0 || l.column == 0 || l.row == 11 || l.column == 11);
}

//lookup on the four sides from the current location in a maze
//Step (c)
void lookUp(Location l, char board[][COLSIZE])
{
    //flag to find if there is any way or not
    int hasWay = 0;

    //loop through each direction and check the path the robot can move
    for(int i = 1; i <= DIRECTIONS; i++)
    {
        int x = l.row;
        int y = l.column;

        switch(i)
        {
        case UP:
            x = moveUp(l);
            break;

        case DOWN:
            x = moveDown(l);
            break;

        case LEFT:
            y = moveLeft(l);
            break;

        case RIGHT:
            y = moveRight(l);
            break;

        default:
            break;

        }

        // check for the path to move
        if(board[x][y] == ' ')
        {
            hasWay = 1;
            Location nextLoc = {x, y, ' '};
            //push the visited location in a stack
            push(visitedLocation, nextLoc);
            //again find the path from the next location
            //Step (b)
            findPath(nextLoc, board);
            break;
        }
    }

    //check the condition if there is no any way to get out from the maze
    if(!hasWay)
    {
        //reach up to the dead end and mark it as 'd'
        visitedLocation->top->loc.symbol = 'd';
        //pop the dead end location and do the back tracking
        Location loc = pop(visitedLocation);
        board[loc.row][loc.column] = 'd';

        if(isEmpty(visitedLocation))
        {
            //if the stack is empty, exit and print if there is no solution found.
            //Step (d)
            printf("%s\n", "There is no solution.");
        }
        else
        {
            //recursively do the back tracking from dead end
            //Step (c)
            lookUp(visitedLocation->top->loc, board);
        }
    }
}

void solveMaze(Location l, char board[][COLSIZE])
{
    //push the initial starting location to the stack
    //Step (a)
    push(visitedLocation, l);
    //Step (b)
    findPath(l, board);
}


//Step (b)
void findPath(Location l, char board[][COLSIZE])
{
    int row = visitedLocation->top->loc.row;
    int col = visitedLocation->top->loc.column;

    //if the starting location has white space
    if(visitedLocation->top->loc.symbol == ' ')
    {
        //overrdide the board with 'X'
        visitedLocation->top->loc.symbol = 'X';
        board[row][col] = 'X';
        if(isExit(l))
        {
            //if the exit found print the maze with solution
            //Step (e)
            printMaze(board);
        }
        else
        {
            //if the exit is not found go and look up in every directions
            //Step(c)
            lookUp(l, board);
        }
    }
}


//print the maze
void printMaze(char board[][COLSIZE])
{
    for(int i = 0; i < ROWSIZE; i++)
    {
        for(int j = 0; j < COLSIZE; j++)
        {
            if(board[i][j] == 'd')
                board[i][j] = ' ';

            printf("%c%s", board[i][j], " ");
        }
        printf("%s", "\n");
    }
}

