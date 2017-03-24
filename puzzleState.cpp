#include <iostream>
#include <cmath>

using namespace std;
class puzzleState {

private:
    int board[3][3];
    int id;
    int emptyPlace;
    int manhattanScore;
    int outOfPlaceScore;

    void createID() {
        id = 0;
        int base = 1;
        for(int i = 2 ; i >= 0 ; i--)
            for(int j = 2 ; j >= 0 ; j--) {
                id += (base*board[i][j]);
                base *= 10;
            }
    }
public:
    puzzleState() {
        int value = 1 ;
        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++) {
                board[i][j] = value;
                value++;
            }
        calculateManhattanScore();
        calculateOutOfPlaceScore();
        board[2][2] = 0;
        id = 123456780;
        emptyPlace = 9;
    }

    puzzleState(int id) {
        for(int i = 2 ; i >= 0 ; i--)
            for(int j = 2 ; j >= 0 ; j--) {
                board[i][j] = id%10;
                id /= 10;
            }
        calculateManhattanScore();
        calculateOutOfPlaceScore();
        emptyPlace = getMovableTilePlace();
    }
    puzzleState(int newBoard[3][3]) {
        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++) {
                board[i][j] = newBoard[i][j];
        }
        createID();
        calculateManhattanScore();
        calculateOutOfPlaceScore();
        emptyPlace = getMovableTilePlace();

    }
    //~puzzleState();

    int getID() {
        return id;
    }


    void displayBoard() {
        cout << "-------" << endl;
        for(int i = 0 ; i < 3 ; i++) {
            for(int j = 0 ; j < 3 ; j++) {
                cout  << " " << board[i][j];
            }
            cout << endl;
        }
        cout << "-------" << endl;
    }
    void setEmptyPlace(int place){
        emptyPlace = place;
    }

    int getMovableTilePlace() {
        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                if( board[i][j] == 0)
                    return (3*i + j + 1) ;
    }

    void setBoard(int newBoard[3][3]) {
        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                board[i][j] = newBoard[i][j];
    }

    void calculateManhattanScore() {
        manhattanScore = 0 ;
        for( int i = 0 ; i < 3 ; i++) {
            for(int j = 0 ; j < 3 ; j++) {
                if( board[i][j] == 0 ) manhattanScore += 4 - (i + j);
                else manhattanScore += ( abs(i-((board[i][j]-1)/3)) + abs(j-(((board[i][j]-1)%3) )));
            }
        }
    }
    void calculateOutOfPlaceScore(){
    	outOfPlaceScore = 0;
        for( int i = 0 ; i < 3 ; i++) {
            for(int j = 0 ; j < 3 ; j++) {
            	if(board[i][j] == 0 && 3*i+j+1 != 9){outOfPlaceScore++;}
            	else if(board[i][j] != 3*i+j+1){outOfPlaceScore++;}//  i*3+j-1
            }
        }   
    }
    int getOutOfPlaceScore() {
        return outOfPlaceScore;
    }

    int getManhattanScore() {
        return manhattanScore;
    }

    puzzleState* moveDown(){                                                      // pointer or the object itself

        // check if possible

        int emptyRow = (emptyPlace -1)/ 3;
        int emptyCol = (emptyPlace - 1) % 3;

        int newBoard[3][3];

        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                newBoard[i][j] = board[i][j];

        if(emptyRow != 0){
            newBoard[emptyRow][emptyCol] = newBoard[emptyRow - 1][emptyCol];
            newBoard[emptyRow - 1][emptyCol] = 0;
            //newState.setEmptyPlace((3*(emptyRow-1)+(emptyCol+1)));
            
        }
        puzzleState* newState = new puzzleState(newBoard);
        if(newState->getID()!= id && emptyRow !=0){return newState;}
        return NULL;
    }

    puzzleState* moveLeft(){
        // check if not possible retruns the old one

        int emptyRow = (emptyPlace -1)/ 3;
        int emptyCol = (emptyPlace - 1) % 3;

        int newBoard[3][3];
        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                newBoard[i][j] = board[i][j];

        if(emptyCol!= 2){

            newBoard[emptyRow][emptyCol] = newBoard[emptyRow][emptyCol+1];
            newBoard[emptyRow ][emptyCol+1] = 0;
            //newState.setEmptyPlace((3*(emptyRow)+(emptyCol+2)));
        }
		puzzleState* newState = new puzzleState(newBoard);
        if(newState->getID() != id && emptyCol !=2){return newState;}
        return NULL;
    }
    puzzleState* moveRight(){
        // check if not possible retruns the old one

        int emptyRow = (emptyPlace -1)/ 3;
        int emptyCol = (emptyPlace - 1) % 3;

        int newBoard[3][3];
        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                newBoard[i][j] = board[i][j];

        if(emptyCol!= 0){

            newBoard[emptyRow][emptyCol] = newBoard[emptyRow][emptyCol-1];
            newBoard[emptyRow ][emptyCol-1] =0 ;
            //newState.setEmptyPlace((3*(emptyRow)+(emptyCol)));
        }
		puzzleState* newState = new puzzleState(newBoard);
        if(newState->getID() != id && emptyCol != 0){return newState;}
        return NULL;
    }
    puzzleState* moveUp(){
        // check if not possible retruns the old one

        int emptyRow = (emptyPlace -1)/ 3;
        int emptyCol = (emptyPlace - 1) % 3;
        int newBoard[3][3];

        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                newBoard[i][j] = board[i][j];

        if(emptyRow!= 2){

            newBoard[emptyRow][emptyCol] = newBoard[emptyRow+1][emptyCol];
            newBoard[emptyRow+1][emptyCol] = 0;
        }
		puzzleState* newState = new puzzleState(newBoard);
        if(newState->getID() != id && emptyRow != 2){return newState;}
        return NULL;
    }
};
/*
int main() {

    puzzleState* init = new puzzleState();
    puzzleState* step2 = init->moveDown();
    step2->displayBoard();

	puzzleState* step3 = step2->moveRight();
	cout << (step3 == NULL);
	//step3->displayBoard();
	//puzzleState* step4 = step3->moveRight();
	//step4->displayBoard();

    return 0;

}
*/