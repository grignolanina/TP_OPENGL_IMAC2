
#version 330 core

// in vec3 vFragColor;
in vec2 vFragTexture;
// in vec2 vFragPosition;

// out vec4 fFragColor;
out vec4 fFragTexture;

uniform sampler2D uTexture;

void main(){
	
	//fFragColor = vec4(1., 1., 0., 1.);	
	// fFragColor = vec4(vFragColor, 1.);
	vec4 T = vec4(texture(uTexture,vFragTexture));
	fFragTexture = T;
}
