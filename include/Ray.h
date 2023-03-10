#ifndef RAY_H_
#define RAY_H_

#include <vector>

#include "Object.h"
#include "Transformations.h"

namespace ray_tracer {

struct Intersection {
  float t;
  const Object *object;
  Intersection(float t, const Object *object) : t(t), object(object) {}
};

using Intersections = std::vector<Intersection>;

struct Ray {
  Point origin;
  Vector direction;

  Ray(Point origin, Vector direction) : origin(origin), direction(direction) {}

  Point position(float t) { return origin + (direction * t); }

  Intersections intersect(const Sphere &sphere) {
    Ray rayT = transform(inverse(sphere.transform));
    Vector sphereToRay = rayT.origin - sphere.center;
    float a = rayT.direction.dot(rayT.direction);
    float b = 2 * rayT.direction.dot(sphereToRay);
    float c = sphereToRay.dot(sphereToRay) - 1;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
      return {};
    float t1 = (-b - sqrtf(discriminant)) / (2 * a);
    float t2 = (-b + sqrtf(discriminant)) / (2 * a);
    return {{t1, &sphere}, {t2, &sphere}};
  }

  const Intersection *hit(const Intersections &xs) {
    const Intersection *minX = nullptr;
    for (const Intersection &x : xs) {
      if (x.t >= 0 && (minX == nullptr || x.t < minX->t)) {
        minX = &x;
      }
    }
    return minX;
  }

  Ray transform(const M4x4 &t) { return {mult(t, origin), mult(t, direction)}; }
};

} // namespace ray_tracer

#endif // RAY_H_
