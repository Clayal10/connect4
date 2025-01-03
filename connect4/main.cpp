#include "game_board.h"

#define CLEAR "cls"
//#define CLEARN "clear"
using namespace std;

int main() {
	srand((unsigned int)time(0));
	Board* board = new Board();
	std::vector<std::vector<int>> moves;

	int game_mode = -1;
	if (game_mode != 0 && game_mode != 1) {
		cout << "Welcome to Connect 4!\nChoose Game Mode (0 Human v. Machine, 1 Machine v. Machine): ";
		cin >> game_mode;
	}
	system(CLEAR);
	char winner;
	if (game_mode == 0) {
		do {
			system(CLEAR);
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
}
