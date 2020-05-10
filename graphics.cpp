#include "graphics.hpp"
#include <iostream>

using namespace std;

// Inicjalizacja
Graphics::Graphics(GLFWwindow* window) {
    this->window = window;

    glClearColor(1, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &vba);
	glBindVertexArray(vba);
	glGenBuffers(1, &vb);
}

// Zwolnienie zasobow
Graphics::~Graphics() {

}


void Graphics::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(window);
}
