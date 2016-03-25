#include "Sudoku.h"
void Sudoku::giveQuestion(){
	int i, j, x, y, cnt;
	int ans[9][9] = {{1,2,3,4,5,6,7,8,9}\
			,{4,5,6,7,8,9,1,2,3}\
			,{7,8,9,1,2,3,4,5,6}\
			,{3,1,2,6,4,5,9,7,8}\
			,{6,4,5,9,7,8,3,1,2}\
			,{9,7,8,3,1,2,6,4,5}\
			,{2,3,1,5,6,4,8,9,7}\
			,{5,6,4,8,9,7,2,3,1}\
			,{8,9,7,2,3,1,5,6,4}};
	for(i=0; i<9; i++)
		for(j=0; j<9; j++){
			grid[i][j]=ans[i][j];
			ans[i][j]=0;
		}
	transform();	
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			swap(grid[i][j], ans[i][j]);	
	setPsb();
	do{
		cnt=0;
		for(i=0; i<9; i++)
			for(j=0; j<9; j++)
				grid[i][j]=0;
		setPsb();
		while(validate()!=1){
			do{
				x=rand()%9;
				y=rand()%9;
			}while(grid[x][y]!=0);
			grid[x][y]=ans[x][y];
			cnt++;
			eliminate(x, y);
		}
	}while(cnt>25);
	for(i=0; i<9 ; i++)
		for(j=0; j<9; j++)
			printf("%d%c", grid[i][j], (j!=8)?' ':'\n');
}
void Sudoku::readIn(){
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			scanf("%d", &grid[i][j]);
}
void Sudoku::solve(){//not tested
	int i, j, val, remain=81;
	setPsb();
	val=validate();
	for(i=0; i<3; i+=2)
		if(val==i){ 
			printf("%d\n", val);
			return;
		}
	while(remain!=0){
		for(i=0; i<9; i++){
			for(j=0; j<9; j++){
				if(psb[i][j].size()==1){
					grid[i][j]=psb[i][j][0];
					eliminate(i, j);
					remain--;
				}
			}
		}
	}
	for(i=0; i<9 ; i++)
		for(j=0; j<9; j++)
			printf("%d%c", grid[i][j], (j!=8)?' ':'\n');
	
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
void Sudoku::rotate(int n){
	int i, j, k;
	for(j=0; j<4; j++)
		for(k=0; k<5; k++){
			swap(grid[j][k], grid[8-k][j]);
			swap(grid[8-k][j], grid[8-j][8-k]);
			swap(grid[8-j][8-k], grid[k][8-j]);
		}	
}
void Sudoku::flip(int n){
	int i, j;
	for(i=0; i<4; i++)
		for(j=0; j<9; j++){
			if(n==0) swap(grid[i][j], grid[8-i][j]);
			else	 swap(grid[j][i], grid[j][8-i]);
		}
}
void Sudoku::transform(){
	srand(time(NULL));
	for(int i=0; i<1000; i++){
		changeNum(rand()%9+1, rand()%9+1);
		changeRow(rand()%3, rand()%3);
		changeCol(rand()%3, rand()%3);
		rotate(rand()%4);
		flip(rand()%2);
	}
}
void Sudoku::setPsb(){
	int i, j, k;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++){
			psb[i][j].clear();
			if(grid[i][j]!=0)
				psb[i][j].push_back(grid[i][j]);
			else	
				for(k=0; k<9;)
					psb[i][j].push_back(++k);
		}
}
int Sudoku::validate(){
	int i, j, k, l, m, n;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			if(grid[i][j]!=0 && !check(i, j))
				return 0;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			for(k=1; j+k<9; k++)
				if(psb[i][j]==psb[i][j+k] || psb[j][i]==psb[j+k][i])
					return 2;
	for(i=0; i<9; i+=3)
	for(j=0; j<9; j+=3)
		for(k=0; k<3; k++)
		for(l=0; l<3; l++)
			for(m=0; m+k<3; m++)
			for(n=0; n+l<3; n++){
				if(m==0 && n==0) continue;
				if(psb[i+k][j+l]==psb[i+k+m][j+l+n])
					return 2;
			}
	return 1;
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
void Sudoku::eliminate(int x, int y){
	int i, j, k, csx=(x/3)*3, csy=(y/3)*3;
	psb[x][y].clear();
	psb[x][y].push_back(grid[x][y]);
	for(i=0; i<9; i++){
		if(psb[i][y].size()==1) continue;
		for(j=0; j<psb[i][y].size(); j++){
			if(psb[i][y][j]==grid[x][y]){
				psb[i][y].erase(psb[i][y].begin()+j);
				break;
			}
		}
	}
	for(i=0; i<9; i++){
		if(psb[x][i].size()==1) continue;
		for(j=0; j<psb[x][i].size(); j++){
			if(psb[x][i][j]==grid[x][y]){
				psb[x][i].erase(psb[x][i].begin()+j);
				break;
			}
		}
	}
	for(i=csx; i<csx+3; i++){
		for(j=csy; j<csy+3; j++){
			if(psb[i][j].size()==1) continue;
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
