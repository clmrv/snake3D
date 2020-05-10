#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Graphics {
private:
    /// Okno animacji
    GLFWwindow* window;

    /// Tablica z "Vertex Array Object Names"
    GLuint vba;

    /// Tablica z "Buffer Object Names"
    GLuint vb;

    
public:
    /// Inicjalizuj grafikę w danym oknie
    Graphics(GLFWwindow* window);

    /// Zwolnij zasoby
    ~Graphics();

    /// Rysuje klatkę animacji
    void draw();

};