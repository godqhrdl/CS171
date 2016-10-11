#include "AIShell.h"
#include <iostream>
#include <queue>


AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline=0;
	this->numRows=numRows;
	this->numCols=numCols;
	this->gravityOn=gravityOn;
	this->gameState=gameState;
	this->lastMove=lastMove;
}


AIShell::~AIShell()
{
	
	//delete the gameState variable.
	for (int i =0; i<numCols; i++){
		delete [] gameState[i];
	}
	delete [] gameState;

}

Move AIShell::makeMove(){
	//this part should be filled in by the student to implement the AI
	//Example of a move could be: Move move(1, 2); //this will make a move at col 1, row 2
	
	
	//this will move to the left-most column possible.
//	for (int col = 0; col<numCols; col++){
//		for (int row = 0; row<numRows; row++){
//			if (gameState[col][row] == NO_PIECE){
//				Move m(col, row);
//				return m;
//			}
//		}
//	}
    std::queue<std::pair<int,int> > all_avalible_move;
    find_all_avl(all_avalible_move);
    
    evalutate(gameState);
    
    for (int col = numCols-1; col >= 0; col--){
        for(int row = numRows-1; row >= 0; row--){
            if (gameState[col][row] == NO_PIECE){
                Move m(col, row);
                return m;
            }
        }
    }
	Move m(0, 0);
	return m;
	 
}

//void print_all_aval(std::queue<std::pair<int,int> > all){}

//Test if a node is a terminal node
bool AIShell::test_terminal_node(int **current_state){
    //Test if there is winner
    
    
    //Test empty space
    return no_empty_space(current_state);
}

bool AIShell::test_horizontal(int **current_state){
    
    return false;
}

bool AIShell::test_vertical(int **current_state){
    
    return false;
}

bool AIShell::test_diagonal(int **current_state){
    
    return false;
}

//If no empty space return true, otherwise return false.
bool AIShell::no_empty_space(int **current_state){
    for(int col=0; col<numCols; col++){
        for(int row=0; row<numRows; row++){
            if(current_state[col][row] == NO_PIECE)
                return false;
        }
    }
    return true;
}



//Minimax Search Algorithm

int AIShell::minimax_search(int **current_state, int depth){
    
    return 0;
}


//Evaluate current state
int AIShell::evalutate(int **current_state){
    std::cout << "Print game board" << std::endl;
    //print current state
    for(int row=numRows-1; row>=0; row--){
        for(int col=0; col<numCols; col++){
            std::cout << current_state[col][row];
        }
        std::cout << std::endl;
    }
    
    
    return 0;
}


/*
 This function will find all available move
 The first part will find all available move when gavity is on
 The second part will find all available move when gavity is off
 Put in a queue, First in first out
 */
void AIShell::find_all_avl(std::queue<std::pair<int,int> > all){
    std::cout << "Available moves: " << std::endl;
    if (gravityOn == true){
        for(int col=0; col<numCols; col++){
            for(int row=0; row<numRows; row++){
                if(gameState[col][row] == NO_PIECE){
                    //std::cout << " (" << col << "," << row << ")" ;
                    std::pair<int,int> now;
                    now =std::make_pair(col, row);
                    all.push(now);
                    std::cout << " (" << all.back().first << "," << all.back().second << ")";
                    break;
                }
            }
        }
    }else{
        for(int col = 0; col<numCols; col++){
            for(int row=0; row<numRows; row++){
                if(gameState[col][row] == NO_PIECE){
                    //std::cout << " (" << col << "," << row << ")" ;
                    std::pair<int,int> now;
                    now =std::make_pair(col, row);
                    all.push(now);
                    std::cout << " (" << all.back().first << "," << all.back().second << ")";
                }
            }
        }
    }
    std::cout << std::endl;
}


