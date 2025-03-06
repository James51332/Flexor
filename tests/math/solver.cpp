#include <math/solver.h>
using namespace flexor;

#include <cassert>

/**
 * Perform a few tests. Build a few matrices (which we know to be nonsingular) and a vectors and
 * then multiply them. Then we run the solver on the result to see how close we get to the original
 * vector. There may be some small error, so we take the difference between the computed solution
 * and the original vector, calculate its magnitude, and make sure that it is very small.
 * */
int math_solver(int argc, char** argv)
{

  return 0;
}