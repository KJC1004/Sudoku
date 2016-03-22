#include "Sudoku.h"
void Sudoku::giveQuestion(){
	srand(time(NULL));
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			grid[i][j]=0;	
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			do{
				grid[i][j]=rand()%9+1;
			}while(!check(i, j));
			cout << " " << grid[i][j];
		}
		cout << endl;
	}
	return;
}
void Sudoku::readIn(){
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			cin >> grid[i][j];
	return;
}
void Sudoku::solve(){
}
void Sudoku::changeNum(int, int){
}
void Sudoku::changeRow(int, int){
}
void Sudoku::changeCol(int, int){
}
void Sudoku::rotate(int){
}
void Sudoku::flip(int){
}
void Sudoku::transform(){
}
bool Sudoku::validate(){
}
bool Sudoku::check(int x, int y){
	int i, j, c_x=(x/3)*3, c_y=(y/3)*3;
	for(i=0; i<9; i++){
		if(i==x) continue;
		if(grid[i][y]==grid[x][y]) return false;
	}
	for(j=0; j<9; j++){
		if(j==y) continue;
		if(grid[x][j]==grid[x][y]) return false;
	}
	for(i=c_x; i<c_x+3; i++){
		if(i==x) continue;
		for(j=c_y; j<c_y+3; j++){
			if(j==y) continue;
			if(grid[i][j]==grid[x][y]) return false;
		}
	}
	return true;
}
