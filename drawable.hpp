#ifndef DRAWABLE_HPP_INCLUDED
#define DRAWABLE_HPP_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader/shaderprogram.h"
#include "glm/glm.hpp"
#include "tiny_obj_loader.h"
#include "lodepng/lodepng.h"

using namespace std;
using namespace glm;

#define TINYOBJLOADER_IMPLEMENTATION

struct Drawable {
    GLuint vertexBuffer;
    GLint count;
    size_t vSize;
    size_t nSize;
    size_t tSize;

    bool hasTexture = false;
    GLuint texName;

    // Utwórz obiekt z pliku .obj
    Drawable(const char* filename);
    ~Drawable();

    // Załaduj teksturę
    void loadTexture(const char* filename);
    
    // Rysuj obiekt na scenie
    void draw(ShaderProgram *sp);
};

#endif