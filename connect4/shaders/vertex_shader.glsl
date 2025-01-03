#version 460


in vec3 in_vertex;
uniform mat4 transform;

void main(){

	gl_Position = transform * vec4(in_vertex, 1.0);

}
