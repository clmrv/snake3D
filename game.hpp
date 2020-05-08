#include <iostream> //DEBUG
#include <cstdlib>  //rand
#include <time.h>   //rand


#define START_LENGTH 3

#define SNAKE_NORTH 101
#define SNAKE_EAST 102
#define SNAKE_SOUTH 103
#define SNAKE_WEST 104




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
    
    void showGameTable();           // debug
    void setApple(int y, int x);    // debug


private:
    Point gameTableSize;
    int** gameTable;

    int snakeLength;
    Point snakePos;
    int snakeDir;
    bool gameOver;
 
    bool checkBorderGameOver();
    void setApple();
};
