#version 330

//variables d'entrées
in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

vec2 fCorrectCoords;

out vec4 fFragColor;

//materiau de l'objet
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

//info sur la lumiere
uniform vec3 uLightDir_vs; //modifier dans la view space = wi normalisé
uniform vec3 uLightIntensity; //Li

vec3 blinnPhong(vec3 Kd, vec3 Ks, float shininess){
	vec3 wi = normalize(uLightDir_vs);
	vec3 Li = uLightIntensity;
	vec3 w0 = normalize(-vPosition_vs);
	vec3 halfVector = (w0 + wi) / 2;

	Kd = vec3(0.7, 0., 0.);
	Ks = vec3(0., 0., 0.7);
	shininess = 0.;
	// return normalize(vNormal_vs);
	return Li*(Kd*max(dot(wi, normalize(vNormal_vs)), 0.) + Ks*pow((max(dot(halfVector, normalize(vNormal_vs)), 0.)),shininess));
}

void main() {


    fCorrectCoords = vec2(vTexCoords.x, 1-vTexCoords.y); //pour le template p6


	fFragColor = vec4(blinnPhong(uKd, uKs, uShininess), 1.);
	
}