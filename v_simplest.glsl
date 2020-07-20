#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color;

out vec4 iC;

void main(void) {
    float d;

    d = distance(V*M*vertex, vec4(0,5,-5,1));
    // z modelu do swiata M*vertex
    // z swiata do oka V*

    d = 1- (d-3.3) / 1.7;

    iC = vec4(color.rgb*d, color.a);
    gl_Position=P*V*M*vertex;
}
