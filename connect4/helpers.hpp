#pragma once

#include<iostream>
#include<vector>
#include<mutex>
#include<thread>

#include "scolor.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



//Prototypes
/****Defined in window_helpers.cpp****/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLuint make_shader(const char* filename, GLenum shaderType);
//make_program() can be modified if I need more shaders for objects
GLuint make_program(const char* vertex_file, const char* fragment_file);

/****Defined in main****/
void game_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void winning_routine(char winner);
void reset_game();

//Objects
/****Defined in game_helpers.cpp****/
void init_helpers();
void free_helpers();



class gameobject{
public:
	unsigned int VBO, VAO, EBO, shader_program, vertex_attrib, mvp_uniform, vertex_color, current_idx;
	float red, green, blue, vertical_movement, speed;
	std::vector<glm::vec3> locations;
	int init();
	void draw();
	void move(); // This will be called in a seperately threaded function
	void set_color(float r, float g, float b);
	bool in_spot(int row, int col);
};

/****Defined in game.cpp****/
void update_board_visuals(std::vector<std::vector<char>> game_board, gameobject* coin, char player);
int unit_conversion(float visual_location);
int v_unit_conversion(float visual_location);
float h_conversion(int idx_location);
float v_conversion(int idx_location);



extern int coin_amount;
extern int shutdown_engine;
