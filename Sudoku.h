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
		bool answer(int);
		bool validate();
		void PSB();
		void initPsb(int);
		void elmPsb(int, int, int, int);
		bool checkPsb();
		void change();
		void swap(int &, int &);
		void printOut(bool);
		bool backTrack();
		void initUsed();
		void setUsed(int, int, int, bool);
		bool used(int, int, int);
		int grid[9][9], psb_rem[9][9], remain; 
		int rowUsed[9][11], colUsed[9][11], cellUsed[3][3][11];
		bool psb[9][9][10];
};
