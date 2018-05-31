#version 120

attribute vec3 position;
attribute vec2 uv;

uniform mat4 transform;

varying vec2 uv0;

void main(){
	uv0 = uv;
	gl_Position = transform * vec4(position, 1.0);
}