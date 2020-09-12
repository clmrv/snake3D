#include "graphics.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace glm;

// Inicjalizacja
Graphics::Graphics(GLFWwindow* window) {
    this->window = window;

    glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &vba);
	glBindVertexArray(vba);

	sp = new ShaderProgram("shader/v_simplest.glsl", NULL, "shader/f_simplest.glsl");

    d = new Drawable("./objects/message_low.obj");

}

// Zwolnienie zasobow
Graphics::~Graphics() {

    delete sp;

}

void Graphics::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 V=glm::lookAt(
        glm::vec3(-10, 9, -20),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 1.0)); //Wylicz macierz widoku


    // X - lewo (-)   <=> prawo (+)
    // Y - góra (+)   <=> dół (-)
    // Z - bliżej (+) <=> dalej (-)

    glm::mat4 P=glm::perspective(50.0f*PI/180.0f, 1.0f, 0.01f, 50.0f); //Wylicz macierz rzutowania

    glm::mat4 M=glm::mat4(1.0f);
    
    M = scale(M, vec3(0.3f, 0.3f, 0.3f));
    mat4 baseM = scale(mat4(1.0f), vec3(0.3f, 0.3f, 0.3f));

    M = translate(M, vec3(1.0, 0.0, 0.0));

    sp->use();
    glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));

    d->draw(sp);

    M = translate(baseM, vec3(40.0, 0.0, 0.0));
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    d->draw(sp);

    M = translate(baseM, vec3(-40.0, 0.0, 0.0));
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    d->draw(sp);

    M = translate(baseM, vec3(0.0, 0.0, 40.0));
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    d->draw(sp);

    M = translate(baseM, vec3(0.0, 0.0, -40.0));
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    d->draw(sp);

    glfwSwapBuffers(window);
}

