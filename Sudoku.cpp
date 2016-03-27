#include "Sudoku.h"
void Sudoku::readIn(){
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			scanf("%d", &grid[i][j]);
}
void Sudoku::giveQuestion(){
	srand(time(NULL));
	int i, j, cnt=0;
	int ans[9][9] = {{1,2,3,4,5,6,7,8,9}\
			,{4,5,6,7,8,9,1,2,3}\
			,{7,8,9,1,2,3,4,5,6}\
			,{3,1,2,6,4,5,9,7,8}\
			,{6,4,5,9,7,8,3,1,2}\
			,{9,7,8,3,1,2,6,4,5}\
			,{2,3,1,5,6,4,8,9,7}\
			,{5,6,4,8,9,7,2,3,1}\
			,{8,9,7,2,3,1,5,6,4}};
	//randomize the answer
	for(i=0; i<9; i++)
		for(j=0; j<9; j++){
			grid[i][j]=ans[i][j];
			ans[i][j]=0;
		}
	change();	
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			swap(grid[i][j], ans[i][j]);
	//fill in the answer randomly
	//prevent multi-solution by DFS(mode:check)
	while(cnt<30 || !DFS(1)){
		do{
			i=rand()%9;
			j=rand()%9;
		}while(grid[i][j]!=0);
		grid[i][j]=ans[i][j];
		cnt++;
	}
	printOut(true);
}
void Sudoku::solve(){
	if(!validate()) return;
	printOut(DFS(0));
}
void Sudoku::transform(){
	change();
	printOut(true);
}
void Sudoku::changeNum(int a, int b){
	if(a==b) return;
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++){
			if(grid[i][j]==a)	grid[i][j]=b;
			else if(grid[i][j]==b)	grid[i][j]=a;
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
	int i, j;
	for(n%=4; n>0; n--)
		for(i=0; i<4; i++)
			for(j=0; j<5; j++){
				swap(grid[i][j], grid[8-j][i]);
				swap(grid[8-j][i], grid[8-i][8-j]);
				swap(grid[8-i][8-j], grid[j][8-i]);
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
bool Sudoku::DFS(int mode){
	//mode 0: solve
	//mode 1: check
	int i, j, loc, dir, tmp_q[9][9], tmp_a[9][9];
	bool onlySol=true, confirm[9][9];
	//initialize data for DFS(low)
	for(i=0; i<9; i++)
		for(j=0; j<9; j++){
			if(grid[i][j]!=0) confirm[i][j]=true;
			else		  confirm[i][j]=false;
			tmp_q[i][j]=grid[i][j];
		}
	//DFS(low)
	for(loc=0, dir=1; loc<81; loc+=dir){
		i=loc/9; j=loc%9;
		if(confirm[i][j]) continue;
		if(dir==-1) dir=1;
		do{grid[i][j]++;}while(!check(i, j));
		if(grid[i][j]>9){
			grid[i][j]=0;
			dir=-1;
		}
	}
	//store the answer for comparing
	//initialize data for DFS(high)
	for(i=0; i<9; i++)
		for(j=0; j<9; j++){
			tmp_a[i][j]=grid[i][j];
			grid[i][j]=tmp_q[i][j];
			if(grid[i][j]==0) grid[i][j]=10;
		}
	//DFS(high)
	for(loc=0, dir=1; loc<81; loc+=dir){
		i=loc/9; j=loc%9;
		if(confirm[i][j]) continue;
		if(dir==-1) dir=1;
		do{grid[i][j]--;}while(!check(i, j));
		if(grid[i][j]<1){
			grid[i][j]=10;
			dir=-1;
		}
	}
	//(answer match)?(only-solution):(multi-solution);
	for(i=0; i<81; i++)
		if(grid[i/9][i%9]!=tmp_a[i/9][i%9]){
			onlySol=false;
			break;
		}
	if(mode==0){
		if(onlySol) printf("1\n");
		else	    printf("2\n");
	}
	else
		for(i=0; i<9; i++)
			for(j=0; j<9; j++)
				grid[i][j]=tmp_q[i][j];
	return onlySol;
}
bool Sudoku::validate(){
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			if(grid[i][j]!=0 && !check(i, j)){
				printf("0\n");
				return false;
			}
	return true;
}
bool Sudoku::check(int x, int y){
	int i, j, csx=(x/3)*3, csy=(y/3)*3;
	//check column
	for(i=0; i<9; i++){
		if(i==x) continue;
		if(grid[i][y]==grid[x][y]) return false;
	}
	//check row
	for(i=0; i<9; i++){
		if(i==y) continue;
		if(grid[x][i]==grid[x][y]) return false;
	}
	//check cell
	for(i=csx; i<csx+3; i++){
		if(i==x) continue;
		for(j=csy; j<csy+3; j++){
			if(j==y) continue;
			if(grid[i][j]==grid[x][y]) return false;
		}
	}
	return true;
}
void Sudoku::change(){
	srand(time(NULL));
	for(int i=0; i<100; i++){
		changeNum(rand()%9+1, rand()%9+1);
		changeRow(rand()%3, rand()%3);
		changeCol(rand()%3, rand()%3);
		rotate(rand()%4);
		flip(rand()%2);
	}
}
void Sudoku::swap(int &a, int &b){
	int tmp;
	tmp=a;
	a=b;
	b=tmp;
}
void Sudoku::printOut(bool onlySol){
	if(!onlySol) return;
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			printf("%d%c", grid[i][j], (j!=8)?' ':'\n');
}
