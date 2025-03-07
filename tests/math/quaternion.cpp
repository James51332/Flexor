#include <math/quaternion.h>
#include <math/trig.h>
using namespace flexor;

#include <cassert>

int math_quaternion(int argc, char** argv)
{
  vector3 x(1.0f, 0.0f, 0.0f);
  vector3 y(0.0f, 1.0f, 0.0f);
  vector3 z(0.0f, 0.0f, 1.0f);

  // This quaternion multiplies around the x-axis by 90 degrees.
  quaternion q(x, radians(90.0f));

  // Rotating the y-axis 90-degrees about the x-axis gives us the z-axis.
  vector3 rotatedY = q * y;
  assert(magnitude(rotatedY - z) < 1e-5f);

  // The quaternion multiples around the y-axis by 180.0f degrees.
  quaternion p(y, radians(180.0f));

  // Rotating about the x-axis should give us the opposite vector
  vector3 rotatedX = p * x;
  assert(magnitude(rotatedX + x) < 1e-5f);

  // Make sure that when we apply the quaternion as a matrix, we get the same result.
  vector3 quatRotated = q * z;
  matrix3 qMatrix = quaternion::matrix(q);
  vector3 matrixRotated = qMatrix * z;
  assert(magnitude(quatRotated - matrixRotated) < 1e-5f);

  return 0;
}