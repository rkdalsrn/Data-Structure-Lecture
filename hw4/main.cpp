#include<iostream>
#include<fstream>
#include "Solver.h"
#include "StackSolver.h"
#include "QueueSolver.h"

using namespace std;

int main( int argc, char* argv[] ){
    if ( argc < 4 ){
        return 1;
    }
    
    Solver* ss = new StackSolver();
    ss->readInput(argv[1]);
    ss->solve(argv[2]);
    Solver* qs = new QueueSolver();
    qs->readInput(argv[1]);
    qs->solve(argv[3]);
    
    /*Solver* ss = new StackSolver();
    ss->readInput("maze.txt");
    ss->solve("stack.txt");
    Solver* qs = new QueueSolver();
    qs->readInput("maze.txt");
    qs->solve("queue.txt");*/
    
    delete ss;
    delete qs;
    return 0;
}
