#include <math/vector.h>
using namespace flexor;

#include <cassert>

int math_vector(int argc, char** argv)
{
  // Small Vector Tests
  {
    vector2 vec2(2.0f);
    vector3 vec3(2.0f);
    vector4 vec4(2.0f);

    assert(vec2 == vec2);
    assert(vec4 * 3.0f == 3.0f * vec4);
    assert(vec3 * 2.0f == vec3 + vec3);

    vector4 lhs(1.0f);
    vector4 rhs(5.0f);
    assert(dot(lhs, rhs) == 20.0f);

    vector3 i(1.0f, 0.0f, 0.0f);
    vector3 j(0.0f, 1.0f, 0.0f);
    vector3 k(0.0f, 0.0f, 1.0f);
    assert(cross(i, j) == k);
    assert(cross(k, j) == -i);
  }

  // Big Vector Tests
  {
    vector lhs(100, 2.0f);
    vector rhs(100, 2.0f);
    assert(lhs == rhs);
    assert(dot(lhs, rhs) == 400.0f);
    assert(lhs - rhs == vector(100));
  }

  return 0;
}