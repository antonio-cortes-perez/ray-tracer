#include <fstream>

#include "Canvas.h"
#include "Ray.h"

using namespace ray_tracer;

int main() {
  float wallZ = 10;
  float wallSize = 7;
  int canvasPixels = 100;
  float pixelSize = wallSize / canvasPixels;
  float half = wallSize / 2;

  Canvas cv(canvasPixels, canvasPixels);
  Color color(0.6, 0.8, 0.2);
  Point rayOrigin(0, 0, -5);
  Sphere s;
  s.applyTransform(scaling(0.5, 1, 1));
  s.applyTransform(rotationZ(PI / 4));

  for (Color &c : cv) {
    c = Color(1, 1, 0.85);
  }

  for (int y = 0; y < canvasPixels; ++y) {
    // top = +half, bottom = -half
    float worldY = half - pixelSize * y;
    for (int x = 0; x < canvasPixels; ++x) {
      // left = -half, right = +half
      float worldX = -half + pixelSize * x;
      Point target(worldX, worldY, wallZ);
      Vector direction = target - rayOrigin;
      Ray r(rayOrigin, direction.normalize());
      Intersections xs = r.intersect(s);
      if (!xs.empty()) {
        cv.set(x, y, color);
      }
    }
  }

  std::ofstream out("sphere.ppm");
  out << cv.toPPM();
  out.close();
  return 0;
}
