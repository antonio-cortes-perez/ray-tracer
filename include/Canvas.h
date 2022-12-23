#ifndef CANVAS_H_
#define CANVAS_H_

#include <vector>

#include "Color.h"

namespace ray_tracer {

class Canvas {
public:
  const int width;
  const int height;

  Canvas(int width, int height)
      : width(width), height(height), v(width * height) {}

  Color &get(int x, int y) { return v[y * width + x]; }
  void set(int x, int y, const Color &c) { v[y * width + x] = c; }

  auto begin() { return v.begin(); }
  auto end() { return v.end(); }

  std::string toPPM();

private:
  std::vector<Color> v;
};

} // namespace ray_tracer

#endif // CANVAS_H_