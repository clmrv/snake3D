#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color; //kolor związany z wierzchołkiem
in vec4 normal; //wektor normalny w przestrzeni modelu
in vec2 texCoord;

//Zmienne interpolowane
out vec4 l;
out vec4 n;
out vec4 v;
out vec2 iTexCoord;

void main(void) {

    // Pozycja światła w przestrzeni świata
    //vec4 lp = vec4(20, -120, 50, 1);
    vec4 lp = vec4(-4, -30, 8, 1);

    
    // Znormalizowany wektor do światła w przestrzeni oka
    l = normalize(V * (lp - (M * vertex))); 

    // Znormalizowany wektor normalny w przestrzeni oka
    n = normalize(V * M * normal); 

    // Wektor do obserwatora w przestrzeni oka
    v = normalize( vec4(0, 0, 0, 1) - V * M * vertex );

    iTexCoord = texCoord;
    
    gl_Position=P*V*M*vertex;
}
