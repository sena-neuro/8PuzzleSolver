#include "puzzleState.cpp" // headerı doldur
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>
using namespace std;
class Puzzle{

	vector<int> visitedIDs;
public:

	bool isVisited(int stateID) {
		for(int i = 0;i < visitedIDs.size();i++){
			if (visitedIDs[i] == stateID){
				return true;
			}

		}
		return false;
	}

	puzzleState* generateInitialState(){

		srand (time(NULL));
		puzzleState* init = new puzzleState();
		int move;
		puzzleState* temp;

		for(int i = 0;i < 200; i++){
		  	move = rand() % 4+ 1;
		  	
		  	if(move == 1)
		  	{
		  		temp = init->moveDown();
		  		if(temp != NULL && !isVisited(temp->getID()))
		  		{ 
		  			delete init;
		  			init = temp;
		  			visitedIDs.push_back(init->getID());
		  		}
		  	}
			
			if(move == 2)
			{	

		  		temp = init->moveLeft();
		  		if(temp != NULL&& !isVisited(temp->getID()))
		  		{
		  			delete init;
		  			init = temp;
		  			visitedIDs.push_back(init->getID());
		  		}
		  	}
			
			if(move == 3)
			{  		 
				temp = init->moveRight();
		  		if(temp != NULL&& !isVisited(temp->getID()))
		  		{
		  			delete init;
		  			init = temp;
		  			visitedIDs.push_back(init->getID());
		  		}
		  	}
			if(move == 4)
			{
				temp = init->moveUp();
		  		if(temp != NULL&& !isVisited(temp->getID()))
		  		{
		  			delete init;
		  			init = temp;
		  			visitedIDs.push_back(init->getID());
		  		}
		  	}
		
		}
		return init;
	}
	void solveWithManhattanDistance(puzzleState &start){

	}
};
