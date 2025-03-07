#pragma once

#include <cassert>
#include <vector>

#include "base.h"
#include "small_matrix.h"
#include "vector.h"

namespace flexor
{

// ----- Operator Declarations -----

// clang-format off

template <typename T> inline typename std::enable_if<std::is_base_of<base::matrix, T>::value, T>::type operator+(const T& lhs, const T& rhs);
template <typename T> inline typename std::enable_if<std::is_base_of<base::matrix, T>::value, T>::type operator-(const T& lhs, const T& rhs);
template <typename T> inline typename std::enable_if<std::is_base_of<base::matrix, T>::value, T>::type operator*(const T& lhs, const T& rhs);
template <typename T> inline typename std::enable_if<std::is_base_of<base::matrix, T>::value, T>::type operator*(const T& mat, float scalar);
template <typename T> inline typename std::enable_if<std::is_base_of<base::matrix, T>::value, T>::type operator*(float scalar, const T& mat);
template <typename T> inline typename std::enable_if<std::is_base_of<base::matrix, T>::value, T>::type operator/(const T& mat, float scalar);

// clang-format on

// ----- Matrix Class -----
/**
 * A generalized n by m matrix allocated on the heap.
 */
class matrix : public base::matrix
{
public:
  // Constructors

  matrix() = delete;

  matrix(int rows, int columns, float v = 1.0f)
    : numRows(rows), numCols(columns), cols(columns, vector(rows, 0.0f))
  {
    assert(rows > 0 && columns > 0);

    int length = rows < columns ? rows : columns;
    for (int i = 0; i < length; i++)
      cols[i][i] = v;
  }

  /**
   * Constructs a matrix from a list of column vectors. Each column vector must have the same number
   * of components.
   */
  matrix(std::initializer_list<vector> columns)
    : numRows(columns.begin()->length()), numCols(columns.size()), cols(columns)
  {
    // Make sure that we have the same number of compenents for each.
    for (auto& col : cols)
      assert(col.length() == numRows);
  }

  // Builds a matrix from a smaller matrix with given # rows and # cols or the same or the same
  // number of rows or cols as the given matrix for each of these parameters that are negative.
  template <typename U, std::enable_if_t<std::is_base_of_v<base::matrix, U>, bool> = true>
  matrix(const U& mat, int rows = -1, int columns = -1)
    : matrix(rows >= 0 ? rows : mat.rows(), columns >= 0 ? columns : mat.columns())
  {
    assert(mat.rows() <= numRows && mat.columns() <= numCols);

    int length = mat.rows() < mat.columns() ? mat.rows() : mat.columns();
    for (int i = 0; i < length; i++)
      cols[i] = vector(mat[i], numRows);
  }

  // Methods

  int columns() const { return numCols; }
  int rows() const { return numRows; }

  // Operators

  matrix& operator+=(const matrix& other)
  {
    (*this) = (*this) + other;
    return (*this);
  }

  matrix& operator-=(const matrix& other)
  {
    (*this) = (*this) - other;
    return (*this);
  }

  matrix& operator*=(const matrix& other)
  {
    (*this) = (*this) * other;
    return (*this);
  }

  matrix& operator*=(float scalar)
  {
    (*this) = (*this) * scalar;
    return (*this);
  }

  matrix& operator/=(float scalar)
  {
    (*this) = (*this) / scalar;
    return (*this);
  }

  vector& operator[](int index)
  {
    assert(index >= 0 && index < columns());
    return cols[index];
  }

  const vector operator[](int index) const
  {
    assert(index >= 0 && index < columns());
    return cols[index];
  }

private:
  // Fields
  std::vector<vector> cols;
  int numRows, numCols;
};

// ----- Matrix Functions -----

template <typename matType>
inline typename std::enable_if<std::is_base_of<base::matrix, matType>::value, matType>::type
transpose(const matType& matrix)
{
  matType res(matrix.columns(), matrix.rows());

  for (int i = 0; i < matrix.columns(); i++)
    for (int j = 0; j < matrix.rows(); j++)
      res[j][i] = matrix[i][j];

  return res;
}

// ----- Inline Operators -----

template <typename matType>
inline typename std::enable_if<std::is_base_of<base::matrix, matType>::value, matType>::type
operator+(const matType& lhs, const matType& rhs)
{
  assert(lhs.rows() == rhs.rows() && lhs.columns() == rhs.columns());

  matType res(lhs.rows(), lhs.columns());
  for (int i = 0; i < res.columns(); i++)
    res[i] = lhs[i] + rhs[i];

  return res;
}

template <typename matType>
inline typename std::enable_if<std::is_base_of<base::matrix, matType>::value, matType>::type
operator-(const matType& lhs, const matType& rhs)
{
  assert(lhs.rows() == rhs.rows() && lhs.columns() == rhs.columns());

  matType res(lhs.rows(), lhs.columns());
  for (int i = 0; i < res.columns(); i++)
    res[i] = lhs[i] + rhs[i];

  return res;
}

template <typename matType>
inline typename std::enable_if<std::is_base_of<base::matrix, matType>::value, matType>::type
operator-(const matType& mat)
{
  return matType(mat) *= -1.0f;
}

template <typename matType>
inline typename std::enable_if<std::is_base_of<base::matrix, matType>::value, matType>::type
operator*(const matType& lhs, const matType& rhs)
{
  assert(lhs.columns() == rhs.rows());

  matType res(lhs.rows(), rhs.columns());
  matType trans = transpose(lhs);

  for (int i = 0; i < rhs.columns(); i++)
    for (int j = 0; j < trans.columns(); j++)
      res[i][j] = dot(trans[j], rhs[i]);

  return res;
}

template <typename matType>
inline typename std::enable_if<std::is_base_of<base::matrix, matType>::value, matType>::type
operator*(const matType& mat, float scalar)
{
  matType res(mat.rows(), mat.columns());
  for (int i = 0; i < mat.columns(); i++)
    res[i] = mat[i] * scalar;

  return res;
}

template <typename matType>
inline typename std::enable_if<std::is_base_of<base::matrix, matType>::value, matType>::type
operator*(float scalar, const matType& mat)
{
  return mat * scalar;
}

template <typename matType>
inline typename std::enable_if<std::is_base_of<base::matrix, matType>::value, matType>::type
operator/(const matType& mat, float scalar)
{
  assert(scalar != 0.0f);

  matType res(mat.rows(), mat.columns());
  for (int i = 0; i < mat.columns(); i++)
    res[i] = mat[i] / scalar;

  return res;
}

template <typename T, typename U, std::enable_if_t<std::is_base_of_v<base::matrix, T>, bool> = true,
          std::enable_if_t<std::is_base_of_v<base::matrix, U>, bool> = true>
inline bool operator==(const T& lhs, const U& rhs)
{
  if ((lhs.rows() != rhs.rows()) || (lhs.columns() != rhs.columns()))
    return false;

  for (int i = 0; i < lhs.columns(); i++)
    if (lhs[i] != rhs[i])
      return false;

  return true;
}

// ----- Matrix Vector Multiplication -----

template <typename T, typename V, std::enable_if_t<std::is_base_of_v<base::matrix, T>, bool> = true,
          std::enable_if_t<std::is_base_of_v<base::vector, V>, bool> = true>
inline V operator*(const T& mat, const V& vec)
{
  assert(mat.rows() == vec.length());

  T trans = transpose(mat);
  V res(mat.columns());
  for (int i = 0; i < res.length(); i++)
    res[i] = dot(trans[i], vec);

  return res;
}

} // namespace flexor