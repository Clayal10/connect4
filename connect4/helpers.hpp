#pragma once

#include<iostream>

#include "scolor.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> //TODO link in msvs

//Prototypes
/****Defined in window_helpers.cpp****/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void window_key_callback(GLFWwindow *window);
GLuint make_shader(const char* filename, GLenum shaderType);
//make_program() can be modified if I need more shaders for objects
GLuint make_program(const char* vertex_file, const char* fragment_file);

//Objects
/****Defined in game_helpers.cpp****/
void init_helpers();
void free_helpers();
class gameobject{
public:
	unsigned int VBO, VAO, EBO, shader_program, vertex_attrib;
	int init();
	void draw();
};
