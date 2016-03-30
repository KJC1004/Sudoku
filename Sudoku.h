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
		bool backTrack(int);
		bool validate();
		void initPsb();
		void elmPsb(int, int, int);
		bool checkPsb();
		void initUsed(int);
		void setUsed(int, int, int, bool);
		bool used(int, int, int);
		void change();
		void swap(int &, int &);
		void printOut(bool);
		int grid[9][9];
		bool rowUsed[9][11], colUsed[9][11], cellUsed[3][3][11], psb[9][9][10];
};
