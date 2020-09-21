#include <iostream>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.hpp"
#include "graphics.hpp"

using namespace std;

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
        case GLFW_KEY_A:
            graphics->cam = glm::vec3(graphics->cam.x - 1, graphics->cam.y, graphics->cam.z);
            break;
        case GLFW_KEY_D:
            graphics->cam = glm::vec3(graphics->cam.x + 1, graphics->cam.y, graphics->cam.z);
            break;
        case GLFW_KEY_W:
            graphics->cam = glm::vec3(graphics->cam.x, graphics->cam.y - 1, graphics->cam.z);
            break;
        case GLFW_KEY_S:
            graphics->cam = glm::vec3(graphics->cam.x, graphics->cam.y + 1, graphics->cam.z);
            break;
        case GLFW_KEY_Q:
            graphics->cam = glm::vec3(graphics->cam.x, graphics->cam.y, graphics->cam.z - 1);
            break;
        case GLFW_KEY_E:
            graphics->cam = glm::vec3(graphics->cam.x, graphics->cam.y, graphics->cam.z + 1);
            break;
        case GLFW_KEY_H:
            graphics->eye = glm::vec3(graphics->eye.x - 1, graphics->eye.y, graphics->eye.z);
            break;
        case GLFW_KEY_K:
            graphics->eye = glm::vec3(graphics->eye.x + 1, graphics->eye.y, graphics->eye.z);
            break;
        case GLFW_KEY_U:
            graphics->eye = glm::vec3(graphics->eye.x, graphics->eye.y - 1, graphics->eye.z);
            break;
        case GLFW_KEY_J:
            graphics->eye = glm::vec3(graphics->eye.x, graphics->eye.y + 1, graphics->eye.z);
            break;
        case GLFW_KEY_Y:
            graphics->eye = glm::vec3(graphics->eye.x, graphics->eye.y, graphics->eye.z - 1);
            break;
        case GLFW_KEY_I:
            graphics->eye = glm::vec3(graphics->eye.x, graphics->eye.y, graphics->eye.z + 1);
            break;
        case GLFW_KEY_P:
            printf("CAM: %f, %f, %f\n", graphics->cam.x, graphics->cam.y, graphics->cam.z);
            printf("EYE: %f, %f, %f\n", graphics->eye.x, graphics->eye.y, graphics->eye.z);
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
    graphics->aspectRatio = (float)width / (float)height;
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glewExperimental = true;

	window = glfwCreateWindow(800, 800, "Snake 3D", NULL, NULL);

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


    
    game = new Game(10, 10);
    graphics = new Graphics(window, game);

    game->showGameTable();
    game->initSnake();

    int frames = 0;
    double previousTime = 0;
    double timeDelta;

    glfwSetTime(0);
    while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
        timeDelta = glfwGetTime() - previousTime;
        if(glfwGetTime() >= 0.5) {
            if(!game->isGameOver() && !game->isGameWon()) {
                game->forward();
                game->showGameTable();
            }
            glfwSetTime(0);
            printf("FPS: %i\n", frames);
            frames = 0;
        }
        frames++;
        previousTime = glfwGetTime();
        graphics->draw(timeDelta);
		glfwPollEvents();
	}

    delete graphics;
    delete game;

    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);

    return 0;
}