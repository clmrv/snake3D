#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lps[5];

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color; //kolor związany z wierzchołkiem
in vec4 normal; //wektor normalny w przestrzeni modelu
in vec2 texCoord;

//Zmienne interpolowane
out vec4 l[5];
out vec4 n;
out vec4 v;
out vec2 iTexCoord;

void main(void) {

    // Pozycje świateł w przestrzeni świata
    for(int i = 0; i < 5; i++) {
        l[i] = normalize(V * (lps[i] - (M * vertex)));
    }

    
    // Znormalizowany wektor do światła w przestrzeni oka
    //l = normalize(V * (lp - (M * vertex))); 

    // Znormalizowany wektor normalny w przestrzeni oka
    n = normalize(V * M * normal); 

    // Wektor do obserwatora w przestrzeni oka
    v = normalize( vec4(0, 0, 0, 1) - V * M * vertex );

    iTexCoord = texCoord;
    
    gl_Position=P*V*M*vertex;
}
