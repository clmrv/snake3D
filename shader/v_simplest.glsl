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
out vec4 ic;
out vec4 l;
out vec4 n;
out vec4 v;
out vec2 iTexCoord;

void main(void) {
    vec4 lp = vec4(-25, 30, -25, 1);
    //vec4 lp = vec4(-13.5, 80, -6, 1); //pozcyja światła, przestrzeń świata

    // l = normalize(V * (lp - M * vertex));
    // v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //wektor do obserwatora w przestrzeni oka
    // n = normalize(V * M * normal); //wektor normalny w przestrzeni oka

    l = normalize(V * (lp - M * vertex));//znormalizowany wektor do światła w przestrzeni oka
    n = normalize(V * M * normal);//znormalizowany wektor normalny w przestrzeni oka
    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //Wektor do obserwatora w przestrzeni oka

    ic = vec4(0.5f, 0.8f, 0.5f, 1.0f);
    iTexCoord = texCoord;
    
    gl_Position=P*V*M*vertex;
}
