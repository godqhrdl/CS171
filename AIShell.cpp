#include "AIShell.h"
#include <iostream>
#include <queue>

#define LIMITED_DEPTH 4


AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline=0;
	this->numRows=numRows;
	this->numCols=numCols;
	this->gravityOn=gravityOn;
	this->gameState=gameState;
	this->lastMove=lastMove;
    
    
    this->AIMove = true;

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

    std::queue<std::pair<int,int> > all_avalible_move;
    find_all_avl(all_avalible_move);
    
    evalutate(gameState);
    
    //Minimax search
    
    //Copy game board for AI search use
    
    
    minimax_search(gameState, LIMITED_DEPTH);
    std::queue<std::pair<int,int> > test;
    find_all_avl(test);
    
    std::pair<int,int> t = next_move(test,true);
    print_current_state(gameState);
    
    undo_move(t);
    print_current_state(gameState);
    
    Move f(t.first,t.second);
    return f;

	 
}

//void print_all_aval(std::queue<std::pair<int,int> > all){}

//Test if a node is a terminal node
bool AIShell::test_terminal_node(int **current_state){
    
    return no_empty_space(current_state) || test_horizontal(current_state) || test_vertical(current_state) || test_diagonal(current_state);
}

bool AIShell::test_horizontal(int **current_state){
    for(int row=0; row<numRows; row++){
        int count_ai=0, count_hm=0;
        for(int col=0; col<numCols; col++){
            if(current_state[col][row] == 1){
                count_ai++;
                count_hm = 0;
            }
            if(current_state[col][row] == -1){
                count_ai = 0;
                count_hm++;
            }
        }
        
        if(count_hm == k || count_ai == k){
            std::cout << "find horizontal winner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            return true;
        }
    }
    
    return false;
}

bool AIShell::test_vertical(int **current_state){
    for(int col=0; col<numCols; col++){
        int count_ai=0, count_hm=0;
        for(int row=0; row<numRows; row++){
            if(current_state[col][row] == 1){
                count_ai++;
                count_hm =0;
            }
            if(current_state[col][row] == -1){
                count_ai=0;
                count_hm++;
            }
        }
        
        if(count_hm==k || count_ai==k){
            std::cout << "find vertical winner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            return true;
        }
    }
    
    return false;
}

bool AIShell::test_diagonal(int **current_state){
    
    //Left bottom corner to right top corner
    for(int row=0; row<=numRows-k; row++){
        int count_ai=0, count_hm=0;
        int c=0, r=row;
        for(;c<numCols && r<numRows; c++, r++){
            if(current_state[c][r] == 1){
                count_ai++;
                count_hm = 0;
            }
            if(current_state[c][r] == -1){
                count_ai=0;
                count_hm++;
            }
        }
        if(count_hm==k || count_ai==k){
            std::cout << "find diagonal winner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            return true;
        }
    }
    
    for(int col=0; col<=numCols-k; col++){
        int count_ai=0, count_hm=0;
        int c=col, r=0;
        for(;c<numCols && r<numRows; c++, r++){
            if(current_state[c][r] == 1){
                count_ai++;
                count_hm = 0;
            }
            if(current_state[c][r] == -1){
                count_ai=0;
                count_hm++;
            }

        }
        if(count_hm==k || count_ai==k){
            std::cout << "find diagonal winner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            return true;
        }
    }
    
    //Left top corner to right bottom corner
    for(int row=numRows-1; row+1>=k; row--){
        int count_ai=0, count_hm=0;
        int c=0, r=row;
        for(;c<numCols && r>=0; c++, r--){
            if(current_state[c][r] == 1){
                count_ai++;
                count_hm = 0;
            }
            if(current_state[c][r] == -1){
                count_ai=0;
                count_hm++;
            }
        }
        if(count_hm==k || count_ai==k){
            std::cout << "find diagonal winner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            return true;
        }
    }
    
    for(int col=0; col<=numCols-k; col++){
        int count_ai=0, count_hm=0;
        int c=col, r=numRows-1;
        for(;c<numCols && r>=0; c++,r--){
            if(current_state[c][r] == 1){
                count_ai++;
                count_hm = 0;
            }
            if(current_state[c][r] == -1){
                count_ai=0;
                count_hm++;
            }
        }
        if(count_hm==k || count_ai==k){
            std::cout << "find diagonal winner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            return true;
        }
    }
    
    
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
    //Test if is leaf node or at limited depth
    if(test_terminal_node(current_state) || depth < 0)
        return evalutate(current_state);
    
    if(AIMove == true)
        return max_search(depth);
    else
        return min_search(depth);
    
}

//Max function for Minimax Search
int AIShell::max_search(int depth){
    int best = -999999;
    if(depth == 0 || test_terminal_node(gameState))
        return evalutate(gameState);
    
    std::queue<std::pair<int,int> > next_all; //A queue contains all availabe moves
    find_all_avl(next_all);
    while(!next_all.empty()){
        
        std::cout << "**********Current Depth: " << LIMITED_DEPTH-depth << std::endl;
        
        std::pair<int,int> next = next_move(next_all,true);  //Make a move on the game board
        

        
        int v = min_search(depth-1);
        undo_move(next);  //Undo the move and restore the board
        if(v > best)
            best = v;
    }
    
    return best;
}

//Min function for Minimax Search.
int AIShell::min_search(int depth){
    //AIMove = false;
    int best = 999999;
    if(depth == 0 || test_terminal_node(gameState))
        return evalutate(gameState);
    
    std::queue<std::pair<int,int> > next_all; //A queue contains all available moves
    find_all_avl(next_all);
    while(!next_all.empty()){
        
        std::cout << "**********Current Depth: " << LIMITED_DEPTH-depth << std::endl;
        
        std::pair<int,int> next = next_move(next_all,false);
        int v = max_search(depth-1);
        undo_move(next);
        if(v < best)
            best = v;
    }
    
    return best;
}

//AI will use this function while searching
std::pair<int,int> AIShell::next_move(std::queue<std::pair<int,int> > &all, bool aimove){
    std::pair<int,int> next= all.front(); //Find the next move
    all.pop(); //pop the next move from queue
    
    std::cout << "AI next move is: "<<next.first << "," << next.second << std::endl;
    gameState[next.first][next.second] = aimove? 1:-1;
    
    AIMove = !AIMove;
    
    print_current_state(gameState);
    
    return next;
}

void AIShell::undo_move(std::pair<int,int> p_move){
    gameState[p_move.first][p_move.second] = 0;
}


//Evaluate current state
int AIShell::evalutate(int **current_state){
    int result = 0;
    
    
    
    
    std::cout << "This is heuristic function" << std::endl;
    
    return 0;
}


/*
 This function will find all available move
 The first part will find all available move when gavity is on
 The second part will find all available move when gavity is off
 Put in a queue, First in first out
 */
void AIShell::find_all_avl(std::queue<std::pair<int,int> > &all){
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

void AIShell::print_current_state(int **current_state){
    std::cout << "Print game board" << std::endl;
    //print current state
    for(int row=numRows-1; row>=0; row--){
        for(int col=0; col<numCols; col++){
            std::cout << current_state[col][row];
        }
        std::cout << std::endl;
    }
}

