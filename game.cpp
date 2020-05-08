#include "game.hpp"

Game::Game(int sizeY, int sizeX) {
    gameTableSize.x = sizeX;
    gameTableSize.y = sizeY;

    gameTable = new int*[sizeY];
    for (int y=0; y<sizeY; y++) {
        gameTable[y] = new int[sizeX];
        for (int x=0; x<sizeY; x++)
            gameTable[y][x] = 0;
    }

    gameOver = false;
}

Game::~Game() {
    for (int y=0; y<gameTableSize.y; y++)
        delete[] gameTable[y];

    delete[] gameTable;
}

void Game::initSnake() {
    snakeLength = START_LENGTH;
    snakeDir = SNAKE_NORTH;

    snakePos.y = gameTableSize.y/2 + snakeLength/2 - 1;
    snakePos.x = gameTableSize.x/2;

    int tmpY = snakePos.y;
    for (int i=snakeLength; i>0; i--) {
        gameTable[tmpY][snakePos.x] = i;
        tmpY--;
    }

    setApple();
}

void Game::setApple() {
    Point tmp;
    do {
        tmp.y = rand()%gameTableSize.y;
        tmp.x = rand()%gameTableSize.x;
    } while (gameTable[tmp.y][tmp.x] > 0);
    gameTable[tmp.y][tmp.x] = -1;
}

void Game::turnLeft() {
    snakeDir--;
    if (snakeDir < SNAKE_NORTH)
        snakeDir = SNAKE_WEST;

}

void Game::turnRight() {
    snakeDir++;
    if (snakeDir > SNAKE_WEST)
        snakeDir = SNAKE_NORTH;
}

bool Game::checkBorderGameOver() {
    if (snakePos.y >= gameTableSize.y) 
        gameOver = true;

    if (snakePos.y < 0)
        gameOver = true;

    if (snakePos.x >= gameTableSize.x)
        gameOver = true;

    if (snakePos.x < 0)
        gameOver = true;

    return gameOver;
}

void Game::forward() {
    bool haveEaten = false;

    // Move snake
    switch(snakeDir) {
        case SNAKE_NORTH:
            snakePos.y++;
            break;

        case SNAKE_EAST:
            snakePos.x++;
            break;

        case SNAKE_SOUTH:
            snakePos.y--;   
            break;

        case SNAKE_WEST:
            snakePos.x--;
            break;
    }

    if (checkBorderGameOver())
        return;

    //Check if stepped on a tile with apple
    if (gameTable[snakePos.y][snakePos.x] == -1) {
        snakeLength++;    
        // update whole snake
        for (int y=0; y<gameTableSize.y; y++)
            for (int x=0; x<gameTableSize.x; x++)
                if (gameTable[y][x] > 0)
                    gameTable[y][x]++;
        haveEaten = true;
    }

    //Update map (remove tail)
    for (int y=0; y<gameTableSize.y; y++)
        for (int x=0; x<gameTableSize.x; x++)
            if (gameTable[y][x] > 0)
                gameTable[y][x]--;

    // Check if stepped on a tile with snake
    if (gameTable[snakePos.y][snakePos.x] > 0)
        gameOver = true;

    // set new tile (move head)
    gameTable[snakePos.y][snakePos.x] = snakeLength;

    // new apple
    if (haveEaten)
        setApple();
}

bool Game::isGameOver() {
    return gameOver;
}

int** Game::getGameTablePtr() {
    return gameTable;
}

void Game::showGameTable() {
    for (int i=0; i<2; i++)
        std::cout << std::endl;

    for (int y=gameTableSize.y-1; y>=0; y--) {
        for (int x=0; x<gameTableSize.x; x++)
            std::cout << gameTable[y][x] << " ";
        std::cout << std::endl;
    }
}

void Game::setApple(int y, int x) {
    gameTable[y][x] = -1; 
}