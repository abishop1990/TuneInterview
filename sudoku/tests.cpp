/* tests.cpp
 *
 * Tests for sudoku solver
 * Since this is just a demo project, I'm opting for high level tests only
 * (I would typically write tests for each class and lower level tests)
 * 
 * Written by Alan Bishop 1/31/2016
 */

#include <iostream>
#include <fstream>

#include "sudoku.h"

using namespace std;

void logFailure(string testName, string msg);
bool readPuzzleFile(string testName, string fileName, int (* values) [BOARD_SIZE][BOARD_SIZE]) ;
bool testSolvesPuzzle(string testName, string fileName);
bool testFailsPuzzle(string testName, string fileName);

int main(int argc, char * argv []) {
	int testCount = 0, failCount = 0;
	bool success;

	cout << "Running puzzle tests..." << endl;

	cout << "Testing can solve blank puzzle" << endl;
	success = testSolvesPuzzle("Solves blank puzzle", "data/blank.csv");
	++testCount; if(!success) ++failCount;
	cerr << (success ? "Successfully solved blank puzzle" : "Failed on solving blank puzzle") << endl;

	cout << "Testing can solve easy puzzle" << endl;
	success = testSolvesPuzzle("Solves easy puzzle", "data/valid_1.csv");
	++testCount; if(!success) ++failCount;
	cerr << (success ? "Successfully solved easy puzzle" : "Failed on solving easy puzzle") << endl;
	
	cout << "Testing can solve hard puzzle" << endl;
	success = testSolvesPuzzle("Solves hard puzzle", "data/valid_2.csv");
	++testCount; if(!success) ++failCount;
	cerr << (success ? "Successfully solved hard puzzle" : "Failed on solving hard puzzle") << endl;
	
	cout << "Testing fails on invalid puzzle" << endl;
	success = testFailsPuzzle("Solves fails on invalid puzzle", "data/invalid.csv");
	++testCount; if(!success) ++failCount;
	cerr << (success ? "Properly fails on invalid puzzle" : "Solved invalid puzzle") << endl;

	if(failCount == 0) cout << "All puzzle tests passed" << endl;
	else cout << failCount << " tests failed" << endl;

	return 0;
}

//Simple convienence method for logging purposes
//We do a similar thing at my current company
void logFailure(string testName, string msg) {
	cout << "Failure in " << testName << ": " << msg << endl;
}	

//Pass/fail on the puzzle reading okay
bool readPuzzleFile(string testName, string fileName, int (* values) [BOARD_SIZE][BOARD_SIZE]) {
	ifstream in;
	in.open(fileName.c_str());
	if(!in) { 
		logFailure(testName, "Couldn't open file '" + fileName + "'");
		return false; 
	}
	if(readBoard(in,values) == false) {
		logFailure(testName, "File '" + fileName + "' contained invalid data");
		return false;
	}
	return true;
}

bool testSolvesPuzzle(string testName, string fileName) {
	int puzzleArray[BOARD_SIZE][BOARD_SIZE];
	if(readPuzzleFile(testName,fileName, &puzzleArray) == false) return false;
	
	SudokuPuzzle puzzle = SudokuPuzzle(puzzleArray);
	if(puzzle.solve() == false) {
		logFailure(testName, "Puzzle couldn't be solved");
		cout << "Puzzle read in:" << endl;
		puzzle.printInitialBoard();
		return false;
	}
	return true;
}

bool testFailsPuzzle(string testName, string fileName) {
	int puzzleArray[BOARD_SIZE][BOARD_SIZE];
	if(readPuzzleFile(testName,fileName, &puzzleArray) == false) return false;
	
	SudokuPuzzle puzzle = SudokuPuzzle(puzzleArray);
	if(puzzle.solve() == true) {
		logFailure(testName, "Puzzle found a solution when it shouldn't");
		cout << "Puzzle read in:" << endl;
		puzzle.printInitialBoard();
		cout << "\nPuzzle solution:" << endl;
		puzzle.printSolvedBoard();
		return false;
	}
	return true;
}
