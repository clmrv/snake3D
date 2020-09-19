#ifndef GRAPHICS_HPP_INCLUDED
#define GRAPHICS_HPP_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader/constants.h"
#include "shader/shaderprogram.h"


#include "drawable.hpp"

#include "game.hpp"

struct Drawable;
struct DrawableArray;

class Graphics {
private:
    /// Okno animacji
    GLFWwindow* window;

    /// Tablica z "Vertex Array Object Names"
    GLuint vba;

    /// Przykładowy obiekt do narysowania
    Drawable *d;
    Bounceable *apple;
    Drawable *stone;
    Drawable *grass;
    Bounceable *plant1;
    Bounceable *plant2;
    Drawable *body;
    Drawable *tail;
    Drawable *bendbody;
    Drawable *head;

    ShaderProgram *sp;

    Game* game;

    
public:
    /// Inicjalizuj grafikę w danym oknie, odbierz pointer na tabele z pozycja snake
    Graphics(GLFWwindow* window, Game* game);

    /// Zwolnij zasoby
    ~Graphics();

    /// Rysuje klatkę animacji
    void draw(double timeSinceLastDraw = 0);

    /// Proporcje obrazu
    float aspectRatio = 1.0;
    
    // vec3 eye = vec3(15, 35, 32);
    // vec3 cam = vec3(11, -39, -1);
    vec3 eye = vec3(15, 35, 5);
    vec3 cam = vec3(13, -4, -14);

};

#endif