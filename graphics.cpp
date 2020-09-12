#include "graphics.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace glm;

// Inicjalizacja
Graphics::Graphics(GLFWwindow* window, Game* game) {
    this->window = window;
    this->game = game;

    glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &vba);
	glBindVertexArray(vba);

	sp = new ShaderProgram("shader/v_simplest.glsl", NULL, "shader/f_simplest.glsl");

    d = new Drawable("./objects/cube.obj");

    apple = new Drawable("./objects/message_low.obj");

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

    glm::mat4 P=glm::perspective(50.0f*PI/180.0f, 1.0f, 0.01f, 30.0f); //Wylicz macierz rzutowania
    glm::mat4 M=glm::mat4(1.0f);
    
    M = scale(M, vec3(0.3f, 0.3f, 0.3f));
    mat4 baseM = scale(mat4(1.0f), vec3(0.3f, 0.3f, 0.3f));

    M = translate(M, vec3(1.0, 0.0, 0.0));

    sp->use();
    glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));
    //glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));


    int max_x = game->getGameTableWidth();
    int max_y = game->getGameTableHeight(); 
    int** gameTable = game->getGameTablePtr();
    for(int y=0; y < max_y; y++)
    {
        for(int x=0; x < max_x; x++)
        {
   
            // snake head
            if (gameTable[y][x] == game->getSnakeLength())
            {
                M = translate(baseM, vec3( -x *3.0, 0.0, y * 3.0 - 20));
                M = rotate(M, game->getHeadDir()*3.14f/2.0f, vec3(0.0f, 1.0f, 0.0f));
                M = scale(M, vec3(2.0f, 1.0f, 1.0f));
                glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
                d->draw(sp);
            }

            // snake tail
            if (gameTable[y][x] == 1)
            {
                M = translate(baseM, vec3( -x *3.0, 0.0, y * 3.0 - 20));
                M = rotate(M, game->getTailDir()*3.14f/2.0f, vec3(0.0f, 1.0f, 0.0f));
                M = scale(M, vec3(2.0f, 1.0f, 1.0f));
                glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
                d->draw(sp);
            }

            // apple
            if (gameTable[y][x] == -1)
            {
                M = translate(baseM, vec3( -x *3.0, 0.0, y * 3.0 - 20));
                M = rotate(M, 3.14f/2.0f, vec3(1.0f, 0.0f, 0.0f));
                M = scale(M, vec3(0.07f, 0.25f, 0.07f));
                glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
                apple->draw(sp);
            }

            // body
            if (gameTable[y][x] > 1)
            {
                if (game->getBendBodyDir(y, x) >=0)
                {
                    // parts which bends
                    M = translate(baseM, vec3( -x *3.0, 0.0, y * 3.0 - 20));
                    M = scale(M, vec3(1.0f, 1.0f, 2.3f));
                    M = rotate(M, 3.14f/4.0f + 3.14f/2.0f*game->getBendBodyDir(y, x), vec3(0.0f, 1.0f, 0.0f));
                    // nie jestem pewien, czy w dobra strone sie to obraca, zobaczy sie po wgraniu modelu co nie wyglada jak prostokat xd
                    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
                    d->draw(sp);
                }
                else
                {
                    // straight parts
                    M = translate(baseM, vec3( -x *3.0, 0.0, y * 3.0 - 20));
                    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
                    d->draw(sp);
                }
            }
        }
    }
        
   
    glfwSwapBuffers(window);
}

