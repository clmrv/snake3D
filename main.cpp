#include <iostream>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.hpp"
#include "graphics.hpp"

using namespace std;

float aspectRatio = 1;

Game* game;
Graphics* graphics;


// Obsługa bledow
void error_callback(int error, const char* description) {
    cout << "Error: " << description << endl;
}


// Obsługa klawiszy
void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {
    if (action == GLFW_PRESS) {
        switch(key) {
        case GLFW_KEY_LEFT:
            game->userDir = Direction::west;
            break;
        case GLFW_KEY_RIGHT:
            game->userDir = Direction::east;
            break;
        case GLFW_KEY_UP:
            game->userDir = Direction::north;
            break;
        case GLFW_KEY_DOWN:
            game->userDir = Direction::south;
            break;
        default:
            break;
        }
    } else if (action==GLFW_RELEASE) {
        
    }
}

// Zmiana rozmiaru okna
void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    aspectRatio = (float)width / (float)height;
    glViewport(0, 0, width, height);
}


int main() {
    srand(time(NULL));

    // Okno
    GLFWwindow* window;

    // Obsługa błedow
	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

    // Inicjalizacja GLFW
	if (!glfwInit()) {
        cout << "Nie udalo sie zainicjowac GLFW\n";
		exit(EXIT_FAILURE);
	}

	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glewExperimental = true;
	*/

	window = glfwCreateWindow(500, 500, "Snake 3D", NULL, NULL);

    // Jesli nie mozna stworzyc okna
    if (!window) {
        cout << "Nie mozna utworzyc okna";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

    glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

    glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, keyCallback);

    // Inicjalizacja GLEW
	if (glewInit() != GLEW_OK) {
		cout << "Nie udalo sie zainicjować GLEW.\n";
		exit(EXIT_FAILURE);
	}


    graphics = new Graphics(window);
    game = new Game(10, 10);

    game->showGameTable();
    game->initSnake();

    glfwSetTime(0);
    while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
        if(glfwGetTime() >= 1) {
            if(!game->isGameOver()) {
                game->forward();
                game->showGameTable();
            }
            glfwSetTime(0);
        }
        graphics->draw();
		glfwPollEvents();
	}

    delete graphics;
    delete game;

    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);

    return 0;
}
