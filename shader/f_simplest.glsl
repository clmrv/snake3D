#version 330

uniform sampler2D textureMap;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 n;
in vec4 l;
in vec4 v;
in vec2 iTexCoord;

void main(void) {

	vec4 ml = normalize(l);
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);
	vec4 mr = reflect(-ml, mn);

	// Kosinus kąta między wektorami n i l
	float nl = clamp(dot(mn, ml), 0, 1);

	// Kosinus kąta między wektorami r i v podniesiony do potęgi
	float rv = pow(clamp(dot(mr, mv), 0, 1), 32); 

	vec4 t = texture(textureMap, iTexCoord);
	//vec4 t = vec4(1.0);

	float ambient = 0.35;

	// Wyliczenie koloru piksela
	pixelColor = vec4(t.rgb * (nl + ambient), t.a) + vec4(rv, rv, rv, 0); 

}
