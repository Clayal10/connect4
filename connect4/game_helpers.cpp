#include "helpers.hpp"

//all objects are initialized right before the main loop
int gameobject::init(){
	vertical_movement = 0; // should declare this
	speed = 0.01f;

	float vertices[] = {

		0.0f, 0.095f, 0.0f,		//0 top
		0.07f, 0.07f, 0.0f,		//1 top right
		0.095f, 0.0f, 0.0f,		//2 right
		0.07f, -0.07f, 0.0f,	//3 bottom right 
		0.0f, -0.095f, 0.0f,	//4 bottom
		-0.07f, -0.07f, 0.0f,	//5 bottom left
		-0.095f, 0.0f, 0.0f,	//6 left
		-0.07f, 0.07f, 0.0f,	//7 top left
	};

	unsigned int indicies[] = {

		0, 2, 4,
		4, 6, 0,
		0, 2, 1,
		2, 4, 3,
		4, 6, 5,
		6, 0, 7,

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
	vertex_color = glGetUniformLocation(shader_program, "v_color");

	return 0;
};

//Called in the main loop
void gameobject::draw(){
	
	
	glUseProgram(shader_program);

	glUniform4f(vertex_color, red, green, blue, 1.0f);
	
	glEnableVertexAttribArray(vertex_attrib);
	glVertexAttribPointer(vertex_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(VAO);
	/****adding more instances****/
	std::vector<glm::mat4> models;
	models.reserve(locations.size());
	for(glm::vec3 l : locations){
		glm::mat4 new_model = glm::mat4(1.0f);
		new_model = translate(new_model, l);
		models.push_back(new_model);
		glGetUniformLocation(shader_program, "model");
		glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, &new_model[0][0]);
		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	}
	
}

void gameobject::set_color(float r, float g, float b) {
	red = r;
	green = g;
	blue = b;
}

bool gameobject::in_spot(int row, int col) {
	for (unsigned int i = 0; i < locations.size(); i++) {
		if (unit_conversion(locations[i].x) == col && v_unit_conversion(locations[i].y == row)){
			return true;
		}
	}
	return false;
}

void gameobject::move() {
	// vertical_movement is a single variable for every location in each instance of the gameobject.
	//		-keep this in mind
	puts("called move");
	if (vertical_movement > 0) {
		puts(RED("Entered if statement").c_str());
		locations[coin_amount].y -= speed; // FIX CREATING THE NEXT OBJECT BEFORE THIS ONE IS DONE WITH
		vertical_movement -= speed;
	}
}


