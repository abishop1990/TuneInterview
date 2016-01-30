/*
 * sudoku.cpp
 *
 * Contains the logic for classes for a sudoku solver program
 *
 * Written by Alan Bishop 1/30/2016
 */

#include <iostream>
#include <stdlib.h>

#include "sudoku.h"

using namespace std;


//Read Board fuction
bool readBoard(int (* values) [BOARD_SIZE][BOARD_SIZE]) {
    string line; 

	for(int i = 0; i < BOARD_SIZE; ++i) {
        for(int j = 0; j < BOARD_SIZE; ++j) {

            //Read next token (there's no commas at the end of the line)
			if(j == BOARD_SIZE -1) getline(cin,line);
			else getline(cin, line, ',');
			
			//Parse out value
            int currentValue = -1;
            if(line == "-") currentValue = 0;
            else currentValue = atoi(line.c_str());

			//Error check for bad data
            if(currentValue < 0 || currentValue > BOARD_SIZE) {
                cerr << "Error parsing in (" << i << "," << j << "), got value of " 
                     << currentValue << " from line " << line << endl;
                return false;
            }

			//Put into array
            (*values)[i][j] = currentValue;
       }
    }
	return true;	
}


//////////////////////////////////////////////////////
//SUDOKU PUZZLE CODE /////////////////////////////////
//////////////////////////////////////////////////////
SudokuPuzzle::SudokuPuzzle(int (&values) [BOARD_SIZE][BOARD_SIZE]) {
    initialBoard = SudokuBoard(values);
    solvedBoard = initialBoard;
}

SudokuPuzzle::SudokuPuzzle() {
    initialBoard = SudokuBoard();
    solvedBoard = initialBoard;
}

bool SudokuPuzzle::solve() {
    int r, c;
    //If the board has no empties, we don't have anything to do
    //Can either assume this is solved or do a check on the whole board
    if(!solvedBoard.firstEmptySquare(&r,&c)) {
        return true;
    }

    for(int i = 1; i < BOARD_SIZE+1; ++i) {
        if(solvedBoard.canPlaceValue(r,c,i)) {
            solvedBoard.setValue(r,c,i);
            if(solve()) return true;
            else solvedBoard.setValue(r,c,0); 
        }
    } 

    return false;
}

void SudokuPuzzle::printSolvedBoard() {
    solvedBoard.printBoard();
}

void SudokuPuzzle::printInitialBoard() {
    initialBoard.printBoard();
}

///////////////////////////////////////////////////////
//SUDOKU BOARD CODE////////////////////////////////////
///////////////////////////////////////////////////////
SudokuBoard::SudokuBoard(int (&values) [BOARD_SIZE][BOARD_SIZE])
{
    for(int i = 0; i < BOARD_SIZE; ++i) {
        for(int j = 0; j < BOARD_SIZE; ++j) {
            cells[i][j] = SudokuCell(values[i][j]);
        }
    }
}

SudokuBoard::SudokuBoard() {
    for(int i = 0; i < BOARD_SIZE; ++i) {
        for(int j = 0; j < BOARD_SIZE; ++j) {
            cells[i][j] = SudokuCell();
        }
    }
}

bool SudokuBoard::setValue(int r, int c, int v) {
    if(r >= BOARD_SIZE || r < 0 || c >= BOARD_SIZE || c < 0) return false;
    
    //Set value for this cell
    cells[r][c].setValue(v);
   
    //Make sure we didn't break anything with this placement...
    //return updateBoardPossibilties(r,c,v);
    return true;
}
/*
//Post value set function to update the rest of the board
//Will attempt to solve any squares it can on it's way
//Returns false if a deduced update is impossible
bool SudokuBoard::updateBoardPossibilties(int r, int c, int v) {
    int gridRowStart = getGridStart(r);
    int gridColumnStart = getGridStart(c); 

    bool puzzleStillValid = true;

    //Update row and column possible values
    for(int i = 0; i < BOARD_SIZE; ++i) {
        if(i != c)  {
            puzzleStillValid = updateCellAfterPlacement(r,i,v);
            if(!puzzleStillValid) return false;
        }
        if(i != r)  {
            puzzleStillValid = updateCellAfterPlacement(i,c,v);
            if(!puzzleStillValid) return false;
        }
    }
    
    //Update grid possible values
    for(int i = 0; i < GRID_SIZE; ++i) {
        for(int j = 0; j < GRID_SIZE; ++j) {
            int r_idx = gridRowStart + i;
            int c_idx = gridColumnStart + j;
            if(r_idx == r || c_idx == c) continue; //Skip cells we just checked
            puzzleStillValid = updateCellAfterPlacement(r_idx,c_idx,v);
            if(!puzzleStillValid) return false;
        }
    }
    return true;
}

//This is basically just a helper function
//Removes the value "v" from cell possibilties
//When this happens we check if we can solve the square or if it's invalid
bool updateCellAfterPlacement(int r, int c, int v)
{
    cells[r][c].deletePossibleValue(v);
    int remaningPossiblities = cells[r][c].possibleValueCount();
    if(remainingPossiblities == 0) return false;
    if(remainingPossibilties == 1) {
        return setValue(r,c,cells[r][c].firstPossibleValue());
    }   
    return true;
}
*/

int SudokuBoard::getValue(int r, int c) {
    if(r >= BOARD_SIZE || r < 0 || c >= BOARD_SIZE || c < 0) return -1;
    return cells[r][c].getValue();
}

//Simple display function, puts out in the same format as input
void SudokuBoard::printBoard() {
    for(int i = 0; i < BOARD_SIZE; ++i) {
        for(int j = 0; j < BOARD_SIZE; ++j) {
            cout << cells[i][j].getValue();
			if(j != BOARD_SIZE -1) cout << ",";
        }
        cout << endl;
    }
}

bool SudokuBoard::canPlaceValue(int r, int c, int v) {
    return (checkRow(r,v) && checkColumn(c,v) && checkGrid(r,c,v));
}

bool SudokuBoard::firstEmptySquare(int * r, int * c) {
    for(int i = 0; i < BOARD_SIZE; ++i) {
        for(int j = 0; j < BOARD_SIZE; ++j) {
            if(cells[i][j].getValue() == 0) {
                *r = i; 
                *c = j;
                return true;
            }
        }
    }
    return false;
}

//Helper function for getting grid row/column start
//This works because r/3 will floor so (0-2) == 0, (3-5) = 1, (6-8) = 2
int SudokuBoard::getGridStart(int idx) {
    return (idx/GRID_SIZE) * GRID_SIZE;
}

bool SudokuBoard::checkRow(int r, int v) {
    for(int i = 0; i < BOARD_SIZE; ++i)  {
		
        if(cells[r][i].getValue() == v) return false;
    }
    return true;
}

bool SudokuBoard::checkColumn(int c, int v) {
    for(int i = 0; i < BOARD_SIZE; ++i) {
        if(cells[i][c].getValue() == v) return false;
    }
    return true;
}

bool SudokuBoard::checkGrid(int r, int c, int v) {
    int gridRowStart = getGridStart(r);
    int gridColumnStart = getGridStart(c);

    for(int i = 0; i < GRID_SIZE; ++i) {
        for(int j = 0; j < GRID_SIZE; ++j) {
            if(cells[gridRowStart+i][gridColumnStart+j].getValue() == v) return false;
        }
    }
    return true;
}

//////////////////////////////////////////////////////////
//SUDOKU CELL CODE////////////////////////////////////////
//////////////////////////////////////////////////////////
SudokuCell::SudokuCell() {
    value = 0;
    /*for(int i = 1; i < BOARD_SIZE+1; ++i) {
        possibleValues[i] = true;e
    }*/
}

SudokuCell::SudokuCell(int v) {
    value = v;
    /*for(int i = 1; i < BOARD_SIZE+1; ++i) {
        if(i == v) possibleValues[i] = true;
        else possibleValues[i] = false;
    }*/
}

int SudokuCell::getValue() {
    return value;
}

//Note: In the case of setting to 0, will allow all possible values again
//My options for this are
//  - Not allow setting back to 0/blank
//  - Allow setting to blank, but this sets all possibilities to true
//  - Just set to zero, do nothing 
// I opted for option 3 here, though all are valid for these purposes
bool SudokuCell::setValue(int v) {
    if(v < 0 || v > BOARD_SIZE) return false;
    if(v == 0) {
        value = v;
        return true;
    }
    //if(possibleValues[v] == false) return false; 

    value = v; 
    //Since this is now "set", delete all other possibilities
    /*
    for(int i = 1; i < BOARD_SIZE+1; ++i) {
        if(i == v) continue; //Skip value we're setting to
        deletePossibleValue(i);
    } */
    return true;
}

/*
void SudokuCell::addPossibleValue(int v) {
    if(v < 1 || v > BOARD_SIZE) return;
    possibleValues[v] = true;
}

void SudokuCell::deletePossibleValue(int v) {
    if(v < 1 || v > BOARD_SIZE) return;
    possibleValues[v] = false;
}

bool SudokuCell::isPossibleValue(int v) {
    if(v < 1 || v > BOARD_SIZE) return false;
    return possibleValues[v];
}

//I debated using a static counter value or a loop to calc this
//In the end I decided a loop of 9 numbers is fast enough to not complicate things
int SudokuCell::possibleValueCount() {
    int count = 0;
    for(int i = 1; i < BOARD_SIZE+1; ++i) {
        if(possibleValues[i]) ++count;
    }
    return count;
} 

int SudokuCell::firstPossibleValue() {
    for(int i = 1; i < BOARD_SIZE+i; ++i) {
        if(possibleValues[i]) return i;
    }
    return 0;
}
*/
