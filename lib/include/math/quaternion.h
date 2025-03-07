#pragma once

#include <cmath>

#include "small_matrix.h"
#include "vector.h"
#include "vector3.h"

namespace flexor
{

// ----- Forward Declarations -----

class quaternion;
inline float magnitude(const quaternion& quat);
inline quaternion conjugate(const quaternion& quat);
inline quaternion inverse(const quaternion& quat);
inline quaternion normalize(const quaternion& quat);

// ----- Quaternion Class -----

/**
 * Represents a quaternion, a four dimensional extension of the complex numbers which can represent
 * rotations in three dimensions. Quaternions can be thought of as having a real component and a
 * vector component w.r.t. complex basis { i, j, k }. We define the multiplication identities as
 * follows:
 *
 * i^2 = j^2 = k^2 = ijk = -1
 *
 * We are going to implement a slightly altered version of quaternions into this engine. Because our
 * quaternions strictly represent rotation, the only operation we have to act directly on them
 * besides manually changing their values is to multiply them. However, the multiplication operator
 * will be defined as rotating using a quaternion. Therefore, we also define the static method
 * multiply() to perform traditional quaternion multiplication. The remainder of the quaternion
 * functions are defined as inline methods.
 *
 * This inspiration has been taken from the unity API for quaternions found here:
 * https://docs.unity3d.com/6000.0/Documentation/ScriptReference/Quaternion.html
 */
class quaternion
{
public:
  // Constructors

  /**
   * Creates a quaternion with given real and imaginary values.
   */
  quaternion(float real = 1.0f, float i = 0.0f, float j = 0.0f, float k = 0.0f)
    : real(real), imag(i, j, k)
  {
  }

  /**
   * Creates a quaternion using an axis and a given angle in radians.
   */
  quaternion(const vector3& axis, float angle)
  {
    assert(axis != vector3(0.0f));

    float halfAngle = 0.5f * angle;
    real = cos(halfAngle);
    imag = sin(halfAngle) * normalize(axis);
  }

  // Methods

  /**
   * It may be useful to think of a quaternion as a four component vector.
   */
  constexpr static int length() { return 4; }

  /**
   * Multiplies using the formal definition of quaternion multiplication.
   */
  static quaternion multiply(const quaternion& lhs, const quaternion& rhs)
  {
    quaternion res;

    // We can compute quaternion multiplication using dot and cross product.
    // https://fgiesen.wordpress.com/2019/02/09/rotating-a-single-vector-using-a-quaternion/
    res.real = lhs.real * rhs.real - dot(lhs.imag, rhs.imag);
    res.imag = lhs.real * rhs.imag + lhs.imag * rhs.real + cross(lhs.imag, rhs.imag);

    return res;
  }

  /**
   * Converts a quaternion to a three dimensional rotation matrix. This will be important for
   * visualizing quaternions since GPUs primarily use matrices. We could just apply the quaternion
   * to the basis vectors, however this is less efficient than using presimplified closed form. The
   * one used here is from this wikipedia page on quaternions and spatial rotations.
   *
   * https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Quaternion-derived_rotation_matrix
   */
  static matrix3 matrix(const quaternion& quat)
  {
    // The closed form doesn't require them to be normalized, but we will normalize first to make
    // things much nicer.
    quaternion q = normalize(quat);

    // clang-format off
    matrix3 res;
    res[0] = {1.0f - 2.0f * (q[2] * q[2] + q[3] * q[3]), 2.0f * (q[1] * q[2] + q[3] * q[0]), 2.0f * (q[1] * q[3] - q[2] * q[0])};
    res[1] = {2.0f * (q[1] * q[2] - q[3] * q[0]), 1.0f - 2.0f * (q[1] * q[1] + q[3] * q[3]), 2.0f * (q[2] * q[3] + q[1] * q[0])};
    res[2] = {2.0f * (q[1] * q[3] + q[2] * q[0]), 2.0f * (q[2] * q[3] - q[1] * q[0]), 1.0f - 2.0f * (q[1] * q[1] + q[2] * q[2])};
    return res;
    // clang-format on
  }

  float scalar() const { return real; }
  vector3 vector() const { return imag; }

  float& scalar() { return real; }
  vector3& vector() { return imag; }

  // Operators

  /**
   * Rotates, one quaternion around another. Note that this is different from multiplying to
   * quaternions.
   */
  quaternion& operator*=(const quaternion& other)
  {
    quaternion& lhs = *this;
    lhs = multiply(lhs, multiply(other, inverse(lhs)));
    return lhs;
  }

  float& operator[](int index)
  {
    assert(index >= 0 && index < length());
    if (index == 0)
      return real;
    else
      return imag[index - 1];
  }

  const float operator[](int index) const
  {
    assert(index >= 0 && index < length());
    if (index == 0)
      return real;
    else
      return imag[index - 1];
  }

private:
  // Fields

  float real;
  vector3 imag;
};

// ----- Inline Operators -----

inline bool operator==(const quaternion& lhs, const quaternion& rhs)
{
  for (int i = 0; i < lhs.length(); i++)
    if (lhs[i] != rhs[i])
      return false;

  return true;
}

inline quaternion operator*(const quaternion& lhs, const quaternion& rhs)
{
  return quaternion(lhs) *= rhs;
}

inline vector3 operator*(const quaternion& lhs, const vector3& rhs)
{
  quaternion res = lhs * quaternion(0.0f, rhs[0], rhs[1], rhs[2]);
  return res.vector();
}

// ----- Quaternion Operations -----

inline float magnitude(const quaternion& quat)
{
  return sqrt(quat.scalar() * quat.scalar() + dot(quat.vector(), quat.vector()));
}

inline quaternion normalize(const quaternion& quat)
{
  float mag = magnitude(quat);
  assert(mag != 0.0f);

  float scale = 1.0f / mag;
  return quaternion(quat[0] * scale, quat[1] * scale, quat[2] * scale, quat[3] * scale);
}

inline quaternion conjugate(const quaternion& quat)
{
  return quaternion(quat[0], -quat[1], -quat[2], -quat[3]);
}

inline quaternion inverse(const quaternion& quat)
{
  float mag = magnitude(quat);
  assert(mag != 0.0f);

  quaternion res = conjugate(quat);
  float scale = 1.0f / (mag * mag);
  res.scalar() *= scale;
  res.vector() *= scale;

  return res;
}

} // namespace flexor