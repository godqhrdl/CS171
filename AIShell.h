#ifndef AISHELL_H
#define AISHELL_H

#pragma once
#include "Move.h"
#include <queue>


// A new AIShell will be created for every move request.
class AIShell{

public:
	//these represent the values for each piece type.
	static const int AI_PIECE=1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE=0;


private:
	//Do not alter the values of numRows or numcols.
	//they are used for deallocating the gameState variable.
	int numRows; //the total number of rows in the game state.
	int numCols; //the total number of columns in the game state.
	int **gameState; //a pointer to a two-dimensional array representing the game state.
	bool gravityOn; //this will be true if gravity is turned on. It will be false if gravity is turned off.
	Move lastMove; //this is the move made last by your opponent. If your opponent has not made a move yet (you move first) then this move will hold the value (-1, -1) instead.


public:
	int deadline; //this is how many milliseconds the AI has to make move.
	int k;        // k is the number of pieces a player must get in a row/column/diagonal to win the game. IE in connect 4, this variable would be 4

	AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove);
	~AIShell();
	Move makeMove();
    
    //Find all available move
    void find_all_avl(std::queue<std::pair<int,int> > all);
    //void print_all_aval(std::queue<std::pair<int,int> > all);
    
    //Evaluate Function
    int evalutate(int **current_state);
    
    //Test terminal node
    bool test_terminal_node(int **current_state);
    bool test_horizontal(int **current_state);
    bool test_vertical(int **current_state);
    bool test_diagonal(int **current_state);
    bool no_empty_space(int **current_state);
    
    //Minimax Search
    int minimax_search(int **current_state, int depth);
    int max_search(int **current_state, int depth);
    
};

#endif //AISHELL_H
