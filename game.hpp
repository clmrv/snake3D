#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <iostream> //DEBUG
#include <cstdlib>  //rand
#include <time.h>   //rand


#define START_LENGTH 3

enum class Direction { north, east, south, west };


struct Point
{
    int x;
    int y;
};

class Game {
public:
    Game(int sizeY, int sizeX);
    ~Game();

    void initSnake();

    void turnLeft();
    void turnRight();
    void forward();
    
    bool isGameOver();
    int** getGameTablePtr();   // info for drawing
    int getGameTableWidth();
    int getGameTableHeight();
    int getSnakeLength();
    int getHeadDir();
    int getTailDir();
    int getBendBodyDir(int y, int x);
    
    void showGameTable();           // debug
    void setApple(int y, int x);    // debug

    Direction userDir;

private:
    Point gameTableSize;
    int** gameTable;

    int snakeLength;
    Point snakePos;
    Direction snakeDir;
    bool gameOver;
 
    bool checkBorderGameOver();
    void setApple();
};


#endif