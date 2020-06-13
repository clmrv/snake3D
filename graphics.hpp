#ifndef GRAPHICS_HPP_INCLUDED
#define GRAPHICS_HPP_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// myCube - testowo
#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "myCube/constants.h"
#include "myCube/shaderprogram.h"
#include "myCube/myCube.h"


class Graphics {
private:
    /// Okno animacji
    GLFWwindow* window;

    /// Tablica z "Vertex Array Object Names"
    GLuint vba;

    /// Tablica z "Buffer Object Names"
    GLuint vb;

    // myCube - testowo
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