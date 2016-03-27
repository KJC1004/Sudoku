#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
class Sudoku{
	public:
		void readIn();
		void giveQuestion();
		void solve();
		void transform();
		void changeNum(int, int);
		void changeRow(int, int);
		void changeCol(int, int);
		void rotate(int);
		void flip(int);
	private:
		bool DFS(int);
		bool validate();
		bool check(int, int);
		void change();
		void swap(int &, int &);
		void printOut(bool);
		int grid[9][9];
};
