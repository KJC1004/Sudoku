#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
class Sudoku{
	public:
		void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int, int);
		void changeRow(int, int);
		void changeCol(int, int);
		void rotate(int);
		void flip(int);
		void transform();
		bool validate();
		bool check(int, int);
		void eliminate(int, int);
	private:
		int grid[9][9];
		vector<int> psb[9][9];	
};
