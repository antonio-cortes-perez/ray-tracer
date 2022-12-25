#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_

#include "Matrix.h"

namespace ray_tracer {

inline M4x4 translation(float x, float y, float z) {
  M4x4 m = I4x4;
  m[0][3] = x;
  m[1][3] = y;
  m[2][3] = z;
  return m;
}

inline M4x4 scaling(float x, float y, float z) {
  M4x4 m = I4x4;
  m[0][0] = x;
  m[1][1] = y;
  m[2][2] = z;
  return m;
}

inline M4x4 rotationX(float radians) {
  M4x4 m = I4x4;
  m[1][1] = cos(radians);
  m[1][2] = -sin(radians);
  m[2][1] = sin(radians);
  m[2][2] = cos(radians);
  return m;
}

inline M4x4 rotationY(float radians) {
  M4x4 m = I4x4;
  m[0][0] = cos(radians);
  m[0][2] = sin(radians);
  m[2][0] = -sin(radians);
  m[2][2] = cos(radians);
  return m;
}

inline M4x4 rotationZ(float radians) {
  M4x4 m = I4x4;
  m[0][0] = cos(radians);
  m[0][1] = -sin(radians);
  m[1][0] = sin(radians);
  m[1][1] = cos(radians);
  return m;
}

// x_y means “x moved in proportion to y,” and represents the
// amount by which to multiply y before adding it to x.
inline M4x4 shearing(float x_y, float x_z, float y_x, float y_z, float z_x,
                     float z_y) {
  M4x4 m = I4x4;
  m[0][1] = x_y;
  m[0][2] = x_z;
  m[1][0] = y_x;
  m[1][2] = y_z;
  m[2][0] = z_x;
  m[2][1] = z_y;
  return m;
}

} // namespace ray_tracer

#endif // TRANSFORMATIONS_H_
