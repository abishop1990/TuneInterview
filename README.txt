Notes for running:

Makefile will build both the solve and tests programs. You don't need anything besides standard g++

To run tests just type ./tests

To run the solver, provide input from stdin or pipe in a file (I've provided some in sudoku/data)
Ex: ./solve < data/tests


Thought process:

I handled solving the sudoku puzzles using a backtracking algorithm, where each possible
value for a square is tried. A value is inserted in the first available blank square, and
then the solve function is recursively called with that value placed. This is repeated for
each value until a solution is found, or a square is found where no value is possible, in 
which case the puzzle can't be solved.

This isn't the fastest algorithm for solving a sudoku, but  it works very fast on any puzzles
I've tried, so I'm satisfied with the solution. I had a thought of using an array of 
possibilities for each cell (the code for this is still in the source commented out), but I
found the implementation to be messy combining this with backtracking since you have to reset
the possiblity arrays for each cell after you return out from a recursive call to solve which 
fails. 


I created some ability for flexibility in board size using the GRID_SIZE and BOARD_SIZE
variables, so if you movidied GRID_SIZE from 3, you could create different sizes of boards.
This would require you to use the correct size of .csv data input, but should work the same.


Design struggles:

My first struggle was in picking a language. I ended up choosing C++, which caused me
some extra overhead in dealing with some language shortcomings, though I wanted to work
in C++ simply because I haven't in a while. If I were to do this again, I probably would
have done this in a language like Python or Ruby which provides some built in routines that
would have reduced code bloat.

I take some issue with doing this in an object-oriented way. This was asked for in the 
spec provided though, so I intentionally created a Cell class, Board class and Puzzle
class, where I feel that just using an array for the board would have been less overhead.
I also wasn't clear what was meant by "object oriented" so I could've created an inheritance
based design with a SudokuBoard which inherits from Board and SudokuPuzzle that inherits from
Puzzle, or perhaps specified it as a 9x9 sudoku board. 

As far as tests go, I didn't want to spend an excessive amount of time on tests, so I opted
to only write high level tests which test different types of puzzles (blank, easy, hard, invalid).
My tests don't check against correct solutions which might have been a nice thing to add as well. 


Complexity:

The worst-case runtime of this is O(n^m) where m is the board size, as well as possibilities for
each square. This obviously is a slow algorithm if used on a large sudoku board, but since a typical
sudoku is 9x9, this doesn't end up being a major issue unless you're solving large numbers of sudoku
puzzles. Easier puzzles (ones with lots of filled in squares in the csv) will take exponentially less
time than harder puzzles. 
