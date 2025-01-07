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
gameobject blank; //background for non selected spaces
Board* board = new Board();
int coin_amount;

bool machine_play = false;
bool end_routine = false;
void machine_playing();
void start_screen();

int main() {
	
	start_screen();

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
	coin.set_color(0.973f, 0.016f, 0.008f);
	auto_coin.set_color(1.0f, 0.851f, 0.031f);
	blank.set_color(1.0f, 1.0f, 1.0f);
	board->fill_background(&blank); // adds locations of the board

	objects.push_back(&blank); // putting this first paints it on the background in main loop
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
		
		glClearColor(0.008f, 0.227f, 0.639f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		if (machine_play) {
			machine_playing();
		}
		
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


void machine_playing() {
	
	play_machine(board, 'H');
	update_board_visuals(board->game_board, &coin, 'H');

	char winner = board->find_winner();
	if (winner != 'Z') {
		winning_routine(winner);
		machine_play = false;
		return;
	}
	play_machine(board, 'M');
	update_board_visuals(board->game_board, &auto_coin, 'M');

	winner = board->find_winner();
	if (winner != 'Z') {
		winning_routine(winner);
		machine_play = false;
		return;
	}

}

void game_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { // Window Handling
		puts(RED("Window Closed by User").c_str());
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { // Clear Board
		if (end_routine) {
			reset_game();
			end_routine = false;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) { // Start PvM
		coin.locations.push_back(glm::vec3(0.9f, 0.5f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) { // Start MvM
		machine_play = true;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && coin_amount != -1) { // Move Left
		float x_loc = coin.locations[coin_amount].x;
		if (x_loc > -0.9f) {
			coin.locations[coin_amount].x -= 0.2f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && coin_amount != -1) { // Move Right
		float x_loc = coin.locations[coin_amount].x;
		if (x_loc < 0.9f) {
			coin.locations[coin_amount].x += 0.2f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) { // Select
		if (coin_amount == -1) return;
		if (coin.locations[coin_amount].x > 0.5f || coin.locations[coin_amount].x < -0.7 || end_routine) {
			return;
		}
		play_human(board, &coin, 'H');
		update_board_visuals(board->game_board, &coin, 'H');
		play_human(board, &auto_coin, 'M');
		update_board_visuals(board->game_board, &auto_coin, 'M');

		coin.locations.push_back(glm::vec3(0.9f, 0.5f, 0.0f)); //put back coin at the start

		char winner = board->find_winner();
		winning_routine(winner);
	}
}

//This function can allow for more ceremony when a player wins
void winning_routine(char winner) {
	if (winner == 'Z') {
		return;
	}
	else {
		printf(GREEN("Winner is %c\n").c_str(), winner);
		end_routine = true;
	}
}

void reset_game() {
	for (auto GO : objects) {
		GO->locations.clear();
	}
	board->reset_board();
	board->fill_background(&blank);
}

void start_screen() {
	//Start Screen
	printf("\n\n********************************************");
	printf("\n*          ");
	printf(BLUE("Welcome to Connect 4!           ").c_str());
	printf("*\n*Controls:     P - Start Player vs Machine *");
	printf("\n*              M - Start Machine vs Machine*");
	printf("\n* <-and-> Arrows - Move player piece       *");
	printf("\n*    'Enter' key - Select the Column       *");
	printf("\n*    'Space' key - Reset the game          *");
	printf("\n*      'ESC' Key - Close Window            *");
	printf("\n********************************************");
	std::cout << "\nPress Enter to Start: ";
	std::cin.get();
}
