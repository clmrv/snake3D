#include "graphics.hpp"
#include <iostream>

#include "myCube.h"

using namespace std;

// Inicjalizacja
Graphics::Graphics(GLFWwindow* window) {
    this->window = window;

    glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &vba);
	glBindVertexArray(vba);
	glGenBuffers(1, &vb);


    sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");
}

// Zwolnienie zasobow
Graphics::~Graphics() {

    delete sp;
}


void Graphics::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Wylicz macierz widoku
    glm::mat4 V=glm::lookAt(
         glm::vec3(0, 0, -5.0),
         glm::vec3(0,0,0),
         glm::vec3(0.0f,1.0f,0.0f)); 

    // Wylicz macierz rzutowania
    glm::mat4 P=glm::perspective(50.0f*PI/180.0f, 1.0f, 0.01f, 50.0f); //drugi to aspect ratio

    sp->use();
    //Przeslij parametry programu cieniującego do karty graficznej
    glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));


    glm::mat4 M=glm::mat4(1.0f);
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));

    glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
    glVertexAttribPointer(sp->a("vertex"),4,GL_FLOAT,false,0,myCubeVertices); //Wskaż tablicę z danymi dla atrybutu vertex
	
    glEnableVertexAttribArray(sp->a("color"));
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, myCubeColors);

    glDrawArrays(GL_TRIANGLES,0, myCubeVertexCount); //Narysuj obiekt

    //Wyłącz przesyłanie danych do atrybutu vertex
    glDisableVertexAttribArray(sp->a("vertex"));  
	glDisableVertexAttribArray(sp->a("color"));


    glfwSwapBuffers(window);
}
