#include "helpers.hpp"

//all objects are initialized right before the main loop
int gameobject::init(){
	//std::vector<glm::vec2> locations;
	float vertices[] = {
		0.2f, 0.2f, 0.0f, 	//top right
		0.2f, -0.2f, 0.0f,	//bottom right 
		-0.2f, -0.2f, 0.0f,	//bottom left
		-0.2f, 0.2f, 0.0f,	//top left
	};

	unsigned int indicies[] = {
		0, 1, 3,
		1, 2, 3,
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO); //used for mulitple triangles

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	
	shader_program = make_program("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
	if(!shader_program){
		return 1;
	}

	//Get attributes for shaders here
	vertex_attrib = glGetAttribLocation(shader_program, "in_vertex");
	mvp_uniform = glGetUniformLocation(shader_program, "mvp");

	return 0;
};

//Called in the main loop
void gameobject::draw(){
	
	glEnableVertexAttribArray(vertex_attrib);
	glVertexAttribPointer(vertex_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	/****Movement****/
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0)); // rotate around z
	
	glUseProgram(shader_program);
	unsigned int transformLoc = glGetUniformLocation(shader_program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));


	/*	
	int size;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	

	glUniformMatrix4fv(mvp_uniform, 1, 0, glm::value_ptr(vp));
	
	glDrawElementsInstanced(GL_TRIANGLES, size / sizeof(uint16_t), GL_UNSIGNED_INT, 0, 100);	
	*/
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
