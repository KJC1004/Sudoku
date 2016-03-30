#include "Sudoku.h"
void Sudoku::readIn(){
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			scanf("%d", &grid[i][j]);
}
void Sudoku::giveQuestion(){
	srand(time(NULL));
	int i, j, cnt;
	int ans[9][9] = {{1,2,3,4,5,6,7,8,9}\
			,{4,5,6,7,8,9,1,2,3}\
			,{7,8,9,1,2,3,4,5,6}\
			,{2,1,4,3,6,5,8,9,7}\
			,{3,6,5,8,9,7,2,1,4}\
			,{8,9,7,2,1,4,3,6,5}\
			,{5,3,1,6,4,2,9,7,8}\
			,{6,4,2,9,7,8,5,3,1}\
			,{9,7,8,5,3,1,6,4,2}};
	//random answer
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
	//prevent multi-solution by backTrack(mode:check)
	do{
		for(i=0; i<9; i++)
			for(j=0; j<9; j++)
				grid[i][j]=0;
		cnt=0;
		while(cnt<30 || !backTrack(1)){
			do{
				i=rand()%9;
				j=rand()%9;
			}while(grid[i][j]!=0);
			grid[i][j]=ans[i][j];
			cnt++;
		}
	}while(cnt>40);
	printOut(true);
}
void Sudoku::solve(){
	if(!validate()) return;
	printOut(backTrack(0));
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
bool Sudoku::backTrack(int mode){
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
	initUsed(0);
	//backtrack(low)
	for(loc=0, dir=1; loc<=80; loc+=dir){
		i=loc/9; j=loc%9;
		if(confirm[i][j]) continue;
		if(dir==-1) dir=1;
		if(grid[i][j]>0)  setUsed(i, j, grid[i][j], false);
		do{ grid[i][j]++;}while(used(i, j, grid[i][j]));
		if(grid[i][j]<10) setUsed(i, j, grid[i][j], true);
		else{ grid[i][j]=0; dir=-1;}
	}
	//store the answer for comparing
	//initialize data for backtrack(high)
	for(i=0; i<9; i++)
		for(j=0; j<9; j++){
			tmp_a[i][j]=grid[i][j];
			grid[i][j] = (tmp_q[i][j]!=0)? tmp_q[i][j]: 10;
		}
	initUsed(0);
	//backtrack(high)
	for(loc=0, dir=1; loc<=80; loc+=dir){
		i=loc/9; j=loc%9;
		if(confirm[i][j]) continue;
		if(dir==-1) dir=1;
		if(grid[i][j]<10) setUsed(i, j, grid[i][j], false);
		do{ grid[i][j]--;}while(used(i, j, grid[i][j]));
		if(grid[i][j]>0)  setUsed(i, j, grid[i][j], true);
		else{ grid[i][j]=10; dir=-1;}
	}
	//(answer match)?(only-solution):(multi-solution);
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			if(grid[i][j]!=tmp_a[i][j]){
				onlySol=false;
				break;
			}
		}
		if(!onlySol) break;
	}
	if(mode==0)
		printf("%d\n", onlySol? 1: 2);
	else
		for(i=0; i<9; i++)
			for(j=0; j<9; j++)
				grid[i][j]=tmp_q[i][j];
	return onlySol;
}
bool Sudoku::validate(){
	int i, j;
	initPsb();
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			if(grid[i][j]!=0){
				if(!psb[i][j][grid[i][j]]){
					printf("0\n");
					return false;
				}
				elmPsb(i, j, grid[i][j]);
			}
	if(checkPsb()) return true;
	else{ printf("0\n"); return false;}	
}
void Sudoku::initPsb(){
	int i, j, n;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			for(n=1; n<10; n++)
				psb[i][j][n]=true;
}
void Sudoku::elmPsb(int x, int y, int n){
	int i, j, csx=x/3*3, csy=y/3*3;
	for(i=0; i<9; i++){
		psb[x][i][n]=false;
		psb[i][y][n]=false;
	}
	for(i=csx; i<csx+3; i++)
	for(j=csy; j<csy+3; j++)
		psb[i][j][n]=false;
}
bool Sudoku::checkPsb(){
	int i, j, k, l, n, space;
	bool exec;
	for(n=1; n<10; n++){
		for(i=0; i<9; i++){
			for(j=0, space=0, exec=false; j<9; j++)
				if(psb[i][j][n]){
					exec=true;
					space++;
					if(grid[i][j]!=0) space--;
				}
			if(space==0 && exec) return false;
			for(j=0, space=0, exec=false; j<9; j++)
				if(psb[j][i][n]){
					exec=true;
					space++;
					if(grid[j][i]!=0) space--;
				}
			if(space==0 && exec) return false;
		}
		for(i=0; i<9; i+=3){
		for(j=0; j<9; j+=3){
			for(k=i, space=0, exec=false; k<i+3; k++){
			for(l=j; l<j+3; l++){
				if(psb[k][l][n]){
					exec=true;
					space++;
					if(grid[k][l]!=0) space--;
				}	
			}
			}
			if(space==0 && exec) return false;
		}
		}
	}
	return true;		
}
void Sudoku::initUsed(int mode){
	//mode 0: normal
	//mode 1: validate
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<11; j++){
			rowUsed[i][j]=false;
			colUsed[i][j]=false;
			cellUsed[i/3][i%3][j]=false;			
		}
	if(mode==0)
		for(i=0; i<9; i++)
			for(j=0; j<9; j++)
				if(grid[i][j]!=0)
					setUsed(i, j, grid[i][j], true);
}
void Sudoku::setUsed(int x, int y, int n, bool use){
	rowUsed[x][n]=use;
	colUsed[y][n]=use;
	cellUsed[x/3][y/3][n]=use;	
}
bool Sudoku::used(int x, int y, int n){
	if(n<1 || n>9) return false;
	return (rowUsed[x][n] || colUsed[y][n] || cellUsed[x/3][y/3][n])? true: false;
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
