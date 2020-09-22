#version 330

uniform sampler2D textureMap;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 n;
in vec4 l[5];
in vec4 v;
in vec2 iTexCoord;

void main(void) {

	vec4 t = texture(textureMap, iTexCoord);
	//vec4 t = vec4(1.0);

	vec4 ml, mr;
	
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);

	float nl, rv;

	vec3 result = vec3(0.0);

	for(int i = 0; i < 4; i++) {
		ml = normalize(l[i]);
		mr = reflect(-ml, mn);

		// Kosinus kąta między wektorami n i l
		nl = clamp(dot(mn, ml), 0, 1);

		// Kosinus kąta między wektorami r i v podniesiony do potęgi
		rv = pow(clamp(dot(mr, mv), 0, 1), 32); 

		result += (t.rgb * nl * 0.9) + vec3(rv);
	}

	float ambient = 0.0;

	{
		ml = normalize(l[4]);
		mr = reflect(-ml, mn);

		// Kosinus kąta między wektorami n i l
		nl = clamp(dot(mn, ml), 0, 1);

		// Kosinus kąta między wektorami r i v podniesiony do potęgi
		rv = pow(clamp(dot(mr, mv), 0, 1), 32); 

		result += (t.rgb * (ambient)) + vec3(rv);
	}

	pixelColor = vec4(result, t.a);

}
