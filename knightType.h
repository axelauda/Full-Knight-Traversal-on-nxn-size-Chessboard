/*
    Name: Alexander Lauderdale
    NSHE ID: 5006688786
    Section: CS 302 1002
    Assignment: 2
    Description: Review recursion by solving the knight tour problem.
*/

#include <iostream>
#include <cstdlib>
#include <vector>

class knightType {

public:
    struct position { //holds positions and number of possible move from position
        position(int r = 0, int c = 0, int o = 0)
            {
            row = r; //The row of knight position
            col = c; //The column of knight position
            onwardMoves = o; //The number of possible moves from this position
            }
        int row;
        int col;
        int onwardMoves;
    };

    knightType(int s); //constructor makes board of size s
    bool knightTour(int , int); //public knightTour() called in main
    void outputTour () const; //outputTour outputs the board with numbers detailing path of knight

private:
    void eightSquares(knightType::position&, int, int, int);

    bool knightTour(int , int , int); //recursive knightTour function creates knight path to fill entire board
    std::vector <position> getAvailableMoves(int , int); //gets possible moves from current knight location
    bool fullBoard(); //Checks if all spots on board are filled
    std::vector <std::vector <int>> board; //The chess board the knight moves on
    int functionsCalled; //Counts how many times the knightTour() function is called recursively
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Function Implementation:

    //Public Functions:

knightType::knightType(int s = 8) { //Constuctor

    std::vector <int> row; //for pushing rows into 2d vector board

    for (int i = 0; i < s; i++) { //chess board of passed size is initialized
        board.push_back(row);
        for (int j = 0; j < s; j++) {
            board[i].push_back(0); //pushing columns onto board
        }
    }
//Number of functions called set to 0
    functionsCalled = 0;
}

bool knightType::knightTour(int r, int c) { //Called by main and starts the knightTour recursion
    return knightType::knightTour(r, c, 1);
}

void knightType::outputTour() const { //outputs the chess board based on size

    char letter = 'A';
    int rowCount = 0;
    int size = board[0].size();
//Every column is labeled with a letter
    std::cout << "   ";
    for (char i = 0; i < size; i++) {
        std::cout << letter << "  ";
        letter++;
    }
//Each row is labeled with a letter and all entries in board are organized neatly
    letter = 'A';
    for (int i = 0; i < size; i++) {
        std::cout << "\n" << letter << "  ";
        for (int j = 0; j < size; j++) {
            std::cout << board[i][j];
            if (board[i][j] < 10) {
                std::cout << "  ";
            }
            if (board[i][j] >= 10 && board[i][j] < 100) {
                std::cout << " ";
            }
        }
        letter++;
    }
//The number of functions called from knightTour() is outputted
    std::cout << "\n\nFunctions called: " << functionsCalled << "\n";
}

    //Private Functions:

bool knightType::knightTour(int r, int c, int o) { //Tail recursive Function

    if (fullBoard()) { //If the board is full, knight tour ends
        return true;
    }

    int next = o + 1; //Counts up the move number of knight

    std::vector <position> posMoves; //All possible moves in vector, best move is found from the vector
    position bestMove;

    bestMove.row = 0; //Best move struct variables initialized
    bestMove.col = 0;
    bestMove.onwardMoves = 9;

    posMoves = getAvailableMoves(r, c); //getAvailableMoves() function is called to get position vector

    for (int i = 0; i < posMoves.size(); i++) { //Best move is chosen by finding possible move with least onward moves
        if ((posMoves[i].onwardMoves < bestMove.onwardMoves)
         && (board[posMoves[i].row][posMoves[i].col] == 0)) {
            bestMove.row = posMoves[i].row;
            bestMove.col = posMoves[i].col;
            bestMove.onwardMoves = posMoves[i].onwardMoves;
        }
    }
    
    board[r][c] = o; //The board is filled with the move number
    functionsCalled++; //Functions called is incremented

    return knightTour(bestMove.row, bestMove.col, next); //The knight tour continues to the next move recursively

}

void knightType::eightSquares(knightType::position& t, int size, int row, int col) {
    //Next First Square Check*************************************************
            if ((row - 2) >= 0 && (col - 1) >= 0) {
                if (board[row - 2][col - 1] == 0) {
                    t.onwardMoves++;
                }
            }
    //Next Second Square Check*************************************************
            if ((row - 1) >= 0 && (col - 2) >= 0) {
                if (board[row - 1][col - 2] == 0) {
                    t.onwardMoves++;
                }
            }
    //Next Third Square Check*************************************************
            if ((row + 1) <= (size - 1) && (col - 2) >= 0) {
                if (board[row + 1][col - 2] == 0) {
                    t.onwardMoves++;
                }
            }
    //Next Fourth Square Check*************************************************
            if ((row + 2) <= (size - 1) && (col - 1) >= 0) {
                if (board[row + 2][col - 1] == 0) {
                    t.onwardMoves++;
                }
            }
    //Next Fifth Square Check*************************************************
            if ((row + 2) <= (size - 1) && (col + 1) <= (size - 1)) {
                if (board[row + 2][col + 1] == 0) {
                    t.onwardMoves++;
                }
            }
    //Next Sixth Square Check*************************************************
            if ((row + 1) <= (size - 1) && (col + 2) <= (size - 1)) {
                if (board[row + 1][col + 2] == 0) {
                    t.onwardMoves++;
                }
            }
    //Next Seventh Square Check*************************************************
            if ((row - 1) >= 0 && (col + 2) <= (size - 1)) {
                if (board[row - 1][col + 2] == 0) {
                    t.onwardMoves++;
                }
            }
    //Next Eigth Square Check*************************************************
            if ((row - 2) >= 0 && (col + 1) <= (size - 1)) {
                if (board[row - 2][col + 1] == 0) {
                    t.onwardMoves++;
                }
            }
}

std::vector <knightType::position> knightType::getAvailableMoves(int r, int c) { //Gets possible moves and stores in position vector
    
    int size = board[0].size();
    
    position test;
    std::vector <position> nextMoves;

    test.onwardMoves = 0;

    int rPos;
    int cPos;

/*Every knight move from passed position (r,c) is checked to see if it is possible and on the board with if statements,
For every possible move, the onward moves is calculated using the same if statement conditions.
After every square check, the move is stored in a vector of position structs, which is returned at the end.
*/

//First Square Check**********************************************************

    test.row = r - 2;
    test.col = c - 1;

    if (test.row >= 0 && test.col >= 0) { //If next move is still on board, check the onward moves
        if (board[test.row][test.col] == 0) {
            eightSquares(test, size, test.row, test.col);
            nextMoves.push_back(test);
            test.onwardMoves = 0;
        }
    }

//Second Square Check**********************************************************

    test.row = r - 1;
    test.col = c - 2;

    if (test.row >= 0 && test.col >= 0) { //If next move is still on board, check the onward moves
        if (board[test.row][test.col] == 0) {
            eightSquares(test, size, test.row, test.col);
            nextMoves.push_back(test);
            test.onwardMoves = 0;
        }
    }

//Third Square Check**********************************************************

    test.row = r + 1;
    test.col = c - 2;

    if (test.row <= (size - 1) && test.col >= 0) { //If next move is still on board, check the onward moves
        if (board[test.row][test.col] == 0) {
            eightSquares(test, size, test.row, test.col);
            nextMoves.push_back(test);
            test.onwardMoves = 0;
        }
    }

//Fourth Square Check**********************************************************

    test.row = r + 2;
    test.col = c - 1;

    if (test.row <= (size - 1) && test.col >= 0) { //If next move is still on board, check the onward moves
        if (board[test.row][test.col] == 0) {
            eightSquares(test, size, test.row, test.col);
            nextMoves.push_back(test);
            test.onwardMoves = 0;
        }
    }

//Fifth Square Check**********************************************************

    test.row = r + 2;
    test.col = c + 1;

    if (test.row <= (size - 1) && test.col <= (size - 1)) { //If next move is still on board, check the onward moves
        if (board[test.row][test.col] == 0) {
            eightSquares(test, size, test.row, test.col);
            nextMoves.push_back(test);
            test.onwardMoves = 0;
        }
    }

//Sixth Square Check**********************************************************

    test.row = r + 1;
    test.col = c + 2;

    if (test.row <= (size - 1) && test.col <= (size - 1)) { //If next move is still on board, check the onward moves
        if (board[test.row][test.col] == 0) {
            eightSquares(test, size, test.row, test.col);
            nextMoves.push_back(test);
            test.onwardMoves = 0;
        }
    }

//Seventh Square Check**********************************************************

    test.row = r - 1;
    test.col = c + 2;

    if (test.row >= 0 && test.col <= (size - 1)) { //If next move is still on board, check the onward moves
        if (board[test.row][test.col] == 0) {
            eightSquares(test, size, test.row, test.col);
            nextMoves.push_back(test);
            test.onwardMoves = 0;
        }
    }

//Eighth Square Check**********************************************************

    test.row = r - 2;
    test.col = c + 1;

    if (test.row >= 0 && test.col <= (size - 1)) { //If next move is still on board, check the onward moves
        if (board[test.row][test.col] == 0) {
            eightSquares(test, size, test.row, test.col);
            nextMoves.push_back(test);
            test.onwardMoves = 0;
        }
    }
    return nextMoves; //Position struct vector is returned
}

bool knightType::fullBoard() { //The board is checked if it is filled

    int size = board[0].size(); //Size of board is determined

    bool isFull = true; //bool isFill stores truth value of whether board is full or not

    for (int i = 0; i < size; i++) { //nested for loop checks every entry in board
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) { //if any entry in board is 0, that means board is not full and returns false
                isFull = false;
                return isFull;
            }
        }
    }
    return isFull; //If no 0 is found in board, function returns true
}