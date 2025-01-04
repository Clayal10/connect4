#include "game_board.hpp"
#include "helpers.hpp"
#include "scolor.hpp"

using namespace std;

std::vector<gameobject*> objects;
std::mutex grand_mutex;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

gameobject coin; // user coin
gameobject auto_coin; // machine coin
Board* board = new Board();
int coin_amount;

int main() {
	init_helpers();
	/****Window Creation****/
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Connect 4", NULL, NULL);
	if (!window){
		puts(RED("Failed to initialize Window").c_str());
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		puts(RED("Failed to initialize GLAD").c_str());
		return -1;
	}
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	/*Callbacks*/
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, game_key_callback);

	/****End of Window Creation****/
	/****Object Creation****/
	coin.set_color(1.0f, 0.0f, 0.0f);
	auto_coin.set_color(1.0f, 1.0f, 0.0f);
	//coin.locations.push_back(glm::vec3(-0.9f, -0.9f, 0.0f));
	objects.push_back(&coin);
	objects.push_back(&auto_coin);
	
	for(gameobject* obj : objects){
		obj->init();
	}

	/***End of Object Creation****/	
	srand((unsigned int)time(0));


	/****Main Loop, Called every frame****/
	while (!glfwWindowShouldClose(window)){
		coin_amount = coin.locations.size()-1;
	
		glClearColor(0.0f, 0.0f, 0.541f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		
		
		//glm::mat4 vp = glm::perspective(3.14159f/1.5f, 1.0f, 0.1f, 1000.0f);
		for(gameobject* obj : objects){
			obj->draw();
		}


		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	delete board;
	free_helpers();

	return 0;
}

void game_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { // Window Handling
		puts(RED("Window Closed by User").c_str());
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { // Creation
		coin.locations.push_back(glm::vec3(0.9f, 0.9f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && coin_amount != -1) { // Move Left
		puts(BLUE("LEFT").c_str());
		float x_loc = coin.locations[coin_amount].x;
		if (x_loc > -0.9f) {
			coin.locations[coin_amount].x -= 0.2f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && coin_amount != -1) { // Move Right
		puts(BLUE("RIGHT").c_str());
		float x_loc = coin.locations[coin_amount].x;
		if (x_loc < 0.9f) {
			coin.locations[coin_amount].x += 0.2f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) { // Select
		play_human(board, &coin, 'H');
		update_board_visuals(board->game_board, &coin);
		play_human(board, &auto_coin, 'M');
		update_board_visuals(board->game_board, &auto_coin);

	}
}
