#ifndef __SUDOKU__
#define __SUDOKU__

#include <iostream>

//Modify GRID_SIZE to create a different sized sudoku board
//Since we use this constant throughout, everything will be resized upon modification
#define GRID_SIZE 3
#define BOARD_SIZE GRID_SIZE * GRID_SIZE

//Utility function to read board from an input source, used for main program and tests
bool readBoard(std::istream & in, int (* values) [BOARD_SIZE][BOARD_SIZE]);


/*
 * SudokuCell class
 *
 * Represents a single sudoku board cell
 * Value will be 0 when multiple possiblities (blank)
 * Actually has no awareness of grid/row/column, so values will be controlled by SudokuPuzzle
 * 
 * In current iteration have possible value code commented out, until I find a way to fix
 * backtracking issues with storing this state without huge overhead.
 * Possiblities are stored in indexes 1-9 of possibileValues for readability/convienence 
 */
class SudokuCell {

    public:
        SudokuCell();
        SudokuCell(int v);
        int getValue();
        bool setValue(int v);
        //void addPossibileValue(int v);
        //void deletePossibleValue(int v);
        //bool isPossibleValue(int v);
        //int possibleValueCount();
        //int firstPossibleValue();
 
    private:
        int value;
        //bool possibleValues[BOARD_SIZE+1];
};

/*
 * SudokuBoard class
 *
 * Represents a board state of a sudoku puzzle
 * Contains logic to check validity and place a value, but no solving logic
 */
class SudokuBoard {

    public:
        SudokuBoard(int (&values) [BOARD_SIZE][BOARD_SIZE]);
        SudokuBoard();
        bool setValue(int r, int c, int v);
        int getValue(int r, int c);
        void printBoard();
        bool canPlaceValue(int r, int c, int v);        
        bool firstEmptySquare(int * r, int * c);
        static int getGridStart(int idx);

    private:
        bool checkRow(int r, int v);
        bool checkColumn(int c, int v);
        bool checkGrid(int r, int c, int v);
        //bool updateBoardPossiblities(int r, int c, int v);
        SudokuCell cells[BOARD_SIZE][BOARD_SIZE];

};

/*
 * SudokuPuzzle class
 *
 * The solver wrapped up in a class 
 *
 * This keeps the initial board as well, which is good for comparison
 * and would be useful for extensibility (such as making a sudoku game program)
 * A third "currentBoard" could be used here in a game mode 
*/
class SudokuPuzzle {

    public:
        SudokuPuzzle(int (&values) [BOARD_SIZE][BOARD_SIZE]);
        SudokuPuzzle();
        bool solve();
        void printSolvedBoard();      
        void printInitialBoard();  


    private:
        SudokuBoard initialBoard;
        SudokuBoard solvedBoard;
};

#endif
