#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shaderprogram.h"


class Graphics {
private:
    /// Okno animacji
    GLFWwindow* window;

    /// Tablica z "Vertex Array Object Names"
    GLuint vba;

    /// Tablica z "Buffer Object Names"
    GLuint vb;


    ShaderProgram *sp;

    const float PI = 3.141592653589793f;

    
public:
    /// Inicjalizuj grafikę w danym oknie
    Graphics(GLFWwindow* window);

    /// Zwolnij zasoby
    ~Graphics();

    /// Rysuje klatkę animacji
    void draw();

};

#endif