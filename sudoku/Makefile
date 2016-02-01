all: solve tests

solve: solve.o sudoku.o sudoku.h
	g++ -o solve solve.o sudoku.o

tests: tests.o sudoku.o sudoku.h
	g++ -o tests tests.o sudoku.o

tests.o: sudoku.o tests.cpp sudoku.h
	g++ -c tests.cpp

solve.o: sudoku.o solve.cpp sudoku.h
	g++ -c solve.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -c sudoku.cpp

clean: 
	rm -f solve tests solve.o sudoku.o tests.o
