#version 330 core

in vec3 vFragColor;
in vec2 vFragPosition;

out vec3 fFragColor;

void main() {
	float alpha = 1.5;
	float beta = 50.;
	float a = alpha * exp(-beta * distance(vec2(0, 0), vFragPosition)*distance(vec2(0, 0), vFragPosition));

	float test = length(fract(5.0 * vFragPosition));
	float test2 = length(abs(fract(5.0 * vFragPosition) * 2.0 - 1.0));
	float test3 = mod(floor(10.0 * vFragPosition.x) + floor(10.0 * vFragPosition.y), 2.0);
	float test4 = smoothstep(0.3, 0.32, length(fract(5.0 * vFragPosition) - 0.5));
	float test5 = smoothstep(0.4, 0.5, max(abs(fract(8.0 * vFragPosition.x - 0.5 * mod(floor(8.0 * vFragPosition.y), 2.0)) - 0.5), abs(fract(8.0 * vFragPosition.y) - 0.5)));


  	fFragColor = vFragColor*a;
};