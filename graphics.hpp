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

    ShaderProgram *sp;

    
public:
    /// Inicjalizuj grafikę w danym oknie
    Graphics(GLFWwindow* window);

    /// Zwolnij zasoby
    ~Graphics();

    /// Rysuje klatkę animacji
    void draw();

};

#endif