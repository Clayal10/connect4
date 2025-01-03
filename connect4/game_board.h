#pragma once

#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<cmath>

//TODO
//	-Clean up find_winner()
//	-Make it a 2d game!

class Board {
public:
	std::vector<std::vector<char>> game_board;

	void print_board() {
		for (int i = 0; i < game_board.size(); i++) {
			for (int j = 0; j < game_board[0].size(); j++) {
				std::cout << game_board[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
	void reset_board() {
		for (int i = 0; i < game_board.size(); i++) {
			for (int j = 0; j < game_board[0].size(); j++) {
				game_board[i][j] = '*';
			}
		}
	}
	void update_board(int col, char player, bool in_minimax);
	std::vector<std::vector<char>> child_board(std::vector<std::vector<char>> game_board_child, int col, char player, bool in_minimax);

	char find_winner() {
		//Returns the entity who won
		//TODO Clean this up
		int checker = 0;
		for(int j=0; j<game_board.size(); j++){
			for(int i=0; i<game_board[0].size(); i++){
				if(game_board[j][i] == '*')
					checker++;		
			}
		}
		if(checker=0) return 'T';

		//horizontal win
		for (int j = 0; j < game_board.size(); j++) {
			for (int i = 0; i < game_board[0].size() - 3; i++) {
				if (game_board[j][i] == 'X' && game_board[j][i + 1] == 'X' &&
					game_board[j][i + 2] == 'X' && game_board[j][i + 3] == 'X') {
					return 'H';
				}
			}
		}
		//vertical win
		for (int j = 0; j < game_board[0].size(); j++) {
			for (int i = 0; i < game_board.size() - 3; i++) {
				if (game_board[i][j] == 'X' && game_board[i + 1][j] == 'X' &&
					game_board[i + 2][j] == 'X' && game_board[i + 3][j] == 'X') {
					return 'H';
				}
			}
		}
		//diagonal up win
		for (int i = 3; i < game_board.size(); i++) {
			for (int j = 0; j < game_board[0].size() - 3; j++) {
				if (game_board[i][j] == 'X' && game_board[i - 1][j + 1] == 'X' &&
					game_board[i - 2][j + 2] == 'X' && game_board[i - 3][j + 3] == 'X') {
					return 'H';
				}
			}

		}
		//diagonal down win
		for (int i = 3; i < game_board.size(); i++) {
			for (int j = 3; j < game_board[0].size(); j++) {
				if (game_board[i][j] == 'X' && game_board[i - 1][j - 1] == 'X' &&
					game_board[i - 2][j - 2] == 'X' && game_board[i - 3][j - 3] == 'X') {
					return 'H';
				}
			}

		}

		//check if AI won
		for (int j = 0; j < game_board.size(); j++) {
			for (int i = 0; i < game_board[0].size() - 3; i++) {
				if (game_board[j][i] == 'O' && game_board[j][i + 1] == 'O' &&
					game_board[j][i + 2] == 'O' && game_board[j][i + 3] == 'O') {
					return 'M';
				}
			}
		}
		//vertical win
		for (int j = 0; j < game_board[0].size(); j++) {
			for (int i = 0; i < game_board.size() - 3; i++) {
				if (game_board[i][j] == 'O' && game_board[i + 1][j] == 'O' &&
					game_board[i + 2][j] == 'O' && game_board[i + 3][j] == 'O') {
					return 'M';
				}
			}
		}
		//diagonal up win
		for (int i = 3; i < game_board.size(); i++) {
			for (int j = 0; j < game_board[0].size() - 3; j++) {
				if (game_board[i][j] == 'O' && game_board[i - 1][j + 1] == 'O' &&
					game_board[i - 2][j + 2] == 'O' && game_board[i - 3][j + 3] == 'O') {
					return 'M';
				}
			}

		}
		//diagonal down win
		for (int i = 3; i < game_board.size(); i++) {
			for (int j = 3; j < game_board[0].size(); j++) {
				if (game_board[i][j] == 'O' && game_board[i - 1][j - 1] == 'O' &&
					game_board[i - 2][j - 2] == 'O' && game_board[i - 3][j - 3] == 'O') {
					return 'M';
				}
			}

		}
		//In the case of no victor
		return 'Z';
	}

	int minimax(std::vector<std::vector<char>> game_board, int depth, int alpha, int beta, bool maximizing_player, char player, int& selection, bool first_time);
	int h_eval(char player);

	Board() {
		for (int i = 0; i < 6; i++) {
			std::vector<char> buff;
			for (int j = 0; j < 7; j++) {
				buff.push_back('*');
			}
			game_board.push_back(buff);
		}
	}
};

void play_human(Board* board, std::vector<std::vector<int>>* moves);
void play_machine(Board* board, std::vector<std::vector<int>>* moves);
