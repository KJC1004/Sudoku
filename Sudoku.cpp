#include "Sudoku.h"
void Sudoku::giveQuestion(){
	int i, j;
	const int ans[9][9]={{1,2,3,4,5,6,7,8,9}\
			    ,{4,5,6,7,8,9,1,2,3}\
			    ,{7,8,9,1,2,3,4,5,6}\
			    ,{3,1,2,6,4,5,9,7,8}\
			    ,{6,4,5,9,7,8,3,1,2}\
			    ,{9,7,8,3,1,2,6,4,5}\
			    ,{2,3,1,5,6,4,8,9,7}\
			    ,{5,6,4,8,9,7,2,3,1}\
			    ,{8,9,7,2,3,1,5,6,4}};
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			grid[i][j]=ans[i][j];
	transform();
	//if(!validate()) return;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			printf("%d%c", grid[i][j], (j!=8)?' ':'\n');
}
void Sudoku::readIn(){
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			scanf("%d", &grid[i][j]);
}
void Sudoku::solve(){//not tested, might have solved multi-answers
	bool stuck=false;
	if(!validate()) return;
	int i, j, k, remain=81;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++){
			if(grid[i][j]!=0)
				psb[i][j].push_back(grid[i][j]);
			else	
				for(k=0; k<9;)
					psb[i][j].push_back(++k);
		}
	while(remain!=0 && !stuck){
		stuck=true;
		for(i=0; i<9; i++){
			for(j=0; j<9; j++){
				if(psb[i][j].size()==1){
					grid[i][j]=psb[i][j][0];
					psb[i][j].clear();
					eliminate(i, j);
					remain--;
					stuck=false;
				}
			}
		}
	}
	if(stuck){
		printf("2\n");
		return;
	}
	for(i=0; i<9; i++){
		for(j=0; j<9; j++)
			printf("%d%c", grid[i][j], (j==8)?'\n':' ');
	}
}
void Sudoku::changeNum(int a, int b){
	if(a==b) return;
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++){
			if(grid[i][j]==a) grid[i][j]=b;
			else if(grid[i][j]==b) grid[i][j]=a;
		}
}
void Sudoku::changeRow(int a, int b){
	if(a==b) return;
	int i, j;
	a*=3; b*=3;
	for(i=0; i<3; i++, a++, b++)
		for(j=0; j<9; j++)
			swap(grid[a][j], grid[b][j]);
}
void Sudoku::changeCol(int a, int b){
	if(a==b) return;
	int i, j;
	a*=3; b*=3;
	for(i=0; i<3; i++, a++, b++)
		for(j=0; j<9; j++)
			swap(grid[j][a], grid[j][b]);
}
void Sudoku::rotate(int n){//not tested
	int i, j, k, tmp[4][5];
}
void Sudoku::flip(int n){
	int i, j;
	for(i=0; i<4; i++)
		for(j=0; j<9; j++){
			if(n==0)
				swap(grid[i][j], grid[8-i][j]);
			else
				swap(grid[j][i], grid[j][8-i]);
		}
}
void Sudoku::transform(){
	srand(time(NULL));
	int i;
	for(i=0; i<1000; i++){
		changeNum(rand()%9+1, rand()%9+1);
		changeRow(rand()%3, rand()%3);
		changeCol(rand()%3, rand()%3);
		//rotate(rand()%4);
		flip(rand()%2);
	}
}
bool Sudoku::validate(){
	int i, j;
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			if(grid[i][j]!=0 && !check(i, j)){
				printf("0\n");	
				return false;
			}
		}
	}
	printf("1\n");
	return true;
}
bool Sudoku::check(int x, int y){
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
		if(psb[i][y].empty()) continue;
		for(j=0; j<psb[i][y].size(); j++){
			if(psb[i][y][j]==grid[x][y]){
				psb[i][y].erase(psb[i][y].begin()+j);
				break;
			}
		}
	}
	for(i=0; i<9; i++){
		if(psb[x][i].empty()) continue;
		for(j=0; j<psb[x][i].size(); j++){
			if(psb[x][i][j]==grid[x][y]){
				psb[x][i].erase(psb[x][i].begin()+j);
				break;
			}
		}
	}
	for(i=csx; i<csx+3; i++){
		for(j=csy; j<csy+3; j++){
			if(psb[i][j].empty()) continue;
			for(k=0; k<psb[i][j].size(); k++){
				if(psb[i][j][k]==grid[x][y]){
					psb[i][j].erase(psb[i][j].begin()+k);
					break;
				}
			}
		}
	}
}
void Sudoku::swap(int &a, int &b){
	int tmp;
	tmp=a;
	a=b;
	b=tmp;
}
