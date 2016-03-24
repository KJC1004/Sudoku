#include "Sudoku.h"
void Sudoku::giveQuestion(){//something wrong with check()?
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
void Sudoku::solve(){//not tested
	if(!validate()){ cout << 0 << endl; return;}
	int i, j, k, remain=81;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++){
			if(grid[i][j]!=0)
				psb[i][j].push_back(grid[i][j]);
			else	
				for(k=0; k<9;)
					psb[i][j].push_back(++k);
		}
	while(remain!=0){
		for(i=0; i<9; i++){
			for(j=0; j<9; j++){
				if(psb[i][j].size()==1){
					grid[i][j]=psb[i][j][0];
					remain--;
					psb[i][j].clear();
					eliminate(i, j);
				}
			}	
		}
	}
	for(i=0; i<9; i++){
		for(j=0; j<9; j++)
			cout << " " << grid[i][j];
		cout << endl;
	}
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
	int i, j;
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			if(grid[i][j]!=0 && !check(i, j)){
				cout << 0 << endl;
				return false;
			}
		}
	}
	cout << 1 << endl;
	return true;
}
bool Sudoku::check(int x, int y){//something wrong?
	int i, j, csx=(x/3)*3, csy=(y/3)*3;
	for(i=0; i<9; i++){
		if(i==x) continue;
		if(grid[i][y]==grid[x][y]) return false;
	}
	for(i=0; i<9; i++){
		if(i==y) continue;
		if(grid[x][i]==grid[x][y]) return false;
	}
	for(i=csx; i<csx+3; i++){
		if(i==x) continue;
		for(j=csy; j<csy+3; j++){
			if(j==y) continue;
			if(grid[i][j]==grid[x][y]) return false;
		}
	}
	return true;
}
void Sudoku::eliminate(int x, int y){//not tested
	int i, j, k, csx=(x/3)*3, csy=(y/3)*3;
	for(i=0; i<9; i++){
		if(i==x || psb[i][y].empty()) continue;
		for(j=0; j<psb[i][y].size(); j++){
			if(psb[i][y][j]==grid[x][y]){
				psb[i][y].erase(psb[i][y].begin()+j);
				break;
			}
		}
	}
	for(i=0; i<9; i++){
		if(i==y || psb[x][i].empty()) continue;
		for(j=0; j<psb[x][i].size(); j++){
			if(psb[x][i][j]==grid[x][y]){
				psb[x][i].erase(psb[x][i].begin()+j);
				break;
			}
		}
	}
	for(i=csx; i<csx+3; i++){
		if(i==x) continue;
		for(j=csy; j<csy+3; j++){
			if(j==y || psb[i][j].empty()) continue;
			for(k=0; k<psb[i][j].size(); k++){
				if(psb[i][j][k]==grid[x][y]){
					psb[i][j].erase(psb[i][j].begin()+k);
					break;
				}
			}
		}
	}
	return;
}
