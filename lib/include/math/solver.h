#pragma once

#include <cassert>
#include <stdexcept>

#include "matrix.h"
#include "vector.h"

namespace flexor::solver
{

// ----- Row Operations -----

/**
 * Swaps i-th and j-th row of matrix A.
 */
inline matrix swapRows(matrix& A, int i, int j)
{
  assert(i < A.rows() && j < A.rows());

  for (int col = 0; col < A.columns(); col++)
  {
    float tmp = A[col][i];
    A[col][i] = A[col][j];
    A[col][j] = tmp;
  }
}

/**
 * Multiplies the i-th row of a matrix A by given scalar.
 */
inline matrix scaleRow(matrix& A, int i, float scalar)
{
  assert(i < A.rows());

  for (int col = 0; col < A.columns(); col++)
    A[col][i] *= scalar;
}

/**
 * Adds scaled i-th row to j-th row in matrix A.
 */
inline matrix performRowOperation(matrix& A, int i, int j, float scalar = 1.0f)
{
  assert(i < A.rows() && j < A.rows());

  for (int col = 0; col < A.columns(); col++)
    A[col][j] += A[col][i] * scalar;
}

// ----- Gauss-Jordan Elimination -----

/**
 * An implementation of gauss-jordan elimination to solve the linear system Ax = B, where A is a
 * known n by n matrix, B is a known n-dimensional vector, and x is an unknown x dimensional
 * vector. If A is a singular matrix, an exception is thrown.
 */
inline vector gaussJordan(const matrix& A, const vector& B)
{
  // Make sure that we are the right size.
  assert(A.rows() == A.columns() && A.columns() == B.length());
  int n = B.length();

  // Start with a copy of A and B to compute x. We might want to make a modification, but we for now
  // will not change the given values.
  matrix copyA = A;
  vector copyB = B;

  // Iterate over each row to perform the elimination. We use the i-th row to zero out all values in
  // the i-th column except for the diagonal, which is made to 1 using row operations.
  for (int row = 0; row < A.rows(); row++)
  {
    // If diagonal entry is zero, then we will swap with a later row to guarantee that is is.
    if (copyA[row][row] == 0.0f)
    {
      bool foundRow = false;
      int swapRow = row + 1;
      for (; swapRow < A.rows(); swapRow++)
      {
        // If this row is good, then we can stop looking.
        if (copyA[swapRow][row] != 0.0f)
        {
          foundRow = true;
          break;
        }
      }

      // If we didn't find a row, we have none or infinite solutions. Don't handle these.
      if (!foundRow)
        throw new std::runtime_error("Unable to solve singular linear system!");

      // Now, we need to swap this row with the current row (and do the same for the vector).
      swapRows(copyA, row, swapRow);
      float tmp = copyB[swapRow];
      copyB[swapRow] = copyB[row];
      copyB[row] = tmp;
    }

    // Now that we have a good value on the diagonal, we divide the row by the scalar, which we know
    // is non-zero because of our swap.
    float scale = 1.0f / copyA[row][row];
    scaleRow(copyA, row, scale);
    copyB[row] *= scale;

    // We'll add this to all the other row to ensure that this column is only one in current row.
    for (int other = 0; other < A.rows(); other++)
    {
      // Don't add the current row to itself.
      if (row == other)
        continue;

      // Add this row scaled by the opposite of the entry in the other row along the column we are
      // eliminating. Then we do the same for the solution vector.
      scale = -copyA[row][other];
      performRowOperation(copyA, row, other, scale);
      copyB[other] += copyB[row] * scale;
    }
  }

  // Return the copy of b which now contains our solution vector.
  return copyB;
}

} // namespace flexor::solver