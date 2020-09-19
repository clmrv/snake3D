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

    apple = new Bounceable("./objects/apple_red.obj");
    apple->loadTexture("./objects/apple_red.png");

    stone = new Drawable("./objects/stones.obj");
    stone->loadTexture("./objects/stones.png");

    grass = new Drawable("./objects/grass.obj");
    grass->loadTexture("./objects/grass.png");

    plant1 = new Bounceable("./objects/plant.obj");
    plant1->loadTexture("./objects/plant1.png");
    plant2 = new Bounceable("./objects/plant.obj");
    plant2->loadTexture("./objects/plant2.png");

    head = new Drawable("./objects/head2.obj");
    head->loadTexture("./objects/cube.png");

    body = new Drawable("./objects/cylinder.obj");
    body->loadTexture("./objects/snake_skin.png");

    bendbody = new Drawable("./objects/bend2.obj");
    bendbody->loadTexture("./objects/snake_skin.png");

    tail = new Drawable("./objects/tail.obj");
    tail->loadTexture("./objects/snake_skin.png");


}

// Zwolnienie zasobow
Graphics::~Graphics() {

    delete sp;

}

void Graphics::draw(double timeSinceLastDraw) {
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
        eye,
        cam,
        glm::vec3(0.0, 1.0, 0.0)); //Wylicz macierz widoku

    // X - lewo (-)   <=> prawo (+)
    // Y - góra (+)   <=> dół (-)
    // Z - bliżej (+) <=> dalej (-)

    glm::mat4 P=glm::perspective(50.0f*PI/180.0f, aspectRatio, 0.01f, 90.0f); //Wylicz macierz rzutowania
    glm::mat4 M=glm::mat4(1.0f);
    
    mat4 baseM = mat4(1.0f);

    sp->use();
    glUniformMatrix4fv(sp->uP,1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->uV,1,false,glm::value_ptr(V));
    //glUniformMatrix4fv(sp->uM,1,false,glm::value_ptr(M));

    // Grass background
    M = translate(baseM, vec3(8, -0.11f, -16));
    M = scale(M, vec3(30.0f, 1.0f, 30.0f));
    glUniformMatrix4fv(sp->uM,1,false,glm::value_ptr(M));
    grass->draw(sp);

    // Plants
    plant1->updateBouncePosition(timeSinceLastDraw / 3.0);
    M = translate(baseM, vec3(-4.0f, -0.2f, -21.0f));
    M = scale(M, vec3(35.0f, 35.0f, 35.0f));
    M = rotate(M, (-2*PI)/24.0f + ((float)plant1->currentBouncePosition*PI)/24.0f, vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(sp->uM,1,false,glm::value_ptr(M));
    plant1->draw(sp);

    plant2->updateBouncePosition(timeSinceLastDraw / 5.0);
    M = translate(baseM, vec3(8.0f, 1.0f, -30.0f));
    M = scale(M, vec3(35.0f, 35.0f, 35.0f));
    M = rotate(M, (-2*PI)/24.0f + ((float)plant2->currentBouncePosition*PI)/24.0f, vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(sp->uM,1,false,glm::value_ptr(M));
    plant2->draw(sp);


    int max_x = game->getGameTableWidth();
    int max_y = game->getGameTableHeight(); 
    int** gameTable = game->getGameTablePtr();
    for(int y=0; y < max_y; y++)
    {
        for(int x=0; x < max_x; x++)
        {
            // WARNING continue; in head

            // stone field
            {
                M = translate(baseM, vec3(x * 3.0, 0.5f, -y * 3.0));
                M = scale(M, vec3(0.45f, 0.45f, 0.45f));
                glUniformMatrix4fv(sp->uM,1,false,glm::value_ptr(M));
                stone->draw(sp);
            }

            

            // snake tail
            if (gameTable[y][x] == 1)
            {
                M = translate(baseM, vec3(x * 3.0, 1.0, -y * 3.0));
                M = rotate(M, game->getBodyDir(y,x) * -PI/2.0f, vec3(0.0f, 1.0f, 0.0f));
                M = scale(M, vec3(1.0f, 1.0f, 1.5f));
                M = rotate(M, PI/2.0f, vec3(1.0f, 0.0f, 0.0f));
                glUniformMatrix4fv(sp->uM,1,false,glm::value_ptr(M));
                tail->draw(sp);
            }

            // apple
            if (gameTable[y][x] == -1)
            {
                M = translate(baseM, vec3(x * 3.0, 0.0, -y * 3.0));

                // "Bounce animation"
                apple->updateBouncePosition(timeSinceLastDraw);
                M = translate(M, vec3(0.0f, 0.05f + 0.8f * apple->currentBouncePosition, 0.0));

                M = rotate(M, PI/2.0f, vec3(0.0, 1.0f, 0.0f));
                glUniformMatrix4fv(sp->uM,1,false,glm::value_ptr(M));
                apple->draw(sp);
            }

            // snake head
            if (gameTable[y][x] == game->getSnakeLength())
            {
                M = translate(baseM, vec3(x * 3.0, 1.0, -y * 3.0));
                M = rotate(M, game->getHeadDir() * -PI/2.0f, vec3(0.0f, 1.0f, 0.0f));
                M = rotate(M, -PI, vec3(1.0f, 0.0f, 0.0f));
                M = rotate(M, -PI, vec3(0.0f, 0.0f, 1.0f));
                M = translate(M, vec3(0.0f, 0.0f, -0.5f));
                glUniformMatrix4fv(sp->uM,1,false,glm::value_ptr(M));
                head->draw(sp);
                continue;
            }
            // body
            if (gameTable[y][x] > 1)
            {
                if (game->getBendBodyDir(y, x) >=0)
                {
                    // parts which bends
                    M = translate(baseM, vec3(x * 3.0, 1.0, -y * 3.0));
                    M = rotate(M, game->getBendBodyDir(y,x) * -PI/2.0f, vec3(0.0f, 1.0f, 0.0f));
                    //M = scale(M, vec3(1.0f, 1.0f, 1.5f));
                    M = rotate(M, PI/2.0f, vec3(0.0f, 0.0f, 1.0f));
                    M = rotate(M, -PI, vec3(1.0f, 0.0f, 0.0f));
                    M = rotate(M, -PI, vec3(0.0f, 0.0f, 1.0f));
                    glUniformMatrix4fv(sp->uM,1,false,glm::value_ptr(M));
                    bendbody->draw(sp);
                    /*
                        na razie zgiete czesci sa za dlugie i nachodza na bloczki obok
                        moze nie bedzie tego widac po zmianie shadera
                        jezeli bedzie, to sie skroci
                    */
                }
                else
                {
                    // straight parts
                    M = translate(baseM, vec3(x * 3.0, 1.0, -y * 3.0));
                    M = rotate(M, -PI/2.0f * game->getBodyDir(y,x), vec3(0.0f, 1.0f, 0.0f));
                    M = scale(M, vec3(1.0f, 1.0f, 1.5f));
                    M = rotate(M, PI/2.0f, vec3(1.0f, 0.0f, 0.0f));
                    
                    glUniformMatrix4fv(sp->uM,1,false,glm::value_ptr(M));
                    body->draw(sp);
                }
            }
        }
    }
        
    glfwSwapBuffers(window);
}
