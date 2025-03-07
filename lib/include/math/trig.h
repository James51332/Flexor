#pragma once

#include <cmath>

namespace flexor
{

// ----- Conversion Functions -----

/**
 * Converts an angle from degrees to radians.
 */
inline float degrees(float radians)
{
  constexpr static float degreesToRadians = 180.0f / M_PI;
  return radians * degreesToRadians;
}

/**
 * Converts an angle from radians to degrees.
 */
inline float radians(float degrees)
{
  constexpr static float radiansToDegrees = M_PI / 180.0f;
  return degrees * radiansToDegrees;
}

} // namespace flexor