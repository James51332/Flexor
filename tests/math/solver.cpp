#include <math/solver.h>
using namespace flexor;

#include <cassert>
#include <iostream>
/**
 * Perform a few tests. Build a few matrices (which we know to be nonsingular) and a vectors and
 * then multiply them. Then we run the solver on the result to see how close we get to the original
 * vector. There may be some small error, so we take the difference between the computed solution
 * and the original vector, calculate its magnitude, and make sure that it is very small.
 * */
int math_solver(int argc, char** argv)
{
  // 4x4 with a 3.0 in the diagonals and a vector filled with 9.0
  matrix A = matrix(4, 4, 3.0);
  vector b = vector(4, 9.00);
  vector x = solver::gaussJordan(A, b);
  // 1. Make sure that x has the correct size for the four by four matricies
  assert(x.length() == b.length());
  // 2. Make sure that the  size of the rows is equal to the size of x
  assert(x.length() == A.rows());
  // 3. Ensure the difference between vector b and vector x is small in magnitude
  assert(std::abs(magnitude(x) - magnitude(b)) <= 0.01);

  // 3x3 matrix with 9.992 on the diaganols non singular filled with a float
  matrix C = matrix(3, 3, 9.992);
  // 1x3vector filed with a 12.0
  vector d = vector(3, 12.0);
  // solutions give c and d
  vector sol = solver::gaussJordan(C, d);
  // 1. Make sure that sol has the correct size for the 3 by 3 matrices
  assert(sol.length() == d.length());
  // 2. Make sure the size of x is equal to the size of A.rows())
  assert(sol.length() == C.rows());
  // 3. Ensure the magnitude difference between vector d and vector sol is small(<= 0.01)
  assert(std::abs(magnitude(sol) - magnitude(d)) <= 0.01);

  // Big matrices 30x30 filled with 19.9292
  matrix E = matrix(30, 30, 19.992);
  // 1x30 vector filled with 8.76
  vector f = vector(30, 8.76);
  // Solutions
  vector sol1 = solver::gaussJordan(E, f);
  // 1.Make sure sol1 has the correct size for the 30 x 30 matrices
  assert(sol1.length() == f.length());
  // 2. Make sure the size of sol1 is equal to E.rows()
  assert(sol1.length() == E.rows());
  // 3. Ensure the magnitude difference between vector f and vector sol1 is small(<= 0.01)
  assert(std::abs(magnitude(sol1) - magnitude(f)) <= 0.01);
  return 0;
}