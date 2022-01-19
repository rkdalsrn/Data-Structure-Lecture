#ifndef SOLVER
#define SOLVER
class Solver
{
public:
	Solver(void);
	virtual ~Solver(void);
	virtual void readInput(char* inputfile) = 0;
	virtual void solve(char* outputfile) = 0;
};

#endif
