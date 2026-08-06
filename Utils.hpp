#include <box2d/math_functions.h>

#ifndef UTILS_HPP
#define UTILS_HPP
inline b2Vec2 makeVec2(double x, double y)
{
  b2Vec2 vec;
  vec.x = x;
  vec.y = y;

  return vec;
}
#endif