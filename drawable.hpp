#ifndef DRAWABLE_HPP_INCLUDED
#define DRAWABLE_HPP_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader/shaderprogram.h"
#include "glm/glm.hpp"
#include "tiny_obj_loader.h"

using namespace std;
using namespace glm;

#define TINYOBJLOADER_IMPLEMENTATION

struct Drawable {
    GLuint vertexBuffer;
    GLint count;
    size_t vSize;
    size_t nSize;
    size_t tSize;

    // Utwórz obiekt z pliku .obj
    Drawable(const char* filename);
    
    // Rysuj obiekt na scenie
    void draw(ShaderProgram *sp);
};

#endif