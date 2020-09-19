#ifndef DRAWABLE_HPP_INCLUDED
#define DRAWABLE_HPP_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader/shaderprogram.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
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
    void draw(ShaderProgram *sp, mat4 &M);
};


struct Bounceable: Drawable {

    // Obecna odległość od podłoża
    double currentBouncePosition = 0.0;

    // Informacja czy ruch odbywa się w górę czy w dół
    bool bouncingUp = true;

    Bounceable(const char* filename) : Drawable(filename) { }

    // Zaktualizuj pozycję obiektu
    void updateBouncePosition(double timeSinceLastDraw);

};


struct Text: Bounceable {
    float minHeight;

    // Obecna odległość od podłoża
    float currentHeight = 0.0;

    Text(const char* filename, float minHeight = 0.0, float maxHeight = 20.0) : Bounceable(filename) {
        this->minHeight = minHeight;
        this->currentHeight = maxHeight;
    }

    // Zaktualizuj pozycję obiektu
    void updatePosition(float by);

};

#endif