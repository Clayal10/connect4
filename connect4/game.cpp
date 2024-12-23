#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<cmath>

#include "game_board.h"

using namespace std;

#define inf numeric_limits<int>::max()
#define neg_inf -numeric_limits<int>::max()

char up_next = 'H'; //start with human

//TODO
//	-Clean up the main function
//		-turn it in to a proper function that can be called in a main.cpp which
//		 will be called every frame when I impliment openGL
//	-Clean up minimax
//		-Don't make it too intensive but maybe make a proper minimax function.
//		 This can be difficult since connect 4 has so many possibilities but we will try!


int main() {
	srand((unsigned int)time(0));
	Board* board = new Board();
	

	//human vs ai or ai vs ai
	int game_mode;
	vector<vector<int>> moves;
choice:
	cout << "Human VS AI or AI VS AI (0 or 1 respectively): ";
	cin >> game_mode;

	if(game_mode == 0){
	
		//print the board for the first time
		cout << "Welcome to Connect 4 (Human = X, Machine = O)\n";
		cout << "=======================================\n\n";
		board->print_board();
		
		vector<int> move(2);
		int selection;
		int selection_val;
		char winner = 'Z';
	
		//This is the main loop
		while(winner == 'Z'){//this is terminal state checking
			//just do this section every other time (the other time will be AI)
			if(up_next == 'H'){
				cout << "Pick a Column for your move: ";
				cin >> selection;
				move[0] = 1;
				move[1] = selection;
				moves.push_back(move);
			}else{
				//stuff for ai
				selection_val = board->minimax(board->game_board, 5, neg_inf, inf, true, 'M', selection, true); //this perameter is the state after the user goes
				move[0] = 2;
				move[1] = selection;
				moves.push_back(move);
			}
	
			board->update_board(selection, up_next, false);
			if(try_again){
				continue;
			}
			board->print_board();
			
			//swap who goes next
			if(up_next == 'H')
				up_next = 'M';
			else
				up_next = 'H';
	
			winner = board->find_winner();
		}
	
		//winner has been found after here
		cout << "\n\nWinner is: " << winner << "\n\n";
	
	} else if(game_mode == 1){
		//AI vs AI
		int game_num = 0;
		while(game_num < 5){
		
		game_num++;
		char winner = 'Z';//H is first ai, M is second
		int selection;
		int selection_val;
		vector<int> move(2);
		while(winner == 'Z'){
			if(up_next == 'H'){
				selection_val = board->minimax(board->game_board, 5, neg_inf, inf, true, 'H', selection, true);//dont think i actually need this value
				move[0] = 1;
				move[1] = selection;
				moves.push_back(move);
			}else{
				//stuff for ai
				selection_val = board->minimax(board->game_board, 5, neg_inf, inf, true, 'M', selection, true); //this perameter is the state after the user goes
				move[0] = 2;
				move[1] = selection;
				moves.push_back(move);
			}
	
			board->update_board(selection, up_next, false);
			if(try_again){
				continue;
			}
			board->print_board();
			
			//swap who goes next
			if(up_next == 'H')
				up_next = 'M';
			else
				up_next = 'H';
	
			winner = board->find_winner();
			
		}
		int ai_winner;
		if(winner == 'H'){
			ai_winner = 1;
		}else{
			ai_winner = 2;
		}

		cout << "Winner is: " << ai_winner << endl;
	
		board->reset_board();
		moves.clear();
	
		}
	
	}else{
		cout << "\n\nSelect Again\n\n";
		goto choice;
	}

	
	return 0;
}

int Board::minimax(vector<vector<char>> game_board, int depth, int alpha, int beta, bool maximizing_player, char player, int& selection, bool first_time){
	int max_eval, min_eval, eval;
	//int max_idx, min_idx;
	int child_num = 0;
	int col;

	vector<vector<char>> child;

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
		//for(int i=0; i<children_states.size(); i++){
		while(child_num<7){
			col = rand()%6;
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
		//for(int i=0; i<children_states.size(); i++){
		while(child_num<7){
			col = rand()%6;
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
				selection = child_num;
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

int Board::h_eval(char player){
	//rearrange the if statments to be nested and add 1 point for each level or something like that.
	int value=0;
/*The current setup is only rewarding very selfishly, need to block the opponent as well*/
if(player == 'H'){
	//horizontal right check
	for(int j=0; j<game_board.size(); j++){
		for(int i=0; i<game_board[0].size()-3; i++){
			if(game_board[j][i] == 'X' && game_board[j][i+1] != 'O' && game_board[j][i+2] != 'O' && game_board[j][i+3] != 'O'){
				value++;
				if(game_board[j][i+1] == 'X' && game_board[j][i+2] != 'O' && game_board[j][i+3] != 'O'){
					value+=2;
					if(game_board[j][i+2] == 'X' && game_board[j][i+3] != 'O') {
						value+=3;
						if(game_board[j][i+3] == 'X'){
							value+=4;
						}
					}
				}
			}
		}
	}
	//horizontal left check
	for(int j=0; j<game_board.size(); j++){
		for(int i=3; i<game_board[0].size(); i++){
			if(game_board[j][i] == 'X' && game_board[j][i-1] != 'O' && game_board[j][i-2] != 'O' && game_board[j][i-3] != 'O'){
				value++;
				if(game_board[j][i-1] == 'X' && game_board[j][i-2] != 'O' && game_board[j][i-3] != 'O'){
					value+=2;
					if(game_board[j][i-2] == 'X' && game_board[j][i-3] != 'O') {
						value+=3;
						if(game_board[j][i-3] == 'X'){
							value+=4;
						}
					}
				}
			}
		}
	}
	//vertical up check
	for(int j=0; j<game_board[0].size(); j++){
		for(int i=3; i<game_board.size(); i++){
			if(game_board[i][j] == 'X' && game_board[i-1][j] != 'O' && game_board[i-2][j] != 'O' && game_board[i-3][j] != 'O'){
				value++;
				if(game_board[i-1][j] == 'X' && game_board[i-2][j] != 'O' && game_board[i-3][j] != 'O'){
					value+=2;
					if(game_board[i-2][j] == 'X' && game_board[i-3][j] != 'O') {
						value+=3;
						if(game_board[i-3][j] == 'X'){
							value+=4;
						}
					}
				}
			}
		}
	}
	//vetical down check
	for(int j=0; j<game_board[0].size(); j++){
		for(int i=0; i<game_board.size()-3; i++){
			if(game_board[i][j] == 'X' && game_board[i+1][j] != 'O' && game_board[i+2][j] != 'O' && game_board[i+3][j] != 'O'){
				value++;
				if(game_board[i+1][j] == 'X' && game_board[i+2][j] != 'O' && game_board[i+3][j] != 'O'){
					value+=2;
					if(game_board[i+2][j] == 'X' && game_board[i+3][j] != 'O') {
						value+=3;
						if(game_board[i+3][j] == 'X'){
							value+=4;
						}
					}
				}
			}
		}
	}
	//diagonal up check
	for(int j=3; j<game_board.size(); j++){
		for(int i=0; i<game_board[0].size()-3; i++){
			if(game_board[j][i] == 'X' && game_board[j-1][i+1] != 'O' && game_board[j-2][j+2] != 'O' && game_board[j-3][j+3] != 'O'){
				value++;
				if(game_board[j-1][i+1] == 'X' && game_board[j-2][i+2] != 'O' && game_board[j-3][i+3] != 'O'){
					value+=2;
					if(game_board[j-2][i+2] == 'X' && game_board[j-3][i+3] != 'O') {
						value+=3;
						if(game_board[j-3][i+3] == 'X'){
							value+=4;
						}
					}
				}
			}
		}
	}
	//diagonal down check
	for(int j=3; j<game_board.size(); j++){
		for(int i=3; i<game_board[0].size()-3; i++){
			if(game_board[j][i] == 'X' && game_board[j-1][i-1] != 'O' && game_board[j-2][i-2] != 'O' && game_board[j-3][i-3] != 'O'){
				value++;
				if(game_board[j-1][i-1] == 'X' && game_board[j-2][i-2] != 'O' && game_board[j-3][i-3] != 'O'){
					value+=2;
					if(game_board[j-2][i-2] == 'X' && game_board[j-3][i-3] != 'O') {
						value+=3;
						if(game_board[j-3][i-3] == 'X'){
							value+=4;
						}
					}
				}
			}
		}
	}

	return value;
	
}else{//same thing but with 'O' instead of 'X'
	//horizontal right check
	for(int j=0; j<game_board.size(); j++){
		for(int i=0; i<game_board[0].size()-3; i++){
			if(game_board[j][i] == 'O' && game_board[j][i+1] != 'X' && game_board[j][i+2] != 'X' && game_board[j][i+3] != 'X'){
				value++;
				if(game_board[j][i+1] == 'O' && game_board[j][i+2] != 'X' && game_board[j][i+3] != 'X'){
					value+=2;
					if(game_board[j][i+2] == 'O' && game_board[j][i+3] != 'X') {
						value+=3;
						if(game_board[j][i+3] == 'O'){
							value+=4;
						}
					}
				}
			}
		}
	}
	//horizontal left check
	for(int j=0; j<game_board.size(); j++){
		for(int i=3; i<game_board[0].size(); i++){
			if(game_board[j][i] == 'O' && game_board[j][i-1] != 'X' && game_board[j][i-2] != 'X' && game_board[j][i-3] != 'X'){
				value++;
				if(game_board[j][i-1] == 'O' && game_board[j][i-2] != 'X' && game_board[j][i-3] != 'X'){
					value+=2;
					if(game_board[j][i-2] == 'O' && game_board[j][i-3] != 'X') {
						value+=3;
						if(game_board[j][i-3] == 'O'){
							value+=4;
						}
					}
				}
			}
		}
	}
	//vertical up check
	for(int j=0; j<game_board[0].size(); j++){
		for(int i=3; i<game_board.size(); i++){
			if(game_board[i][j] == 'O' && game_board[i-1][j] != 'X' && game_board[i-2][j] != 'X' && game_board[i-3][j] != 'X'){
				value++;
				if(game_board[i-1][j] == 'O' && game_board[i-2][j] != 'X' && game_board[i-3][j] != 'X'){
					value+=2;
					if(game_board[i-2][j] == 'O' && game_board[i-3][j] != 'X') {
						value+=3;
						if(game_board[i-3][j] == 'O'){
							value+=4;
						}
					}
				}
			}
		}
	}
	//vetical down check
	for(int j=0; j<game_board[0].size(); j++){
		for(int i=0; i<game_board.size()-3; i++){
			if(game_board[i][j] == 'O' && game_board[i+1][j] != 'X' && game_board[i+2][j] != 'X' && game_board[i+3][j] != 'X'){
				value++;
				if(game_board[i+1][j] == 'O' && game_board[i+2][j] != 'X' && game_board[i+3][j] != 'X'){
					value+=2;
					if(game_board[i+2][j] == 'O' && game_board[i+3][j] != 'X') {
						value+=3;
						if(game_board[i+3][j] == 'O'){
							value+=4;
						}
					}
				}
			}
		}
	}
	//diagonal up check
	for(int j=3; j<game_board.size(); j++){
		for(int i=0; i<game_board[0].size()-3; i++){
			if(game_board[j][i] == 'O' && game_board[j-1][i+1] != 'X' && game_board[j-2][i+2] != 'X' && game_board[j-3][i+3] != 'X'){
				value++;
				if(game_board[j-1][i+1] == 'O' && game_board[j-2][i+2] != 'X' && game_board[j-3][i+3] != 'X'){
					value+=2;
					if(game_board[j-2][i+2] == 'O' && game_board[j-3][i+3] != 'X') {
						value+=3;
						if(game_board[j-3][i+3] == 'O'){
							value+=4;
						}
					}
				}
			}
		}
	}
	//diagonal down check
	for(int j=3; j<game_board.size(); j++){
		for(int i=3; i<game_board[0].size()-3; i++){
			if(game_board[j][i] == 'O' && game_board[j-1][i-1] != 'X' && game_board[j-2][i-2] != 'X' && game_board[j-3][i-3] != 'X'){
				value++;
				if(game_board[j-1][i-1] == 'O' && game_board[j-2][i-2] != 'X' && game_board[j-3][i-3] != 'X'){
					value+=2;
					if(game_board[j-2][i-2] == 'O' && game_board[j-3][i-3] != 'X') {
						value+=3;
						if(game_board[j-3][i-3] == 'O'){
							value+=4;
						}
					}
				}
			}
		}
	}

	return value;

}
}

