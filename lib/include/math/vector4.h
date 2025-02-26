#pragma once

#include <cassert>

#include "base.h"
#include "vector.h"

namespace flexor
{

// ----- Vector4 Class -----

/**
 * A 4-component floating point vector
 *
 * Since many of the vectors in this engine will have a small size, either being 2, 3, or 4, it is
 * likely not worth it to store these in a dynamically sized heap array. Since we will need to be
 * able to have larger vectors as well, we will implement both methods. Also note that we are only
 * implementing this for academic purposes, as we performance benefits of SIMD with this method.
 */
struct vector4 : public base::vector
{
  // Fields

  float x, y, z, w;

  // Constructors

  vector4(float v = 0.0f)
    : vector4(v, v, v, v)
  {
  }

  vector4(int len, float v = 0.0f)
    : vector4(v, v, v, v)
  {
    assert(len == length());
  }

  vector4(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w)
  {
  }

  // Methods

  constexpr static int length() { return 4; }

  // Operators

  vector4& operator+=(const vector4& other)
  {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return (*this);
  }

  vector4& operator-=(const vector4& other)
  {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return (*this);
  };

  vector4& operator*=(float scalar)
  {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return (*this);
  }

  vector4& operator/=(float scalar)
  {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
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
      case 3: return w;
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
      case 3: return w;
    }
  }
};

} // namespace flexor