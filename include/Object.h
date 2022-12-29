#ifndef OBJECT_H_
#define OBJECT_H_

#include <vector>

#include "Material.h"
#include "Transformations.h"

namespace ray_tracer {

struct Object {
  M4x4 transform = I4x4;
  const Material material{};

  Object() = default;
  Object(Material material) : material(material) {}

  void applyTransform(const M4x4 &t) { transform = mult(t, transform); }
  virtual Vector normalAt(const Point &p) const = 0;
};

struct Sphere : Object {
  float radius = 1;
  Point center{0, 0, 0};
  Sphere() = default;
  Sphere(Material m) : Object(m) {}

  Vector normalAt(const Point &worldPoint) const override {
    Point objectPoint = mult(inverse(transform), worldPoint);
    Vector objectNormal = objectPoint - Point(0, 0, 0);
    // if transform includes a translation, then multiplying by its transpose
    // will mess up the w coordinate.
    M4x4 transformNoTranslation = transform;
    transformNoTranslation[0][3] = 0;
    transformNoTranslation[1][3] = 0;
    transformNoTranslation[2][3] = 0;
    Vector worldNormal =
        mult(transpose(inverse(transformNoTranslation)), objectNormal);
    return worldNormal.normalize();
  }
};

} // namespace ray_tracer

#endif // OBJECT_H_
