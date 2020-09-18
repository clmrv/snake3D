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
    d->loadTexture("./objects/cube.png");

    apple = new Drawable("./objects/apple_red.obj");
    apple->loadTexture("./objects/apple_red.png");

    grass = new Drawable("./objects/grass.obj");
    grass->loadTexture("./objects/grass.png");

    dirt = new Drawable("./objects/dirt.obj");
    dirt->loadTexture("./objects/dirt.png");

    head = new Drawable("./objects/head.obj");

    body = new Drawable("./objects/cylinder.obj");

    bendbody = new Drawable("./objects/bend.obj");

    tail = new Drawable("./objects/tail.obj");


}

// Zwolnienie zasobow
Graphics::~Graphics() {

    delete sp;

}

void Graphics::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glm::mat4 V=glm::lookAt(
    //     glm::vec3(-13.5, 40, -6),
    //     glm::vec3(-13.5, 0.0, -6),
    //     glm::vec3(0.0, 1.0, 1.0)); //Wylicz macierz widoku

    // glm::mat4 V=glm::lookAt(
    //     glm::vec3(-13.5, 40, -6),
    //     cam,
    //     glm::vec3(0.0, 1.0, 1.0)); //Wylicz macierz widoku

    glm::mat4 V=glm::lookAt(
        glm::vec3(-25, 34, -25),
        cam,
        glm::vec3(0.0, 1.0, 1.0)); //Wylicz macierz widoku

    // X - lewo (-)   <=> prawo (+)
    // Y - góra (+)   <=> dół (-)
    // Z - bliżej (+) <=> dalej (-)

    glm::mat4 P=glm::perspective(50.0f*PI/180.0f, 1.0f, 0.01f, 90.0f); //Wylicz macierz rzutowania
    glm::mat4 M=glm::mat4(1.0f);
    
    mat4 baseM = mat4(1.0f);

    sp->use();
    glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));
    //glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));

    // Dirt
    M = translate(baseM, vec3(-5, -0.11f, -5));
    M = scale(M, vec3(30.0f, 1.0f, 30.0f));
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    dirt->draw(sp);



    int max_x = game->getGameTableWidth();
    int max_y = game->getGameTableHeight(); 
    int** gameTable = game->getGameTablePtr();
    for(int y=0; y < max_y; y++)
    {
        for(int x=0; x < max_x; x++)
        {
            // WARNING continue; in head


            // grass field
            {
                M = translate(baseM, vec3( -x *3.0, -0.1f, y * 3.0 - 20));
                M = scale(M, vec3(0.009f, 0.009f, 0.009f));
                M = rotate(M, -PI/2.0f, vec3(1.0f, 0, 0));
                glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
                grass->draw(sp);
            }

            

            // snake tail
            if (gameTable[y][x] == 1)
            {
                M = translate(baseM, vec3( -x *3.0, 1.0, y * 3.0 - 20));
                M = rotate(M, -PI/2.0f * game->getBodyDir(y,x), vec3(0.0f, 1.0f, 0.0f));
                M = scale(M, vec3(1.0f, 1.0f, 1.5f));
                M = rotate(M, -PI/2.0f, vec3(1.0f, 0.0f, 0.0f));
                glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
                tail->draw(sp);
            }

            // apple
            if (gameTable[y][x] == -1)
            {
                M = translate(baseM, vec3( -x *3.0, 0.0, y * 3.0 - 20));
                M = rotate(M, -PI/2.0f, vec3(1.0f, 0.0f, 0.0f));
                //M = scale(M, vec3(0.07f, 0.25f, 0.07f));
                M = scale(M, vec3(0.02f, 0.02f, 0.02f));
                glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
                apple->draw(sp);
            }

            // snake head
            if (gameTable[y][x] == game->getSnakeLength())
            {
                M = translate(baseM, vec3( -x *3.0, 0.0, y * 3.0 - 20));
                M = rotate(M, PI, vec3(1.0f, 0.0f, 0.0f));
                M = rotate(M, game->getHeadDir()*-PI/2.0f, vec3(0.0f, 1.0f, 0.0f));
                M = scale(M, vec3(0.5f, 0.5f, 0.5f));
                glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
                head->draw(sp);
                continue;
            }
            // body
            if (gameTable[y][x] > 1)
            {
                if (game->getBendBodyDir(y, x) >=0)
                {
                    // parts which bends
                    M = translate(baseM, vec3( -x *3.0, 3.0, y * 3.0 - 20));
                    M = rotate(M, -PI/2.0f * game->getBendBodyDir(y,x), vec3(0.0f, 1.0f, 0.0f));
                    M = scale(M, vec3(1.0f, 1.0f, 1.5f));
                    M = rotate(M, PI/2.0f, vec3(1.0f, 0.0f, 0.0f));
                    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
                    bendbody->draw(sp);
                }
                else
                {
                    // straight parts
                    M = translate(baseM, vec3( -x *3.0, 1.0, y * 3.0 - 20));
                    M = rotate(M, -PI/2.0f * game->getBodyDir(y,x), vec3(0.0f, 1.0f, 0.0f));
                    M = scale(M, vec3(1.0f, 1.0f, 1.5f));
                    M = rotate(M, PI/2.0f, vec3(1.0f, 0.0f, 0.0f));
                    
                    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
                    body->draw(sp);
                }
            }
        }
    }
        
    glfwSwapBuffers(window);
}
