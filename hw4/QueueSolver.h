#include "Solver.h"
#include "Tree.h"
class QueueSolver : public Solver
{
private:
	int size;
	int** maze;
	Tree queue_tree;
public:
	QueueSolver(void);
	~QueueSolver(void);
	void readInput(char* inputfile);
	void solve(char* outputfile);
};

