#include "game_board.hpp"
#include "helpers.hpp"
#include "scolor.hpp"

using namespace std;

std::vector<gameobject*> objects;
std::mutex grand_mutex;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

gameobject coin;
int coin_amount;

void game_key_callback(GLFWwindow *window){
	//TODO Limit to 1 per press OR TODO mouse implimentation
	if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
		coin.locations.push_back(glm::vec3(0.9f, 0.9f, 0.0f));
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && coin_amount != -1){
		puts(BLUE("PRESSED").c_str());
		coin.locations[coin_amount].x -= 0.1f;
	}
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && coin_amount != -1){
		puts(BLUE("PRESSED").c_str());
		coin.locations[coin_amount].x += 0.1f;
	}
}


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
	window = glfwCreateWindow(1000, 800, "Connect 4", NULL, NULL);
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

	/****End of Window Creation****/
	/****Object Creation****/

	objects.push_back(&coin);
	
	for(gameobject* obj : objects){
		obj->init();
	}

	/***End of Object Creation****/	
	srand((unsigned int)time(0));
	Board* board = new Board();
	std::vector<std::vector<int>> moves;



	/****Main Loop, Called every frame****/
	while (!glfwWindowShouldClose(window)){
		coin_amount = coin.locations.size()-1;
	
		glClearColor(0.025f, 0.364f, 0.411f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		
		/****Callbacks****/
		window_key_callback(window);
		game_key_callback(window);

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
