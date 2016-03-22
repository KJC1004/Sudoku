giveQuestion: Sudoku.o giveQuestion.cpp
	g++ -o giveQuestion giveQuestion.cpp Sudoku.o
	
solve: Sudoku.o solve.cpp
	g++ -o solve solve.cpp Sudoku.o

transform: Sudoku.o transform.cpp
	g++ -o transform transform.cpp Sudoku.o

Sudoku.o: Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp

clean:
	rm *.exe *.o
