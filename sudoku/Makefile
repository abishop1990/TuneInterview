solve: solve.o sudoku.o sudoku.h
	g++ -o solve solve.o sudoku.o

solve.o: sudoku.o solve.cpp sudoku.h
	g++ -c solve.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -c sudoku.cpp

clean: 
	rm -f solve solve.o sudoku.o
