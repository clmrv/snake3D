#version 330

uniform sampler2D textureMap;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 ic; 
in vec4 n;
in vec4 l;
in vec4 v;
in vec2 iTexCoord;

void main(void) {
	
	vec4 ml = normalize(l);
	vec4 mn = normalize(n);
	float nl = clamp(dot(mn, ml), 0, 1); //Kosinus kąta pomiędzy wektorami n i l.

	vec4 mv = normalize(v);
	vec4 mr = reflect(-ml,mn); //Wektor odbity
	float rv = pow(clamp(dot(mr, mv), 0, 1), 500); // Kosinus kąta pomiędzy wektorami r i v podniesiony do 25 potęgi

	vec4 t = texture(textureMap, iTexCoord);

	pixelColor= vec4(t.rgb, t.a) + vec4(rv, rv, rv, 0); //Wyliczenie modelu oświetlenia (bez ambient);
	//pixelColor = vec4(1,1,1,1);
}
