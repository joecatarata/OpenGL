#version 120

attribute vec3 position;
varying vec3 color0;

uniform mat4 transform;
uniform vec3 color;

void main() {
	gl_Position = transform * vec4(position, 1.0);
    color0 = color;
}

