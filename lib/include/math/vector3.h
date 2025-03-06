#pragma once

#include <cassert>

#include "base.h"
#include "vector.h"

namespace flexor
{

// ----- Vector3 Class -----

/**
 * A 3-component floating point vector
 *
 * Since many of the vectors in this engine will have a small size, either being 2, 3, or 4, it is
 * likely not worth it to store these in a dynamically sized heap array. Since we will need to be
 * able to have larger vectors as well, we will implement both methods. Also note that we are only
 * implementing this for academic purposes, as we performance benefits of SIMD with this method.
 */
struct vector3 : public base::vector
{
  // Fields

  float x, y, z;

  // Constructors

  vector3(float v = 0.0f)
    : vector3(v, v, v)
  {
  }

  vector3(int len, float v = 0.0f)
    : vector3(v, v, v)
  {
    assert(len == length());
  }

  vector3(float x, float y, float z)
    : x(x), y(y), z(z)
  {
  }

  // Methods

  constexpr static int length() { return 3; }

  // Operators

  vector3& operator+=(const vector3& other)
  {
    x += other.x;
    y += other.y;
    z += other.z;
    return (*this);
  }

  vector3& operator-=(const vector3& other)
  {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return (*this);
  };

  vector3& operator*=(float scalar)
  {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return (*this);
  }

  vector3& operator/=(float scalar)
  {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return (*this);
  }

  float& operator[](int index)
  {
    assert(index >= 0 && index < length());
    switch (index)
    {
      default:
      case 0: return x;
      case 1: return y;
      case 2: return z;
    }
  }

  const float operator[](int index) const
  {
    assert(index >= 0 && index < length());
    switch (index)
    {
      default:
      case 0: return x;
      case 1: return y;
      case 2: return z;
    }
  }
};

// ----- Cross Product -----

inline vector3 cross(const vector3& lhs, const vector3& rhs)
{
  // https://en.wikipedia.org/wiki/Cross_product
  vector3 res;
  res[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
  res[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
  res[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
  return res;
}

} // namespace flexor