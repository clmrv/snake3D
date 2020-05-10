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
    snakeDir = Direction::north;
    userDir = Direction::north;

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

    // Get user movement
    switch(snakeDir) {
    case Direction::north:
    case Direction::south:
        if(userDir == Direction::west || userDir == Direction::east) snakeDir = userDir;
        break;
    case Direction::east:
    case Direction::west:
        if(userDir == Direction::north || userDir == Direction::south) snakeDir = userDir;
        break;
    default:
        break;
    }

    // Move snake
    switch(snakeDir) {
    case Direction::north:
        snakePos.y++;
        break;

    case Direction::east:
        snakePos.x++;
        break;

    case Direction::south:
        snakePos.y--;   
        break;

    case Direction::west:
        snakePos.x--;
        break;
    default:
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
            if(gameTable[y][x] < 0)
                std::cout << "x ";
            else
                std::cout << gameTable[y][x] << " ";
        std::cout << std::endl;
    }
}

void Game::setApple(int y, int x) {
    gameTable[y][x] = -1; 
}