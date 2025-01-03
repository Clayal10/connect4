#include "helpers.hpp"

//all objects are initialized right before the main loop
int gameobject::init(){
	//std::vector<glm::vec2> locations;
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO); //used for mulitple triangles


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(), )

	shader_program = make_program("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
	if(!shader_program){
		return 1;
	}

	//Get attributes for shaders here
	vertex_attrib = glGetAttribLocation(shader_program, "in_vertex");

	return 0;
};

//Called in the main loop
void gameobject::draw(){
	glUseProgram(shader_program);
	
	glEnableVertexAttribArray(vertex_attrib);
	glBindVertexArray(VAO);
	glVertexAttribPointer(vertex_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 3);	
}
