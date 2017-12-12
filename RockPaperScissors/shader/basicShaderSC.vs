#version 120

//attributes are passed and stay in the buffer
attribute vec3 position;
attribute vec3 color;

//varyings are used to pass data between shaders
varying vec3 color0;

//uniforms are data that dynamically change
uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(position, 1.0);
    color0 = color;
}

