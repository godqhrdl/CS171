#include "AIShell.h"
#include <iostream>
#include <queue>


#define LIMITED_DEPTH 4


AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline = 0;
	this->numRows = numRows;
	this->numCols = numCols;
	this->gravityOn = gravityOn;
	this->gameState = gameState;
	this->lastMove = lastMove;


	this->AIMove = true;
	this->best_move.first = 0;
	this->best_move.second = 0;
	this->total_pieces = 0;
}


AIShell::~AIShell()
{

	//delete the gameState variable.
	for (int i = 0; i<numCols; i++){
		delete[] gameState[i];
	}
	delete[] gameState;

}

Move AIShell::makeMove(){
	//this part should be filled in by the student to implement the AI
	//Example of a move could be: Move move(1, 2); //this will make a move at col 1, row 2

	//std::queue<std::pair<int, int> > all_avalible_move;
	//find_all_avl(all_avalible_move);

	//evalutate(gameState);

	//Minimax search
	//minimax_search(gameState, LIMITED_DEPTH);
	//alpha_beta_pruning(gameState, -9999999, 9999999, LIMITED_DEPTH, true);
	start_time = std::chrono::steady_clock::now();
	iterative_deepening_alpha_beta(gameState);



	Move f(final_best_move.first, final_best_move.second);
	end_time = std::chrono::steady_clock::now();
	std::cout << "Final move: " << best_move.first << "," << best_move.second << std::endl;
	std::cout << "Elapsed Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << "miliseconds" << std::endl;
	return f;


}

//void print_all_aval(std::queue<std::pair<int,int> > all){}

//Test if a node is a terminal node
bool AIShell::test_terminal_node(int **current_state){

	return no_empty_space(current_state) || test_horizontal(current_state) || test_vertical(current_state) || test_diagonal(current_state);
}

bool AIShell::test_horizontal(int **current_state){
	for (int row = 0; row<numRows; row++){
		int count_ai = 0, count_hm = 0;
		for (int col = 0; col<numCols; col++){
			if (current_state[col][row] == 1){
				count_ai++;
				count_hm = 0;
			}
			if (current_state[col][row] == 0){
				count_ai = 0;
				count_hm = 0;
			}
			if (current_state[col][row] == -1){
				count_ai = 0;
				count_hm++;
			}
		}

		if (count_hm == k || count_ai == k){
			//std::cout << "find horizontal winner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			//std::cout << "------------------TEST LINE-----------------" << std::endl;
			return true;
		}
	}

	return false;
}

bool AIShell::test_vertical(int **current_state){
	for (int col = 0; col<numCols; col++){
		int count_ai = 0, count_hm = 0;
		for (int row = 0; row<numRows; row++){
			if (current_state[col][row] == 1){
				count_ai++;
				count_hm = 0;
			}
			if (current_state[col][row] == 0){
				count_ai = 0;
				count_hm = 0;
			}
			if (current_state[col][row] == -1){
				count_ai = 0;
				count_hm++;
			}
		}

		if (count_hm == k || count_ai == k){
			//std::cout << "find vertical winner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			return true;
		}
	}

	return false;
}

bool AIShell::test_diagonal(int **current_state){

	//Left bottom corner to right top corner
	for (int row = 0; row <= numRows - k; row++){
		int count_ai = 0, count_hm = 0;
		int c = 0, r = row;
		for (; c<numCols && r<numRows; c++, r++){
			if (current_state[c][r] == 1){
				count_ai++;
				count_hm = 0;
			}
			if (current_state[c][r] == 0){
				count_ai = 0;
				count_hm = 0;
			}
			if (current_state[c][r] == -1){
				count_ai = 0;
				count_hm++;
			}
		}
		if (count_hm == k || count_ai == k){
			//std::cout << "find diagonal winner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			return true;
		}
	}

	for (int col = 0; col <= numCols - k; col++){
		int count_ai = 0, count_hm = 0;
		int c = col, r = 0;
		for (; c<numCols && r<numRows; c++, r++){
			if (current_state[c][r] == 1){
				count_ai++;
				count_hm = 0;
			}
			if (current_state[c][r] == 0){
				count_ai = 0;
				count_hm = 0;
			}
			if (current_state[c][r] == -1){
				count_ai = 0;
				count_hm++;
			}

		}
		if (count_hm == k || count_ai == k){
			//std::cout << "find diagonal winner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			return true;
		}
	}

	//Left top corner to right bottom corner
	for (int row = numRows - 1; row + 1 >= k; row--){
		int count_ai = 0, count_hm = 0;
		int c = 0, r = row;
		for (; c<numCols && r >= 0; c++, r--){
			if (current_state[c][r] == 1){
				count_ai++;
				count_hm = 0;
			}
			if (current_state[c][r] == 0){
				count_ai = 0;
				count_hm = 0;
			}
			if (current_state[c][r] == -1){
				count_ai = 0;
				count_hm++;
			}
		}
		if (count_hm == k || count_ai == k){
			//std::cout << "find diagonal winner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			return true;
		}
	}

	for (int col = 0; col <= numCols - k; col++){
		int count_ai = 0, count_hm = 0;
		int c = col, r = numRows - 1;
		for (; c<numCols && r >= 0; c++, r--){
			if (current_state[c][r] == 1){
				count_ai++;
				count_hm = 0;
			}
			if (current_state[c][r] == 0){
				count_ai = 0;
				count_hm = 0;
			}
			if (current_state[c][r] == -1){
				count_ai = 0;
				count_hm++;
			}
		}
		if (count_hm == k || count_ai == k){
			//std::cout << "find diagonal winner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			return true;
		}
	}


	return false;
}

//If no empty space return true, otherwise return false.
bool AIShell::no_empty_space(int **current_state){
	for (int col = 0; col<numCols; col++){
		for (int row = 0; row<numRows; row++){
			if (current_state[col][row] == NO_PIECE)
				return false;
		}
	}
	return true;
}


//Iterative Deepening Search
int AIShell::iterative_deepening_alpha_beta(int **current_state){
	//Time limit
	//start = clock();
	end_time = std::chrono::steady_clock::now(); 
	ids_depth = 0;
	//auto elapsed_time = end_time - start_time;
	//std::cout << "Elapsed Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count << "miliseconds" << std::endl;
	while (std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() < deadline*0.95){

		std::cout << "Current depth:" << ids_depth << std::endl;
		alpha_beta_pruning(current_state, -9999999, 9999999, ids_depth, true);
		ids_depth++;
		end_time = std::chrono::steady_clock::now();
	}
	std::cout << "END" << std::endl;

	//Iterative Deepening


	return 0;
}

//Alpha-beta pruning
int AIShell::alpha_beta_pruning(int **current_state, int alpha, int beta, int depth, bool ai_play){
	if (depth == 0 || test_terminal_node(current_state))
		return evalutate(current_state);

	if (AIMove == true)
		return max_search(depth, alpha, beta);
	else
		return min_search(depth, alpha, beta);

}


//Minimax Search Algorithm
//int AIShell::minimax_search(int **current_state, int depth){
//    //Test if is leaf node or at limited depth
//    if(test_terminal_node(current_state) || depth < 0)
//        return evalutate(current_state);
//    
//    if(AIMove == true)
//        return max_search(depth);
//    else
//        return min_search(depth);
//    
//}

//Max function for Minimax Search
int AIShell::max_search(int depth, int alpha, int beta){
	end_time = std::chrono::steady_clock::now();
	auto elapsed_time = end_time - start_time;

	int best = -9999999;
	//std::cout << "------------------TEST LINE-----------------" << std::endl;
	if (depth == 0 || test_terminal_node(gameState)){

		return evalutate(gameState);
	}

	//@@@@@@@@@@@@@@@@@@@@@@@@@
	if (std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count() >= deadline*0.95)
		return evalutate(gameState);


	std::queue<std::pair<int, int> > next_all; //A queue contains all availabe moves

	if (depth == ids_depth && ids_depth>1)
		next_all.push(final_best_move);

	find_all_avl(next_all);
	while (!next_all.empty()){
		//if ((clock() - start) * 1000 / CLOCKS_PER_SEC > 5000)
			//return evalutate(gameState);
		//std::cout << "**********Current Depth: " << LIMITED_DEPTH-depth << std::endl;

		std::pair<int, int> next = next_move(next_all, true);  //Make a move on the game board

		int v = min_search(depth - 1, alpha, beta);
		undo_move(next);  //Undo the move and restore the board

		end_time = std::chrono::steady_clock::now();
		auto elapsed_time = end_time - start_time;
		
		if (std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count() >= deadline*0.95)
			return evalutate(gameState);
		
		if (depth == ids_depth){
			//std::cout << "The current step is: " << "(" << next.first << "," << next.second << ")" << std::endl;
			//std::cout << "Depth:" << LIMITED_DEPTH - depth << "  MAX   ALPHA BETA V: " << alpha << "," << beta << "," << v << std::endl;
			if (v>best){
				//std::cout << "The best value is: " << best << std::endl;
				best_move.first = next.first;
				best_move.second = next.second;

			}
		}

		if (v > alpha)
			alpha = v;
		if (v > best)
			best = v;


		//std::cout << "Depth:" << LIMITED_DEPTH-depth <<"  MAX   ALPHA BETA V: " << alpha << "," << beta << "," << v << std::endl;
		if (beta <= alpha){
			//std::cout << "############Pruning  V:" << v << std::endl;
			return best;
		}



	}

	if (depth == ids_depth){
		final_best_move.first = best_move.first;
		final_best_move.second = best_move.second;
		std::cout << "Find final move@@@@@@@@@@@@@@@@@@@" << std::endl;
	}

	return best;
}

//Min function for Minimax Search.
int AIShell::min_search(int depth, int alpha, int beta){
	end_time = std::chrono::steady_clock::now();
	auto elapsed_time = end_time - start_time;

	int best = 9999999;
	//std::cout << "------------------TEST LINE-----------------" << std::endl;
	if (depth == 0 || test_terminal_node(gameState))
		return evalutate(gameState);

	if (std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count() >= deadline*0.95)
		return evalutate(gameState);

	std::queue<std::pair<int, int> > next_all; //A queue contains all available moves
	find_all_avl(next_all);
	while (!next_all.empty()){
		//if ((clock() - start) * 1000 / CLOCKS_PER_SEC > 5000)
			//return evalutate(gameState);
		//std::cout << "**********Current Depth: " << LIMITED_DEPTH-depth << std::endl;

		std::pair<int, int> next = next_move(next_all, false);
		int v = max_search(depth - 1, alpha, beta);
		undo_move(next);

		end_time = std::chrono::steady_clock::now();
		auto elapsed_time = end_time - start_time;

		if (std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count() >= deadline*0.95)
			return evalutate(gameState);

		if (v < beta)
			beta = v;
		if (v < best)
			best = v;
		//std::cout << "Depth:" << LIMITED_DEPTH-depth <<"   MIN   ALPHA BETA V: " << alpha << "," << beta << ","  << v << std::endl;
		if (alpha >= beta){
			//std::cout << "############Pruning  V:" << v << std::endl;
			return best;
		}
	}

	return best;
}

//AI will use this function while searching
std::pair<int, int> AIShell::next_move(std::queue<std::pair<int, int> > &all, bool aimove){
	std::pair<int, int> next = all.front(); //Find the next move
	all.pop(); //pop the next move from queue

	//    if(aimove == true)
	//        std::cout << "AI next move is: "<<next.first << "," << next.second << std::endl;
	//    else
	//        std::cout << "HM next move is: "<<next.first << "," << next.second << std::endl;
	gameState[next.first][next.second] = aimove ? 1 : -1;

	//print_current_state(gameState);

	return next;
}

void AIShell::undo_move(std::pair<int, int> p_move){
	gameState[p_move.first][p_move.second] = 0;
}


//Evaluate current state
int AIShell::evalutate(int **current_state){
	int result = 0;

//	result += horizontal_eval(current_state);
//	result += vertical_eval(current_state);
//	result += diagonal_eval(current_state);
    result += new_eval(current_state);


	//std::cout << "@@This is heuristic function: " << result << std::endl;

	return result;
}

int AIShell::new_eval(int **current_state){
    int result=0;
    
    for(int row=0; row<numRows; row++){
        for(int col=0; col<numCols; col++){
            //Horizontal ->
            
            if(col <= numCols-k){
                
                int ai_score = 0, hm_score=0,ai_pieces=0,hm_pieces=0;
                for (int i = 0; i<k; i++){
                    if (current_state[col + i][row] == 1){
                        ai_score += 5;
                        ai_pieces++;
                    }
                    if (current_state[col + i][row] == 0){
                        ai_score += 3;
                        hm_score -= 3;
                    }
                    if (current_state[col + i][row] == -1){
                        hm_score -= 5;
                        hm_pieces++;
                    }
                }
                
                int p_ai_pieces = ai_pieces;
                int p_hm_pieces = hm_pieces;
                
                if (p_ai_pieces != 0)
                    hm_score = 0;
                if (p_hm_pieces != 0)
                    ai_score = 0;
                
                
                
                ai_score *= ai_pieces;
                hm_score *= hm_pieces;
                if (ai_pieces == k){
                    ai_score = 1000;
                }
                if (hm_pieces == k){
                    hm_score = -1000;
                }
                
                result += ai_score;
                result += hm_score;
            }
            
            //Vertical |
            if(row <= numRows-k){
                int ai_score = 0, hm_score=0,ai_pieces=0,hm_pieces=0;
                for (int i = 0; i<k; i++){
                    if (current_state[col][row + i] == 1){
                        ai_score += 5;
                        ai_pieces++;
                    }
                    if (current_state[col][row + i] == 0){
                        ai_score += 3;
                        hm_score -= 3;
                    }
                    if (current_state[col][row + i] == -1){
                        hm_score -= 5;
                        hm_pieces++;
                    }
                }
                int p_ai_pieces = ai_pieces;
                int p_hm_pieces = hm_pieces;
                
                if (p_ai_pieces != 0)
                    hm_score = 0;
                if (p_hm_pieces != 0)
                    ai_score = 0;
                
                ai_score *= ai_pieces;
                hm_score *= hm_pieces;
                if (ai_pieces == k){
                    ai_score = 1000;
                }
                if (hm_pieces == k){
                    hm_score = -1000;
                }
                
                result += ai_score;
                result += hm_score;
            }
            
            // (/)
            if(col <= numCols-k && row <= numRows-k){
                int ai_score = 0, hm_score=0,ai_pieces=0,hm_pieces=0;
                
                for (int i = 0; i<k; i++){
                    if (current_state[col + i][row + i] == 1){
                        ai_score += 5;
                        ai_pieces++;
                    }
                    if (current_state[col + i][row + i] == 0){
                        ai_score += 3;
                        hm_score -= 3;
                    }
                    if (current_state[col + i][row + i] == -1){
                        hm_score -= 5;
                        hm_pieces++;
                    }
                }
                int p_ai_pieces = ai_pieces;
                int p_hm_pieces = hm_pieces;
                
                if (p_ai_pieces != 0)
                    hm_score = 0;
                if (p_hm_pieces != 0)
                    ai_score = 0;
                
                ai_score *= ai_pieces;
                hm_score *= hm_pieces;
                if (ai_pieces == k){
                    ai_score = 1000;
                }
                if (hm_pieces == k){
                    hm_score = -1000;
                }
                
                
                result += ai_score;
                result += hm_score;
            }
            
            //(\)
            if(row >= k-1 && col <= numCols-k){
                int ai_score = 0, hm_score=0,ai_pieces=0,hm_pieces=0;
                
                for (int i = 0; i<k; i++){
                    if (current_state[col + i][row - i] == 1){
                        ai_score += 5;
                        ai_pieces++;
                    }
                    if (current_state[col + i][row - i] == 0){
                        ai_score += 3;
                        hm_score -= 3;
                    }
                    if (current_state[col + i][row - i] == -1){
                        hm_score -= 5;
                        hm_pieces++;
                    }
                }
                int p_ai_pieces = ai_pieces;
                int p_hm_pieces = hm_pieces;
                
                if (p_ai_pieces != 0)
                    hm_score = 0;
                if (p_hm_pieces != 0)
                    ai_score = 0;
                
                ai_score *= ai_pieces;
                hm_score *= hm_pieces;
                if (ai_pieces == k){
                    ai_score = 1000;
                }
                if (hm_pieces == k){
                    hm_score = -1000;
                }
                
                result += ai_score;
                result += hm_score;
            }
            
        }
    }
    return result;
}


int AIShell::horizontal_eval(int **current_state){
	int ai_result = 0, hm_result = 0;

	//Score for each AI piece is 100, empty space is 5
	//Score for each HM piece is -100, empty space is -5
	for (int row = 0; row<numRows; row++){
		for (int col = 0; col <= numCols - k; col++){
			int ai_score = 0, hm_score = 0, ai_pieces = 0, hm_pieces = 0;
			//int k_pieces[k];

			for (int i = 0; i<k; i++){
				if (current_state[col + i][row] == 1){
					ai_score += 5;
					ai_pieces++;
				}
				if (current_state[col + i][row] == 0){
					ai_score += 3;
					hm_score -= 3;
				}
				if (current_state[col + i][row] == -1){
					hm_score -= 5;
					hm_pieces++;
				}
			}
            
            int p_ai_pieces = ai_pieces;
            int p_hm_pieces = hm_pieces;
            
			if (p_ai_pieces != 0)
				hm_score = 0;
			if (p_hm_pieces != 0)
				ai_score = 0;
            
            

			ai_score *= ai_pieces;
			hm_score *= hm_pieces;
			if (ai_pieces == k){
				ai_score = 1000;
			}
			if (hm_pieces == k){
				hm_score = -1000;
			}

			ai_result += ai_score;
			hm_result += hm_score;


		}
	}

	return ai_result + hm_result;
}

int AIShell::vertical_eval(int **current_state){
	int ai_result = 0, hm_result = 0;

	for (int col = 0; col<numCols; col++){
		for (int row = 0; row <= numRows - k; row++){
			int ai_score = 0, hm_score = 0, ai_pieces = 0, hm_pieces = 0;

			for (int i = 0; i<k; i++){
				if (current_state[col][row + i] == 1){
					ai_score += 5;
					ai_pieces++;
				}
				if (current_state[col][row + i] == 0){
					ai_score += 3;
					hm_score -= 3;
				}
				if (current_state[col][row + i] == -1){
					hm_score -= 5;
					hm_pieces++;
				}
			}
            int p_ai_pieces = ai_pieces;
            int p_hm_pieces = hm_pieces;
            
            if (p_ai_pieces != 0)
                hm_score = 0;
            if (p_hm_pieces != 0)
                ai_score = 0;
            
			ai_score *= ai_pieces;
			hm_score *= hm_pieces;
			if (ai_pieces == k){
				ai_score = 1000;
			}
			if (hm_pieces == k){
				hm_score = -1000;
			}

			ai_result += ai_score;
			hm_result += hm_score;
		}
	}

	return ai_result + hm_result;
}


int AIShell::diagonal_eval(int **current_state){
	int ai_result = 0, hm_result = 0;

	// (/)
	for (int col = 0; col <= numCols - k; col++){
		for (int row = 0; row <= numRows - k; row++){
			int ai_score = 0, hm_score = 0, ai_pieces = 0, hm_pieces = 0;

			for (int i = 0; i<k; i++){
				if (current_state[col + i][row + i] == 1){
					ai_score += 5;
					ai_pieces++;
				}
				if (current_state[col + i][row + i] == 0){
					ai_score += 3;
					hm_score -= 3;
				}
				if (current_state[col + i][row + i] == -1){
					hm_score -= 5;
					hm_pieces++;
				}
			}
            int p_ai_pieces = ai_pieces;
            int p_hm_pieces = hm_pieces;
            
            if (p_ai_pieces != 0)
                hm_score = 0;
            if (p_hm_pieces != 0)
                ai_score = 0;
            
			ai_score *= ai_pieces;
			hm_score *= hm_pieces;
			if (ai_pieces == k){
				ai_score = 1000;
			}
			if (hm_pieces == k){
				hm_score = -1000;
			}


			ai_result += ai_score;
			hm_result += hm_score;
		}

	}


	// (\)
	for (int col = 0; col <= numCols - k; col++){
		for (int row = numRows - 1; row + 1 >= k; row--){
			int ai_score = 0, hm_score = 0, ai_pieces = 0, hm_pieces = 0;

			for (int i = 0; i<k; i++){
				if (current_state[col + i][row - i] == 1){
					ai_score += 5;
					ai_pieces++;
				}
				if (current_state[col + i][row - i] == 0){
					ai_score += 3;
					hm_score -= 3;
				}
				if (current_state[col + i][row - i] == -1){
					hm_score -= 5;
					hm_pieces++;
				}
			}
            int p_ai_pieces = ai_pieces;
            int p_hm_pieces = hm_pieces;
            
            if (p_ai_pieces != 0)
                hm_score = 0;
            if (p_hm_pieces != 0)
                ai_score = 0;
            
			ai_score *= ai_pieces;
			hm_score *= hm_pieces;
			if (ai_pieces == k){
				ai_score = 1000;
			}
			if (hm_pieces == k){
				hm_score = -1000;
			}

			ai_result += ai_score;
			hm_result += hm_score;
		}
	}

	return ai_result + hm_result;
}



/*
This function will find all available move
The first part will find all available move when gavity is on
The second part will find all available move when gavity is off
Put in a queue, First in first out
*/
void AIShell::find_all_avl(std::queue<std::pair<int, int> > &all){
	//std::cout << "Available moves: " << std::endl;
	if (gravityOn == true){
		for (int col = 0; col<numCols; col++){
			for (int row = 0; row<numRows; row++){
				if (gameState[col][row] == NO_PIECE){
					//std::cout << " (" << col << "," << row << ")" ;
					std::pair<int, int> now;
					now = std::make_pair(col, row);
					all.push(now);
					//std::cout << " (" << all.back().first << "," << all.back().second << ")";
					break;
				}
			}
		}
	}
	else{
		for (int col = 0; col<numCols; col++){
			for (int row = 0; row<numRows; row++){
				if (gameState[col][row] == NO_PIECE){
					//std::cout << " (" << col << "," << row << ")" ;

					//Changed$$$$$$$$$$$$$$

					std::pair<int, int> now;
					now = std::make_pair(col, row);
					all.push(now);
					//std::cout << " (" << all.back().first << "," << all.back().second << ")";
				}
			}
		}
	}
	//std::cout << std::endl;

}

void AIShell::print_current_state(int **current_state){
	std::cout << "Print game board" << std::endl;
	//print current state
	for (int row = numRows - 1; row >= 0; row--){
		for (int col = 0; col<numCols; col++){
			std::cout << current_state[col][row];
		}
		std::cout << std::endl;
	}
}
