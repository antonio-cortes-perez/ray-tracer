#ifndef COLOR_H_
#define COLOR_H_

#include <cmath>
#include <ostream>

#include "Util.h"

namespace ray_tracer {

struct Color {
  float r, g, b;
  Color(float r, float g, float b) : r(r), g(g), b(b) {}
  Color() : Color(0, 0, 0) {}
};

inline std::ostream &operator<<(std::ostream &os, const Color &c) {
  return os << "C(" << c.r << ", " << c.g << ", " << c.b << ")";
}

inline bool operator==(const Color &c0, const Color &c1) {
  return eqf(c0.r, c1.r) && eqf(c0.g, c1.g) && eqf(c0.b, c1.b);
}

inline Color operator+(const Color &c0, const Color &c1) {
  return Color(c0.r + c1.r, c0.g + c1.g, c0.b + c1.b);
}

inline Color operator-(const Color &c0, const Color &c1) {
  return Color(c0.r - c1.r, c0.g - c1.g, c0.b - c1.b);
}

inline Color operator*(const Color &c, float s) {
  return Color(c.r * s, c.g * s, c.b * s);
}

inline Color operator*(const Color &c0, const Color &c1) {
  return Color(c0.r * c1.r, c0.g * c1.g, c0.b * c1.b);
}

} // namespace ray_tracer

#endif // COLOR_H_
