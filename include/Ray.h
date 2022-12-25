#ifndef RAY_H_
#define RAY_H_

#include <vector>

#include "Tuple.h"

namespace ray_tracer {

struct Sphere {
  float radius;
  Point center;
  Sphere() : radius(1), center(Point(0, 0, 0)) {}
};

struct Ray {
  Point origin;
  Vector direction;

  Ray(Point origin, Vector direction) : origin(origin), direction(direction) {}

  Point position(float t) { return origin + (direction * t); }

  std::vector<float> intersect(const Sphere &sphere) {
    Vector sphereToRay = origin - sphere.center;
    float a = direction.dot(direction);
    float b = 2 * direction.dot(sphereToRay);
    float c = sphereToRay.dot(sphereToRay) - 1;
    float discriminant = b * b - 4 * a * c;
    float t1 = (-b - sqrtf(discriminant)) / (2 * a);
    float t2 = (-b + sqrtf(discriminant)) / (2 * a);
    return {t1, t2};
  }
};

} // namespace ray_tracer

#endif // RAY_H_
