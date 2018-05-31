#version 120

attribute vec3 position;
attribute vec2 uv;

uniform mat4 transform;

varying vec2 uv0;

void main(){
	uv0 = uv;
	vec3 pos = position;
	pos.y *= -1;
	gl_Position = transform * vec4(pos, 1.0);
}