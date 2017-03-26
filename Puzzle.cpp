#include "puzzleState.cpp" // headerı doldur
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Puzzle {

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
		visitedIDs.clear();
		return init;
	}
	void solveWithManhattanDistance(puzzleState* start) {
		//priority_queue<puzzleState> queue;
		priority_queue<puzzleState, vector<puzzleState>, ManhattonScoreComp> queue;

		puzzleState* temp;
		puzzleState cur;
		queue.push(*start);
		int noOfMoves = 0;

		while(queue.top().getManhattanScore() != 0 && !queue.empty()){
			cur = queue.top();
			cur.displayBoard();

			noOfMoves++;

			temp = cur.moveDown();
			if(temp != NULL && !isVisited(temp->getID())){
				queue.push(*temp);
				visitedIDs.push_back(temp->getID());

			}

			temp = cur.moveUp();
			if(temp != NULL && !isVisited(temp->getID())){
				queue.push(*temp);
				visitedIDs.push_back(temp->getID());

			}

			temp = cur.moveLeft();
			if(temp != NULL&& !isVisited(temp->getID())){
				queue.push(*temp);
				visitedIDs.push_back(temp->getID());

			}
			temp = cur.moveRight();
			if(temp != NULL && !isVisited(temp->getID())){
				queue.push(*temp);
				visitedIDs.push_back(temp->getID());
			}
			if(! (	queue.top().moveUp() != NULL   && !isVisited(queue.top().moveUp()->getID() ) ||
					queue.top().moveDown() != NULL && !isVisited(queue.top().moveDown()->getID() ) ||
					queue.top().moveLeft() != NULL && !isVisited(queue.top().moveLeft()->getID() ) ||
					queue.top().moveRight() != NULL && !isVisited(queue.top().moveRight()->getID() ) ) )
				queue.pop();

		}
		queue.top().displayBoard();
		cout << "Number of moves: " << noOfMoves << endl;
		visitedIDs.clear();
		return;
	}

		void solveWithOutOfPlace(puzzleState* start) {
		//priority_queue<puzzleState> queue;
		priority_queue<puzzleState, vector<puzzleState>, OutOfPlaceScoreComp> queue;

		puzzleState* temp;
		puzzleState cur;
		queue.push(*start);
		int noOfMoves = 0;

		while(queue.top().getOutOfPlaceScore() != 0 && !queue.empty()){
			cur = queue.top();
			cur.displayBoard();

			temp = cur.moveDown();
			if(temp != NULL && !isVisited(temp->getID())){
				queue.push(*temp);
				visitedIDs.push_back(temp->getID());

			}

			temp = cur.moveUp();
			if(temp != NULL && !isVisited(temp->getID())){
				queue.push(*temp);
				visitedIDs.push_back(temp->getID());

			}

			temp = cur.moveLeft();
			if(temp != NULL&& !isVisited(temp->getID())){
				queue.push(*temp);
				visitedIDs.push_back(temp->getID());

			}
			temp = cur.moveRight();
			if(temp != NULL && !isVisited(temp->getID())){
				queue.push(*temp);
				visitedIDs.push_back(temp->getID());
			}
			if(! (	queue.top().moveUp() != NULL   && !isVisited(queue.top().moveUp()->getID() ) ||
					queue.top().moveDown() != NULL && !isVisited(queue.top().moveDown()->getID() ) ||
					queue.top().moveLeft() != NULL && !isVisited(queue.top().moveLeft()->getID() ) ||
					queue.top().moveRight() != NULL && !isVisited(queue.top().moveRight()->getID() ) ) )
				queue.pop();
            noOfMoves++;
		}
		queue.top().displayBoard();
		cout << "Number of moves: " << noOfMoves << endl;
		visitedIDs.clear();
		return;
	}

	struct ManhattonScoreComp {  //if the man of s1 score is bigger than its has less priority
		bool operator()(const puzzleState &s1, const puzzleState &s2) const
		{
			return s1.getManhattanScore() > s2.getManhattanScore();
		}
	};
	struct OutOfPlaceScoreComp {
		bool operator()(const puzzleState &s1, const puzzleState &s2) const
		{
			return s1.getOutOfPlaceScore() > s2.getOutOfPlaceScore();
		}
	};
};

int main() {
	puzzleState* ps;
	Puzzle p;

	ps = p.generateInitialState();
	p.solveWithManhattanDistance(ps);
	p.solveWithOutOfPlace(ps);

	return 0;
}
