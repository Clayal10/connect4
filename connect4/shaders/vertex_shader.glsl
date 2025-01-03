#version 460


in vec3 in_vertex;
uniform mat4 model;

void main(){

	gl_Position =  model * vec4(in_vertex, 1.0);

}
