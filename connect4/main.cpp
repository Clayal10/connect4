#include "game_board.h"

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
	system("cls");

	char winner;
	if (game_mode == 0) {
		do {
			system("clear");
			play_human(board, &moves);
			board->print_board();
			winner = board->find_winner();
		}while (winner == 'Z');
	}
	else {
		play_machine(board, &moves);
		winner = board->find_winner();
	}

	board->print_board();
	cout << "Winner: " << winner;

	delete board;
	return 0;
}
