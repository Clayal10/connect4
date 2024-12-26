#include "game_board.h"

using namespace std;

int main() {
	srand((unsigned int)time(0));
	Board* board = new Board();

	int game_mode = -1;
	if (game_mode != 0 || game_mode != 1) {
		cout << "Welcome to Connect 4!\nChoose Game Mode (0 Human v. Machine, 1 Machine v. Machine): ";
		cin >> game_mode;
	}
	system("cls");

	std::vector<std::vector<int>> moves;
	play(game_mode, board, &moves);
	
	board->print_board();

	delete board;
	return 0;
}