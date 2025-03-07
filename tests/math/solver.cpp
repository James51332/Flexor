#include <math/solver.h>
using namespace flexor;

#include <cassert>
#include <iostream>

int math_solver(int argc, char** argv)
{
  // Define our some linearly independent basis vector for linear transformation A.
  vector e1 = {2.0f, 1.0f, 4.0f, 0.0f};
  vector e2 = {1.0f, 6.0f, 8.0f, 5.0f};
  vector e3 = {0.0f, 7.0f, 3.0f, 0.0f};
  vector e4 = {9.0f, 0.0f, 4.0f, 2.0f};

  // Construct the matrix of A w.r.t the standard basis.
  matrix A = {e1, e2, e3, e4};

  // Construct some vector x that we will transform under A.
  vector trueX = {4.0f, 5.0f, 2.0f, 1.0f};

  // Solve the system Ax = B with knowledge of A and B.
  vector B = A * trueX;
  vector computedX = solver::gaussJordan(A, B);

  // Make sure that the computed version is close to the final version.
  assert(magnitude(computedX - trueX) < 1e-5f);

  return 0;
}