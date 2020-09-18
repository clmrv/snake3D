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
    Drawable *apple;
    Drawable *stone;
    Drawable *grass;
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
    void draw();

    vec3 cam = vec3(-8, -18.0, -1);

};

#endif