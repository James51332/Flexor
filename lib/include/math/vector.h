#pragma once

#include <cassert>
#include <vector>

#include "base.h"

// These each form a circular include, but this is okay as long as small vectors aren't included
// without operators defined in this header. We also want them accessible from just including this
// file.
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

namespace flexor
{

// ----- Vector Class -----

/**
 * A heap allocated vector that can have any size greater than zero. If size is 2, 3, or 4, it is
 * strongly suggested to use the vectorN types, since they are stack allocated and will perform
 * better in general. This class is most useful when the size of the vector is not known until
 * runtime. We ironically implement this class by wrapping over std::vector.
 */
class vector : public base::vector
{
public:
  // Constructors

  vector() = delete;

  vector(int len, float fill = 0.0f)
    : data(len, fill)
  {
  }

  // Constructs a vector from a smaller vector, with the new set size, or the same size if len is
  // negative.
  template <typename U, std::enable_if_t<std::is_base_of_v<base::vector, U>, bool> = true>
  vector(const U& vec, int len = -1)
    : vector(len >= 0 ? len : vec.length())
  {
    assert(vec.length() <= length());

    for (int i = 0; i < vec.length(); i++)
      data[i] = vec[i];
  }

  // Methods

  int length() const { return data.size(); }

  // Operators

  vector& operator+=(const vector& other)
  {
    assert(length() == other.length());

    for (int i = 0; i < length(); i++)
      data[i] += other[i];

    return (*this);
  }

  vector& operator-=(const vector& other)
  {
    assert(length() == other.length());

    for (int i = 0; i < length(); i++)
      data[i] -= other[i];

    return (*this);
  };

  vector& operator*=(float scalar)
  {
    for (float& elt : data)
      elt *= scalar;

    return (*this);
  }

  vector& operator/=(float scalar)
  {
    assert(scalar != 0.0f);

    for (float& elt : data)
      elt /= scalar;

    return (*this);
  }

  float& operator[](int index)
  {
    assert(index >= 0 && index < length());
    return data[index];
  }

  const float operator[](int index) const
  {
    assert(index >= 0 && index < length());
    return data[index];
  }

private:
  // Fields

  std::vector<float> data;
};

// ----- Inline Operators -----

template <typename vecType>
inline typename std::enable_if<std::is_base_of<base::vector, vecType>::value, vecType>::type
operator+(const vecType& lhs, const vecType& rhs)
{
  return vecType(lhs) += rhs;
}

template <typename vecType>
inline typename std::enable_if<std::is_base_of<base::vector, vecType>::value, vecType>::type
operator-(const vecType& lhs, const vecType& rhs)
{
  return vecType(lhs) -= rhs;
}

template <typename vecType>
inline typename std::enable_if<std::is_base_of<base::vector, vecType>::value, vecType>::type
operator-(const vecType& vec)
{
  return vecType(vec) *= -1.0f;
}

template <typename vecType>
inline typename std::enable_if<std::is_base_of<base::vector, vecType>::value, vecType>::type
operator*(const vecType& vec, float scalar)
{
  return vecType(vec) *= scalar;
}

template <typename vecType>
inline typename std::enable_if<std::is_base_of<base::vector, vecType>::value, vecType>::type
operator*(float scalar, const vecType& vec)
{
  return vec * scalar;
}

template <typename vecType>
inline typename std::enable_if<std::is_base_of<base::vector, vecType>::value, vecType>::type
operator/(const vecType& vec, float scalar)
{
  return vecType(vec) /= scalar;
}

template <typename T>
inline typename std::enable_if<std::is_base_of<base::vector, T>::value, bool>::type
operator==(const T& lhs, const T& rhs)
{
  if (lhs.length() != rhs.length())
    return false;

  for (int i = 0; i < lhs.length(); i++)
    if (lhs[i] != rhs[i])
      return false;

  return true;
}

// ----- Vector Operations -----

template <typename vecType>
inline typename std::enable_if<std::is_base_of<base::vector, vecType>::value, float>::type
dot(const vecType& lhs, const vecType& rhs)
{
  assert(lhs.length() == rhs.length());

  float res = 0.0f;
  for (int i = 0; i < lhs.length(); i++)
    res += lhs[i] * rhs[i];

  return res;
}

template <typename vecType>
inline typename std::enable_if<std::is_base_of<base::vector, vecType>::value, float>::type
magnitude(const vecType& vec)
{
  return sqrt(dot(vec, vec));
}

} // namespace flexor