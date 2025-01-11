#define _CRT_SECURE_NO_WARNINGS

#include "helpers.hpp"
#define GBLEN 100000
char* buffer;

void init_helpers() {
	buffer = (char*)malloc(GBLEN);
}
void free_helpers() {
	free(buffer);
}

//Function Definitions
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
	printf("Window resized to %dpx by %dpx\n", width, height);
}


//When function is called, ensure to include directory in relation to /connect4/connect4/
/****Based on make_shader() function from Dr. S. Seth Long****/
GLuint make_shader(const char* filename, GLenum shaderType){
	
	FILE* fd = fopen(filename, "r"); // linux
	//int err = fopen_s(&fd, filename, "r"); //windows
	//if (err != 0) {
    if(!fd){
   		printf("File not found:  %s\n", filename);
        	return 0;
	}
	
	//char* buffer;
	size_t readlen = fread(buffer, 1, GBLEN, fd);
	fclose(fd);
    
	if (readlen == GBLEN) {
  		printf(RED("Buffer Length of %d bytes Inadequate for File %s\n").c_str(), GBLEN, filename);
		return 0;
	}
	if (readlen == 0) {
             puts(RED("File read problem, read 0 bytes").c_str());
             return 0;
        }
	buffer[readlen] = 0;
   	printf(DGREEN("Read shader in file %s (%d bytes)\n").c_str(), filename, readlen);
	puts(buffer);
	
	unsigned int shader_reference = glCreateShader(shaderType);
	glShaderSource(shader_reference, 1, (const char**)&buffer, 0);
	glCompileShader(shader_reference);
	glGetShaderInfoLog(shader_reference, GBLEN, NULL, buffer);
	puts(buffer);
	GLint compile_status;
	glGetShaderiv(shader_reference, GL_COMPILE_STATUS, &compile_status);
	if(compile_status){
		puts(GREEN("Compile Success").c_str());
		return shader_reference;
	}
	puts(RED("Compile Failed\n").c_str());

	return 0;

}

GLuint make_program(const char* vertex_file, const char* fragment_file){
	//Can create conditionals for the perameters, but every object should have both shaders
	unsigned int vertex_shader_reference = make_shader(vertex_file, GL_VERTEX_SHADER);
	unsigned int fragment_shader_reference = make_shader(fragment_file, GL_FRAGMENT_SHADER);
	
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertex_shader_reference);
	glAttachShader(program, fragment_shader_reference);
	glLinkProgram(program);
	
	GLint link_status;
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);
	
	if(!link_status){
		glGetProgramInfoLog(program, GBLEN, NULL, buffer);
		puts(buffer);
		puts(RED("Link Failed").c_str());
		return 0;
	}

	glDeleteShader(vertex_shader_reference);
	glDeleteShader(fragment_shader_reference);

	return program;

}
