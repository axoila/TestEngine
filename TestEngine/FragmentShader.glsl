#version 120

uniform sampler2D mainTex;

varying vec2 uv0;

void main(){
	gl_FragColor = texture2D(mainTex, uv0);
}