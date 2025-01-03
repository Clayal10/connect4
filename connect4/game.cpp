#include<fstream>
#include "game_board.h"
#define inf std::numeric_limits<int>::max()
#define neg_inf -std::numeric_limits<int>::max()

extern bool try_again = false;
extern char up_next = 'M'; //start with machine

//TODO
//	-Clean up minimax
//		-Don't make it too intensive but maybe make a proper minimax function.
//		 This can be difficult since connect 4 has so many possibilities but we will try!


void play_human(Board* board, std::vector<std::vector<int>>* moves) {
	//print the board for the first time
	board->print_board();

	std::vector<int> move(2);
	int selection;
	int selection_val;
	do {
		//just do this section every other time (the other time will be AI)
		if (up_next == 'H') {
			std::cout << "Pick a Column for your move: ";
			std::cin >> selection;
			move[0] = 1;
			move[1] = selection;
			moves->push_back(move);
		}
		else {
			//stuff for ai
			selection_val = board->minimax(board->game_board, 8, neg_inf, inf, true, 'M', selection, true); //this perameter is the state after the user goes
			move[0] = 2;
			move[1] = selection;
			moves->push_back(move);
		}

		board->update_board(selection, up_next, false); // doesn't update if invalid placement
	} while (try_again);

	//swap who goes next
	if (up_next == 'H')
		up_next = 'M';
	else
		up_next = 'H';
}

void play_machine(Board* board, std::vector<std::vector<int>>* moves) {
	//AI vs AI
	char winner = 'Z';//H is first ai, M is second
	int selection;
	int selection_val;
	std::vector<int> move(2);
	while (winner == 'Z') { //This will just do everything in one go
		if (up_next == 'H') {
			selection_val = board->minimax(board->game_board, 5, neg_inf, inf, true, 'H', selection, true);//dont think i actually need this value
			move[0] = 1;
			move[1] = selection;
			moves->push_back(move);
		}
		else {
			//stuff for ai
			selection_val = board->minimax(board->game_board, 5, neg_inf, inf, true, 'M', selection, true); //this perameter is the state after the user goes
			move[0] = 2;
			move[1] = selection;
			moves->push_back(move);
		}

		board->update_board(selection, up_next, false);
		if (try_again) {
			continue;
		}

		//swap who goes next
		if (up_next == 'H')
			up_next = 'M';
		else
			up_next = 'H';

		winner = board->find_winner();

	}
	int ai_winner;
	if (winner == 'H') {
		ai_winner = 1;
	}
	else {
		ai_winner = 2;
	}

	std::cout << "Winner is: " << ai_winner << std::endl;

	//board->reset_board();
	//moves->clear();

}

int Board::minimax(std::vector<std::vector<char>> game_board, int depth, int alpha, int beta, bool maximizing_player, char player, int& selection, bool first_time){
	int max_eval, min_eval, eval;
	//int max_idx, min_idx;
	int child_num = 0;
	int col;

	std::vector<std::vector<char>> child;

	if(depth==0 || find_winner() == 'H' || find_winner() == 'M'){
		//return fitnesss of gameboard
		return h_eval(player);// needed the player perameter just for this
	}
	if(maximizing_player){
		max_eval = neg_inf;
		if(!first_time){
			if(player == 'H'){
				player = 'M';
			}else{
				player = 'H';
			}
		}
		//for each child, could be while loop
		//for(int i=0; i<7; i++){
		while(child_num<7){
			col = rand()%7;
			child = child_board(game_board, col, player, true);
			//this is to prevent an infinate loop of trying to pick the column that is already 6 high
			if(try_again){
				//invalid_children.push_back(child_num);//not really using this though
				try_again = false;
				eval = neg_inf;
			}else{
				eval = minimax(child, depth-1, alpha, beta, false, player, selection, false);//going recursive to the leaf
			}
			child_num++;
			if(eval > max_eval){
				max_eval = eval;
				selection = col;
			}
			if(eval > alpha){
				alpha = eval;
			}
			if(beta <= alpha){
				break;
			}
		}
		return max_eval;
		
	}else{
		
		min_eval = inf;
		if(player == 'H'){
			player = 'M';
		}else{
			player = 'H';
		}
		//for(int i=0; i<7; i++){
		while(child_num<7){
			col = rand()%7;
			child = child_board(game_board, col, player, true);
			if(try_again){
				//invalid_children.push_back(child_num);
				try_again = false;
				eval = inf;
			}else{
				eval = minimax(child, depth-1, alpha, beta, true, player, selection, false);
			}
			child_num++;
			if(eval < min_eval){
				min_eval = eval;
				selection = col;
			}
			if(eval < beta){
				beta = eval;
			}
			if(beta <= alpha){
				break;
			}
		}
		return min_eval;
	}
		
	
}

//h_eval serves the following purpose
//	Uses a score to determine the best / worst moves instead of finding the end state of the game.
//	This is due to connect4's complex nature as compared to other minimax type games.
//	Input will be the player and the return will be the highest number
//		This number indicates the longest string of X's or O's in a row,
//		and the for loops already check for the board size
//	Theorhetically, minimax will be able to tell if the next move will increase this score for itself or
//	decrease this score for the player

int Board::h_eval(char player){
	int value = 0;
	int global_value = 0;
	if(player == 'H'){
		//horizontal right check
		for(int j=0; j<game_board.size(); j++){
			for(int i=0; i<game_board[0].size()-3; i++){
				if(game_board[j][i] == 'X' && game_board[j][i+1] != 'O' && game_board[j][i+2] != 'O' && game_board[j][i+3] != 'O'){
					value=1;
					if(game_board[j][i+1] == 'X' && game_board[j][i+2] != 'O' && game_board[j][i+3] != 'O'){
						value=2;
						if(game_board[j][i+2] == 'X' && game_board[j][i+3] != 'O') {
							value=3;
							if(game_board[j][i+3] == 'X'){
								value=4;
							}
						}
					}
				}
			}
		}
		if(value > global_value){
			global_value = value;
		}
		//horizontal left check
		for(int j=0; j<game_board.size(); j++){
			for(int i=3; i<game_board[0].size(); i++){
				if(game_board[j][i] == 'X' && game_board[j][i-1] != 'O' && game_board[j][i-2] != 'O' && game_board[j][i-3] != 'O'){
					value=1;
					if(game_board[j][i-1] == 'X' && game_board[j][i-2] != 'O' && game_board[j][i-3] != 'O'){
						value=2;
						if(game_board[j][i-2] == 'X' && game_board[j][i-3] != 'O') {
							value=3;
							if(game_board[j][i-3] == 'X'){
								value=4;
							}
						}
					}
				}
			}
		}
		if(value > global_value){
			global_value = value;
		}
		//vertical up check
		for(int j=0; j<game_board[0].size(); j++){
			for(int i=3; i<game_board.size(); i++){
				if(game_board[i][j] == 'X' && game_board[i-1][j] != 'O' && game_board[i-2][j] != 'O' && game_board[i-3][j] != 'O'){
					value=1;
					if(game_board[i-1][j] == 'X' && game_board[i-2][j] != 'O' && game_board[i-3][j] != 'O'){
						value=2;
						if(game_board[i-2][j] == 'X' && game_board[i-3][j] != 'O') {
							value=3;
							if(game_board[i-3][j] == 'X'){
								value=4;
							}
						}
					}
				}
			}
		}
		if(value > global_value){
			global_value = value;
		}
		//vetical down check
		for(int j=0; j<game_board[0].size(); j++){
			for(int i=0; i<game_board.size()-3; i++){
				if(game_board[i][j] == 'X' && game_board[i+1][j] != 'O' && game_board[i+2][j] != 'O' && game_board[i+3][j] != 'O'){
					value=1;
					if(game_board[i+1][j] == 'X' && game_board[i+2][j] != 'O' && game_board[i+3][j] != 'O'){
						value=2;
						if(game_board[i+2][j] == 'X' && game_board[i+3][j] != 'O') {
							value=3;
							if(game_board[i+3][j] == 'X'){
								value=4;
							}
						}
					}
				}
			}
		}
		if(value > global_value){
			global_value = value;
		}
		//diagonal up check
		for(int j=3; j<game_board.size(); j++){
			for(int i=0; i<game_board[0].size()-3; i++){
				if(game_board[j][i] == 'X' && game_board[j-1][i+1] != 'O' && game_board[j-2][i+2] != 'O' && game_board[j-3][i+3] != 'O'){
					value=1;
					if(game_board[j-1][i+1] == 'X' && game_board[j-2][i+2] != 'O' && game_board[j-3][i+3] != 'O'){
						value=2;
						if(game_board[j-2][i+2] == 'X' && game_board[j-3][i+3] != 'O') {
							value=3;
							if(game_board[j-3][i+3] == 'X'){
								value=4;
							}
						}
					}
				}
			}
		}
		if(value > global_value){
			global_value = value;
		}
		//diagonal down check
		for(int j=3; j<game_board.size(); j++){
			for(int i=3; i<game_board[0].size()-3; i++){
				if(game_board[j][i] == 'X' && game_board[j-1][i-1] != 'O' && game_board[j-2][i-2] != 'O' && game_board[j-3][i-3] != 'O'){
					value=1;
					if(game_board[j-1][i-1] == 'X' && game_board[j-2][i-2] != 'O' && game_board[j-3][i-3] != 'O'){
						value=2;
						if(game_board[j-2][i-2] == 'X' && game_board[j-3][i-3] != 'O') {
							value=3;
							if(game_board[j-3][i-3] == 'X'){
								value=4;
							}
						}
					}
				}
			}
		}
	
		return global_value;
		
	}else{//same thing but with 'O' instead of 'X'
		//horizontal right check
		for(int j=0; j<game_board.size(); j++){
			for(int i=0; i<game_board[0].size()-3; i++){
				if(game_board[j][i] == 'O' && game_board[j][i+1] != 'X' && game_board[j][i+2] != 'X' && game_board[j][i+3] != 'X'){
					value=1;
					if(game_board[j][i+1] == 'O' && game_board[j][i+2] != 'X' && game_board[j][i+3] != 'X'){
						value=2;
						if(game_board[j][i+2] == 'O' && game_board[j][i+3] != 'X') {
							value=3;
							if(game_board[j][i+3] == 'O'){
								value=4;
							}
						}
					}
				}
			}
		}
		if(value > global_value){
			global_value = value;
		}
		//horizontal left check
		for(int j=0; j<game_board.size(); j++){
			for(int i=3; i<game_board[0].size(); i++){
				if(game_board[j][i] == 'O' && game_board[j][i-1] != 'X' && game_board[j][i-2] != 'X' && game_board[j][i-3] != 'X'){
					value=1;
					if(game_board[j][i-1] == 'O' && game_board[j][i-2] != 'X' && game_board[j][i-3] != 'X'){
						value=2;
						if(game_board[j][i-2] == 'O' && game_board[j][i-3] != 'X') {
							value=3;
							if(game_board[j][i-3] == 'O'){
								value=4;
							}
						}
					}
				}
			}
		}
		if(value > global_value){
			global_value = value;
		}
		//vertical up check
		for(int j=0; j<game_board[0].size(); j++){
			for(int i=3; i<game_board.size(); i++){
				if(game_board[i][j] == 'O' && game_board[i-1][j] != 'X' && game_board[i-2][j] != 'X' && game_board[i-3][j] != 'X'){
					value=1;
					if(game_board[i-1][j] == 'O' && game_board[i-2][j] != 'X' && game_board[i-3][j] != 'X'){
						value=2;
						if(game_board[i-2][j] == 'O' && game_board[i-3][j] != 'X') {
							value=3;
							if(game_board[i-3][j] == 'O'){
								value=4;
							}
						}
					}
				}
			}
		}
		if(value > global_value){
			global_value = value;
		}
		//vetical down check
		for(int j=0; j<game_board[0].size(); j++){
			for(int i=0; i<game_board.size()-3; i++){
				if(game_board[i][j] == 'O' && game_board[i+1][j] != 'X' && game_board[i+2][j] != 'X' && game_board[i+3][j] != 'X'){
					value=1;
					if(game_board[i+1][j] == 'O' && game_board[i+2][j] != 'X' && game_board[i+3][j] != 'X'){
						value=2;
						if(game_board[i+2][j] == 'O' && game_board[i+3][j] != 'X') {
							value=3;
							if(game_board[i+3][j] == 'O'){
								value=4;
							}
						}
					}
				}
			}
		}
		if(value > global_value){
			global_value = value;
		}
		//diagonal up check
		for(int j=3; j<game_board.size(); j++){
			for(int i=0; i<game_board[0].size()-3; i++){
				if(game_board[j][i] == 'O' && game_board[j-1][i+1] != 'X' && game_board[j-2][i+2] != 'X' && game_board[j-3][i+3] != 'X'){
					value=1;
					if(game_board[j-1][i+1] == 'O' && game_board[j-2][i+2] != 'X' && game_board[j-3][i+3] != 'X'){
						value=2;
						if(game_board[j-2][i+2] == 'O' && game_board[j-3][i+3] != 'X') {
							value=3;
							if(game_board[j-3][i+3] == 'O'){
								value=4;
							}
						}
					}
				}
			}
		}
		if(value > global_value){
			global_value = value;
		}
		//diagonal down check
		for(int j=3; j<game_board.size(); j++){
			for(int i=3; i<game_board[0].size()-3; i++){
				if(game_board[j][i] == 'O' && game_board[j-1][i-1] != 'X' && game_board[j-2][i-2] != 'X' && game_board[j-3][i-3] != 'X'){
					value=1;
					if(game_board[j-1][i-1] == 'O' && game_board[j-2][i-2] != 'X' && game_board[j-3][i-3] != 'X'){
						value=2;
						if(game_board[j-2][i-2] == 'O' && game_board[j-3][i-3] != 'X') {
							value=3;
							if(game_board[j-3][i-3] == 'O'){
								value=4;
							}
						}
					}
				}
			}
		}
		if(value > global_value){
			global_value = value;
		}
	
		return global_value;
	
	}
}

void Board::update_board(int col, char player, bool in_minimax) {
	for (int i = 0; i < game_board.size(); i++) {
		if (game_board[i][col] == '*') {
			if (i == 5 || game_board[i + 1][col] != '*') {
				if (player == 'H') {
					game_board[i][col] = 'X';
				}
				else {
					game_board[i][col] = 'O';
				}
				try_again = false;
				break;
			}
		}
		else {
			if (!in_minimax) {
				//std::cout << "\nYou Must Pick A Different Column\n\n";
			}
			try_again = true;
			break;
		}
	}
}

std::vector<std::vector<char>> Board::child_board(std::vector<std::vector<char>> game_board_child, int col, char player, bool in_minimax) {
	for (int i = 0; i < game_board_child.size(); i++) {
		if (game_board_child[i][col] == '*') {
			if (i == 5 || game_board_child[i + 1][col] != '*') {
				if (player == 'H') {
					game_board_child[i][col] = 'X';
				}
				else {
					game_board_child[i][col] = 'O';
				}
				try_again = false;
				break;
			}
		}
		else {
			if (!in_minimax) {
				std::cout << "\nYou Must Pick A Different Column\n\n";
			}
			try_again = true;
			break;
		}
	}
	return game_board_child;
}

