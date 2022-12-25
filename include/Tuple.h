#ifndef TUPLE_H_
#define TUPLE_H_

#include <cassert>
#include <cmath>
#include <ostream>

#include "Util.h"

namespace ray_tracer {

struct Tuple {
  float x, y, z, w;
  Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

struct Point : Tuple {
  Point(float x, float y, float z, float w = 1.0f) : Tuple(x, y, z, w) {
    assert(eqf(w, 1.0f));
  }
};

struct Vector : Tuple {
  Vector(float x, float y, float z, float w = 0.0f) : Tuple(x, y, z, w) {
    assert(eqf(w, 0.0f));
  }

  float magnitude() { return sqrtf(x * x + y * y + z * z + w * w); }

  Vector normalize() {
    float m = magnitude();
    return Vector(x / m, y / m, z / m);
  }

  float dot(const Vector &t) { return x * t.x + y * t.y + z * t.z + w * t.w; }

  Vector cross(const Vector &v) {
    return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  }
};

inline std::ostream &operator<<(std::ostream &os, const Tuple &t) {
  return os << "T(" << t.x << ", " << t.y << ", " << t.z << ", " << t.w << ")";
}

inline std::ostream &operator<<(std::ostream &os, const Point &p) {
  return os << "P(" << p.x << ", " << p.y << ", " << p.z << ")";
}

inline std::ostream &operator<<(std::ostream &os, const Vector &v) {
  return os << "V(" << v.x << ", " << v.y << ", " << v.z << ")";
}

inline bool operator==(const Tuple &t0, const Tuple &t1) {
  return eqf(t0.x, t1.x) && eqf(t0.y, t1.y) && eqf(t0.z, t1.z) &&
         eqf(t0.w, t1.w);
}

inline Tuple operator+(const Tuple &t0, const Tuple &t1) {
  return {t0.x + t1.x, t0.y + t1.y, t0.z + t1.z, t0.w + t1.w};
}

inline Tuple operator-(const Tuple &t0, const Tuple &t1) {
  return {t0.x - t1.x, t0.y - t1.y, t0.z - t1.z, t0.w - t1.w};
}

inline Tuple operator-(const Tuple &t) { return Tuple(-t.x, -t.y, -t.z, -t.w); }

inline Tuple operator*(const Tuple &t, float s) {
  return Tuple(s * t.x, s * t.y, s * t.z, s * t.w);
}

inline Tuple operator/(const Tuple &t, float d) {
  return Tuple(t.x / d, t.y / d, t.z / d, t.w / d);
}

} // namespace ray_tracer

#endif // TUPLE_H_
