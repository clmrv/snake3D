#include "game.hpp"

#include <unistd.h>

int main() {
    srand(time(NULL));
    Game test = Game(10, 10);
    test.showGameTable();
    sleep(1);
    test.initSnake();
    //test.setApple(8,5);
    test.showGameTable();
    for (int nr=0; !test.isGameOver(); nr++) {
        sleep(1);
        if (nr == 3 || nr == 5)
            test.turnRight();
        test.forward();
        test.showGameTable();
    }
    std::cout << "\n game over \n";
    return 0;
}