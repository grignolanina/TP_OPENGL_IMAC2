#version 330 core

layout(location = 0) in vec2 aVertexPosition;
// layout (location = 1) in vec2 aVertexColor;
layout (location = 1) in vec2 aVertexTexture;

// out vec3 vFragColor;
out vec2 vFragTexture;
// out vec2 vFragPosition;

//uniform float uTime; //variable uniforme utilise pour envoyer le temps ecouler depuis le debut d'app a notre shader
uniform mat3 uModelMatrix;
// uniform vec3 uColor;

mat3 rotate(float a){
  return mat3(vec3(cos(radians(a)), sin(radians(a)), 0), vec3(-sin(radians(a)),cos(radians(a)) , 0), vec3(0, 0, 1));
}

void main(){

	// mat3 r = rotate(uTime);
	mat3 r = uModelMatrix;
	// vFragColor = uColor;
	vFragTexture = aVertexTexture;
	gl_Position = vec4((r*vec3(aVertexPosition, 1)).xy, 0, 1);

	// vFragPosition = aVertexTexture;
	// vFragTexture = (r*vec3(aVertexPosition, 1)).xy;
	// gl_Position = vec4(vFragTexture, 0., 1.);
}