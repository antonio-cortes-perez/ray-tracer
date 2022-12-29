#include <fstream>

#include "Canvas.h"
#include "Light.h"
#include "Ray.h"

using namespace ray_tracer;

int main() {
  float wallZ = 10;
  float wallSize = 7;
  int canvasPixels = 100;
  float pixelSize = wallSize / canvasPixels;
  float half = wallSize / 2;

  Canvas cv(canvasPixels, canvasPixels);
  Point rayOrigin(0, 0, -5);
  Material m;
  m.ambient = 0.3;
  m.diffuse = 0.9;
  m.specular = 0.4;
  m.shininess = 10;
  m.color = Color(0.15, 0.4, 0.9);
  Sphere s(m);
  s.applyTransform(scaling(1, 0.9, 1));
  s.applyTransform(rotationZ(-PI / 8));
  Light light(Point(10, 0, -6), Color(1, 1, 1));

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
      if (xs.empty())
        continue;
      const Intersection *hit = r.hit(xs);
      Point point = r.position(hit->t);
      Vector normal = hit->o->normalAt(point);
      Vector eye = -r.direction;
      Color c = lighting(hit->o->m, light, point, eye, normal);
      cv.set(x, y, c);
    }
  }

  std::ofstream out("sphere.ppm");
  out << cv.toPPM();
  out.close();
  return 0;
}
