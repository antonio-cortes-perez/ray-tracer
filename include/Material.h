#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Color.h"

namespace ray_tracer {

struct Material {
  Color color{1, 1, 1};
  float ambient = 0.1;
  float diffuse = 0.9;
  float specular = 0.9;
  float shininess = 200;

  Material() = default;

  Material(Color color, float ambient, float diffuse, float specular,
           float shininess)
      : color(color), ambient(ambient), diffuse(diffuse), specular(specular),
        shininess(shininess) {}
};

} // namespace ray_tracer

#endif // MATERIAL_H_
