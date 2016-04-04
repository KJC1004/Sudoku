#include "Sudoku.h"
void Sudoku::readIn(){
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			scanf("%d", &grid[i][j]);
}
/*void Sudoku::giveQuestion(){
	int ans[9][9] = {{0,0,0,0,0,0,0,0,0}\
			,{0,0,0,0,0,0,0,0,0}\
			,{0,0,0,0,0,0,0,0,0}\
			,{0,0,0,0,0,0,0,0,0}\
			,{0,0,0,0,0,0,0,0,0}\
			,{0,0,0,0,0,0,0,0,0}\
			,{0,0,1,0,0,0,0,0,0}\
			,{0,0,0,0,0,1,0,0,0}\
			,{0,0,0,0,0,0,2,3,4}};	
	int ans[9][9] = {{0,0,0,0,0,0,0,1,0}\
			,{4,0,0,0,0,0,0,0,0}\
			,{0,2,0,0,0,0,0,0,0}\
			,{0,0,0,0,5,0,4,0,7}\
			,{0,0,8,0,0,0,3,0,0}\
			,{0,0,1,0,9,0,0,0,0}\
			,{3,0,0,4,0,0,2,0,0}\
			,{0,5,0,1,0,0,0,0,0}\
			,{0,0,0,8,0,6,0,0,0}};
	for(int i=0; i<9; i++)
		for(int j=0; j<9; j++)
			printf("%d%c", ans[i][j], (j!=8)?' ':'\n');
}*/
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
			ans[i][j]=grid[i][j];
	//fill in the answer randomly
	//prevent multi-solution by answer()
	do{
		for(i=0; i<9; i++)
			for(j=0; j<9; j++)
				grid[i][j]=0;
		cnt=0;
		while(cnt<30 || !answer(1)){
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
	printOut(answer(0));
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
bool Sudoku::answer(int mode){
	//mode 0: solve
	//mode 1: check
	int i, j, last, tmp[9][9];
	bool onlySol=true;
	if(mode==1)
		for(i=0; i<9; i++)
			for(j=0; j<9; j++)
				tmp[i][j]=grid[i][j];
	initPsb(0);
	while(remain>0){
		last=remain;
		PSB();
		if(remain==last) break;
	}
	if(remain>0) onlySol=backTrack();
	if(mode==0)
		printf("%d\n", onlySol? 1: 2);
	else
		for(i=0; i<9; i++)
			for(j=0; j<9; j++)
				grid[i][j]=tmp[i][j];
	return onlySol;
}
bool Sudoku::validate(){
	int i, j;
	initPsb(1);
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			if(grid[i][j]!=0){
				if(psb[i][j][grid[i][j]]==false){
					printf("0\n");
					return false;
				}
				elmPsb(i, j, grid[i][j], 1);
			}
	if(checkPsb()) return true;
	else{ printf("0\n"); return false;}	
}
void Sudoku::PSB(){
	int i, j, k, l, x, y, N, cnt;
	//onlyPsb
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			if(psb_rem[i][j]==1){
				for(N=1; !psb[i][j][N]; N++);
				elmPsb(i, j, N, 0);
			}
	//lonePsb
	for(i=0; i<9; i++)
		for(N=1; N<10; N++){
			for(j=0, cnt=0; (j<9 && cnt<=1); j++)
				if(psb[i][j][N]){cnt++; y=j;}
			if(cnt==1) elmPsb(i, y, N, 0);
			for(j=0, cnt=0; (j<9 && cnt<=1); j++)
				if(psb[j][i][N]){cnt++; x=j;}
			if(cnt==1) elmPsb(x, i, N, 0);
		}
	for(i=0; i<9; i+=3)
	for(j=0; j<9; j+=3)
		for(N=1; N<10; N++){
			for(k=i, cnt=0; (k<i+3 && cnt<=1); k++)
			for(l=j; (l<j+3 && cnt<=1); l++)
				if(psb[k][l][N]){cnt++; x=k; y=l;}
			if(cnt==1) elmPsb(x, y, N, 0);
		}
}
void Sudoku::initPsb(int mode){
	//mode 0: normal
	//mode 1: validate
	int i, j, N;
	remain=81;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++){
			psb_rem[i][j]=9;
			psb[i][j][0]=false;
			for(N=1; N<10; N++)
				psb[i][j][N]=true;
		}
	if(mode==0)
		for(i=0; i<9; i++)
			for(j=0; j<9; j++)
				if(grid[i][j]!=0)
					elmPsb(i, j, grid[i][j], 0);
}
void Sudoku::elmPsb(int x, int y, int N, int mode){
	//mode 0: normal
	//mode 1: check
	int i, j, n, csx=x/3*3, csy=y/3*3;
	remain--;
	grid[x][y]=N;
	psb_rem[x][y]=0;
	if(mode==0)
		for(n=1; n<10; n++)
			psb[x][y][n]=false;
	for(i=0; i<9 ; i++){
		if(psb[x][i][N]){
			psb[x][i][N]=false;
			psb_rem[x][i]--;
		}
		if(psb[i][y][N]){
			psb[i][y][N]=false;
			psb_rem[i][y]--;
		}
	}
	for(i=csx; i<csx+3; i++)
	for(j=csy; j<csy+3; j++)
			if(psb[i][j][N]){
				psb[i][j][N]=false;
				psb_rem[i][j]--;
			}
}
bool Sudoku::checkPsb(){
	int i, j, k, l, N, space;
	bool exec;
	for(N=1; N<10; N++){
		for(i=0; i<9; i++){
			for(j=0, space=0, exec=false; j<9; j++)
				if(psb[i][j][N]){
					exec=true;
					space++;
					if(grid[i][j]!=0) space--;
				}
			if(space==0 && exec) return false;
			for(j=0, space=0, exec=false; j<9; j++)
				if(psb[j][i][N]){
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
				if(psb[k][l][N]){
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
void Sudoku::change(){
	srand(time(NULL));
	for(int i=0; i<10; i++){
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
bool Sudoku::backTrack(){
	int i, j, loc, dir, tmp_q[9][9], tmp_a[9][9];
	bool onlySol=true, confirm[9][9];
	//initialize data for DFS(low)
	for(i=0; i<9; i++)
		for(j=0; j<9; j++){
			if(grid[i][j]!=0) confirm[i][j]=true;
			else		  confirm[i][j]=false;
			tmp_q[i][j]=grid[i][j];
		}
	initUsed();
	//backtrack(low)
	for(loc=0, dir=1; loc<=80; loc+=dir){
		i=loc/9; j=loc%9;
		if(confirm[i][j]) continue;
		dir=1;
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
			grid[i][j]=(tmp_q[i][j]!=0)? tmp_q[i][j]: 10;
		}
	initUsed();
	//backtrack(high)
	for(loc=0, dir=1; loc<=80; loc+=dir){
		i=loc/9; j=loc%9;
		if(confirm[i][j]) continue;
		dir=1;
		if(grid[i][j]<10) setUsed(i, j, grid[i][j], false);
		do{ grid[i][j]--;}while(used(i, j, grid[i][j]));
		if(grid[i][j]>0)  setUsed(i, j, grid[i][j], true);
		else{ grid[i][j]=10; dir=-1;}
	}
	//(answer match)?(only-solution):(multi-solution);
	for(i=0; i<=80; i++)
		if(grid[i/9][i%9]!=tmp_a[i/9][i%9]){
			onlySol=false;
			break;
		}
	return onlySol;
}
void Sudoku::initUsed(){
	int i, j;
	for(i=0; i<9; i++)
		for(j=0; j<11; j++){
			rowUsed[i][j]=false;
			colUsed[i][j]=false;
			cellUsed[i/3][i%3][j]=false;			
		}
	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			if(grid[i][j]>0 && grid[i][j]<10)
				setUsed(i, j, grid[i][j], true);
}
void Sudoku::setUsed(int x, int y, int n, bool use){
	rowUsed[x][n]=use;
	colUsed[y][n]=use;
	cellUsed[x/3][y/3][n]=use;	
}
bool Sudoku::used(int x, int y, int n){
	if(n<1 || n>9) return false;
	return (rowUsed[x][n] || colUsed[y][n] || cellUsed[x/3][y/3][n]);
}
