#include "Solver.h"
#include "Tree.h"

class StackSolver : public Solver
{
private:
	int size;
	int** maze;
	Tree stack_tree;
public:
	StackSolver(void);
	~StackSolver(void);
	void readInput(char* inputfile);
	void solve(char* outputfile);
};

