#pragma once

#include <cassert>

#include "base.h"
#include "vector.h"

namespace flexor
{

// ----- Vector2 Class -----

/**
 * A 2-component floating point vector
 *
 * Since many of the vectors in this engine will have a small size, either being 2, 3, or 4, it is
 * likely not worth it to store these in a dynamically sized heap array. Since we will need to be
 * able to have larger vectors as well, we will implement both methods. Also note that we are only
 * implementing this for academic purposes, as we performance benefits of SIMD with this method.
 */
struct vector2 : public base::vector
{
  // Fields

  float x, y;

  // Constructors

  vector2(float x = 0.0f, float y = 0.0f)
    : x(x), y(y)
  {
  }

  vector2(float v)
    : vector2(v, v)
  {
  }

  // Methods

  constexpr static int length() { return 2; }

  // Operators

  vector2& operator+=(const vector2& other)
  {
    x += other.x;
    y += other.y;
    return (*this);
  }

  vector2& operator-=(const vector2& other)
  {
    x -= other.x;
    y -= other.y;
    return (*this);
  };

  vector2& operator*=(float scalar)
  {
    x *= scalar;
    y *= scalar;
    return (*this);
  }

  vector2& operator/=(float scalar)
  {
    x /= scalar;
    y /= scalar;
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
    }
  }
};

} // namespace flexor