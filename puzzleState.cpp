#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
class puzzleState {

private:
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
	int board[3][3];
    puzzleState() {
        int value = 1 ;
        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++) {
                board[i][j] = value;
                value++;
            }
        calculateManhattanScore();
        calculateOutOfPlaceScore();
        board[2][2] = 9;
        id = 123456789;
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

    int getID() const{
        return id;
    }


    void displayBoard() const{
        for(int i = 0 ; i < 3 ; i++) {
            for(int j = 0 ; j < 3 ; j++) {
            	if( board[i][j] == 9) cout << "  " ;
                else cout  << " " << board[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    void setEmptyPlace(int place){
        emptyPlace = place;
    }

    int getMovableTilePlace() const{
        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                if( board[i][j] == 9)
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
                if( board[i][j] == 9 ) manhattanScore += 4 - (i + j);
                else manhattanScore += ( abs(i-((board[i][j]-1)/3)) + abs(j-(((board[i][j]-1)%3) )));
            }
        }
    }
    void calculateOutOfPlaceScore(){
    	outOfPlaceScore = 0;
        for( int i = 0 ; i < 3 ; i++) {
            for(int j = 0 ; j < 3 ; j++) {
            	if(board[i][j] == 9 && 3*i+j+1 != 9){outOfPlaceScore++;}
            	else if(board[i][j] != 3*i+j+1){outOfPlaceScore++;}//  i*3+j-1
            }
        }
    }
    int getOutOfPlaceScore() const{
        return outOfPlaceScore;
    }

    int getManhattanScore() const{
        return manhattanScore;
    }

    puzzleState* moveDown()const{                                                      // pointer or the object itself

        // check if possible

        int emptyRow = (emptyPlace -1)/ 3;
        int emptyCol = (emptyPlace - 1) % 3;

        int newBoard[3][3];

        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                newBoard[i][j] = board[i][j];

        if(emptyRow != 0){
            newBoard[emptyRow][emptyCol] = newBoard[emptyRow - 1][emptyCol];
            newBoard[emptyRow - 1][emptyCol] = 9;
            //newState.setEmptyPlace((3*(emptyRow-1)+(emptyCol+1)));

        }
        puzzleState* newState = new puzzleState(newBoard);
        //cout << newState->getMovableTilePlace() << endl;
        if(newState->getID()!= id && emptyRow !=0){return newState;}
        return NULL;
    }

    puzzleState* moveLeft()const{
        // check if not possible retruns the old one

        int emptyRow = (emptyPlace -1)/ 3;
        int emptyCol = (emptyPlace - 1) % 3;

        int newBoard[3][3];
        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                newBoard[i][j] = board[i][j];

        if(emptyCol!= 2){

            newBoard[emptyRow][emptyCol] = newBoard[emptyRow][emptyCol+1];
            newBoard[emptyRow ][emptyCol+1] = 9;
            //newState.setEmptyPlace((3*(emptyRow)+(emptyCol+2)));
        }
		puzzleState* newState = new puzzleState(newBoard);
        if(newState->getID() != id && emptyCol !=2){return newState;}
        return NULL;
    }
    puzzleState* moveRight() const{
        // check if not possible retruns the old one

        int emptyRow = (emptyPlace -1)/ 3;
        int emptyCol = (emptyPlace - 1) % 3;

        int newBoard[3][3];
        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                newBoard[i][j] = board[i][j];

        if(emptyCol!= 0){

            newBoard[emptyRow][emptyCol] = newBoard[emptyRow][emptyCol-1];
            newBoard[emptyRow ][emptyCol-1] =9 ;
            //newState.setEmptyPlace((3*(emptyRow)+(emptyCol)));
        }
		puzzleState* newState = new puzzleState(newBoard);
        if(newState->getID() != id && emptyCol != 0){return newState;}
        return NULL;
    }
    puzzleState* moveUp() const{
        // check if not possible retruns the old one

        int emptyRow = (emptyPlace -1)/ 3;
        int emptyCol = (emptyPlace - 1) % 3;
        int newBoard[3][3];

        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                newBoard[i][j] = board[i][j];

        if(emptyRow!= 2){

            newBoard[emptyRow][emptyCol] = newBoard[emptyRow+1][emptyCol];
            newBoard[emptyRow+1][emptyCol] = 9	;
        }
		puzzleState* newState = new puzzleState(newBoard);
        if(newState->getID() != id && emptyRow != 2){return newState;}
        return NULL;

    }
    void operator=( const puzzleState p){ // getters const -> const puzSt ...


        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                board[i][j] = p.board[i][j];

    	id = p.getID();
    	emptyPlace = p.getMovableTilePlace();
    	manhattanScore = p.getManhattanScore();
    	outOfPlaceScore = p.getOutOfPlaceScore();

    }


};
