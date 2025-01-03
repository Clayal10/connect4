#include "game_board.hpp"
#include "helpers.hpp"
#include "scolor.hpp"

using namespace std;

std::vector<gameobject*> objects;

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
	glViewport(0, 0, 1000, 800);
	/*Callbacks*/
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/****End of Window Creation****/
	/****Object Creation****/

	gameobject test_object;
	objects.push_back(&test_object);
	
	for(gameobject* obj : objects){
		obj->init();
	}

	/***End of Object Creation****/	
	srand((unsigned int)time(0));
	Board* board = new Board();
	std::vector<std::vector<int>> moves;



	/****Main Loop, Called every frame****/
	while (!glfwWindowShouldClose(window)){
		glClearColor(0.208f, 0.659f, 0.902f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		window_key_callback(window);
	
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
	/* Text based game


	int game_mode = -1;
	if (game_mode != 0 && game_mode != 1) {
		cout << "Welcome to Connect 4!\nChoose Game Mode (0 Human v. Machine, 1 Machine v. Machine): ";
		cin >> game_mode;
	}
	system("clear"); // linux
	//system("cls"); // windows

	char winner;
	if (game_mode == 0) {
		do {
			system("clear");
			play_human(board, &moves);
			board->print_board();
			winner = board->find_winner();
			if(winner == 'T')break;
		}while (winner == 'Z');
	}
	else {
		play_machine(board, &moves);
		winner = board->find_winner();
	}

	board->print_board();
	cout << "Winner: " << winner << "\n";
	
	delete board;
	return 0;
	
	*/
}
