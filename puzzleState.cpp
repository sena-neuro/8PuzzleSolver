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
        emptyPlace = getMovableTilePlace();
    }
    puzzleState(int newBoard[3][3]) {
        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++) {
                board[i][j] = newBoard[i][j];
        }
        id = getID();
        calculateManhattanScore();
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

    int getManhattanScore() {
        return manhattanScore;
    }

    puzzleState moveDown(){                                                      // pointer or the object itself

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
         puzzleState newState(newBoard);
        return newState;
    }

    puzzleState moveLeft(){
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
        puzzleState newState(newBoard);
        return newState;
    }
    puzzleState moveRight(){
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
         puzzleState newState(newBoard);
        return newState;
    }
    puzzleState moveUp(){
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
        puzzleState newState(newBoard);
        return newState;
    }
};

int main() {
    puzzleState p;
    cout << p.getID() << endl;
    p.displayBoard();
    puzzleState p1, p2, p3;
    cout << "mov: " << p.getMovableTilePlace() << endl;


    p1 = p.moveDown();
    cout << "p1's man sc: " << p1.getManhattanScore() << endl;
    p1.displayBoard();

    p2 = p1.moveRight();
    cout << "p2's man sc: " << p2.getManhattanScore() << endl;
    p2.displayBoard();

    p3 = p2.moveRight();
    cout << "p3's man sc: " << p3.getManhattanScore() << endl;
    p3.displayBoard();

    return 0;

}
