#ifndef UTIL_H_
#define UTIL_H_

#include <cmath>

namespace ray_tracer {

#define PI 3.14159265f

inline bool eqf(float a, float b, float epsilon = 0.00001f) {
  return fabs(a - b) < epsilon;
}

} // namespace ray_tracer

#endif // UTIL_H_
