#include <math/matrix.h>
using namespace flexor;

#include <cassert>

int math_matrix(int argc, char** argv)
{
  // Small Matrix Tests
  {
    matrix2 mat2(2.0f);
    matrix3 mat3(2.0f);
    matrix4 mat4(2.0f);

    assert(mat2 == mat2);
    assert(mat2 * 3.0f == 3.0f * mat2);
    assert(mat3 * 2.0f == mat3 + mat3);
    assert(mat4 == transpose(mat4));

    matrix4 lhs(2.0f);
    matrix4 rhs(5.0f);
    lhs *= rhs;

    assert(lhs.columns() == 4 && lhs.rows() == 4);
    for (int i = 0; i < lhs.columns(); i++)
    {
      for (int j = 0; j < lhs.rows(); j++)
      {
        if (i == j)
          assert(lhs[i][j] == 10.0f);
        else
          assert(lhs[i][j] == 0.0f);
      }
    }
  }

  // Big Matrix Tests
  {
    matrix mat5(5, 5, 2.0f);
    vector vec5(5, 2.0f);
    assert(vec5 * 2.0f == mat5 * vec5);

    matrix rowVec(1, 10);
    matrix colVec(10, 1);
    for (int i = 0; i < 10; i++)
    {
      rowVec[i][0] = 1.0f;
      colVec[0][i] = 1.0f;
    }

    matrix scalar(1, 1, 10.0f);
    assert(rowVec * colVec == scalar);
  }

  return 0;
}