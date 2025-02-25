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

  matrix(float rows, float cols, float v = 0.0f)
    : numRows(rows), numCols(cols), cols(cols, vector(rows, v))
  {
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
operator*(const matType& lhs, const matType& rhs)
{
  assert(lhs.columns() == rhs.rows());

  matType res(lhs.rows(), rhs.columns());
  matType trans = transpose(lhs);

  for (int i = 0; i < res.columns(); i++)
    for (int j = 0; j < res.rows(); j++)
      res[i][j] = dot(trans[i], rhs[i]);

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
  matType res(mat.rows(), mat.columns());
  for (int i = 0; i < mat.columns(); i++)
    res[i] = mat[i] / scalar;

  return res;
}

} // namespace flexor