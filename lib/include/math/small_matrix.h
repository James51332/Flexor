#pragma once

#include <cassert>

#include "base.h"
#include "matrix.h"
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

// ----- Small Matrix Class -----

/**
 * A small n by n matrix allocated on the stack where n is the length of the vector type given.
 */
template <typename T, int N = T::length()> class small_matrix : public base::matrix
{
public:
  // Constructors

  small_matrix() = delete;

  small_matrix(T vec)
    : cols(N, vec)
  {
  }

  small_matrix(float v = 0.0f)
    : small_matrix(T(v))
  {
  }

  // Methods

  constexpr static int columns() { return N; }
  constexpr static int rows() { return N; }

  // Operators

  small_matrix<T>& operator+=(const small_matrix<T>& other)
  {
    (*this) = (*this) + other;
    return (*this);
  }

  small_matrix<T>& operator-=(const small_matrix<T>& other)
  {
    (*this) = (*this) - other;
    return (*this);
  }

  small_matrix<T>& operator*=(const small_matrix<T>& other)
  {
    (*this) = (*this) * other;
    return (*this);
  }

  small_matrix& operator*=(float scalar)
  {
    (*this) = (*this) * scalar;
    return (*this);
  }

  small_matrix& operator/=(float scalar)
  {
    (*this) = (*this) / scalar;
    return (*this);
  }

  T& operator[](int index)
  {
    assert(index >= 0 && index < length());
    return cols[index];
  }

  const T operator[](int index) const
  {
    assert(index >= 0 && index < length());
    return cols[index];
  }

private:
  // Fields

  T cols[N];
};

// ----- Convenient Typenames -----

using matrix2 = small_matrix<vector2>;
using matrix3 = small_matrix<vector3>;
using matrix4 = small_matrix<vector4>;

} // namespace flexor