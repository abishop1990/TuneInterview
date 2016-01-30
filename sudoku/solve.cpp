#include <iostream>
#include <stdlib.h>

#include "sudoku.h"

using namespace std;

int main(int argc, char * argv [])
{
    int values[BOARD_SIZE][BOARD_SIZE];

	if(readBoard(&values) == false) return 1;
	
    //cout << "Puzzle scanned in:\n" << endl;
    SudokuPuzzle puzzle = SudokuPuzzle(values);
    //puzzle.printInitialBoard();    
    //cout << endl; 

    if(puzzle.solve()) puzzle.printSolvedBoard();
    else cout << "Puzzle could not be solved" << endl;

    return 0;
}

