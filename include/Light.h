#ifndef LIGHT_H_
#define LIGHT_H_

#include "Color.h"
#include "Material.h"
#include "Tuple.h"

namespace ray_tracer {

struct Light {
  const Point position{0, 0, 0};
  const Color intensity{1, 1, 1};

  Light() = default;

  Light(Point position, Color intensity)
      : position(position), intensity(intensity) {}
};

inline Color lighting(const Material &material, const Light &light,
                      const Point &point, const Vector &eyev,
                      const Vector &normalv) {
  // Combine the surface color with the light's color/intensity.
  Color effectiveColor = material.color * light.intensity;

  // Compute the ambient contribution.
  Color ambient = effectiveColor * material.ambient;

  // Find the direction to the light source.
  Vector lightv = Vector(light.position - point).normalize();

  // lightDotNormal represents the cosine of the angle between the​
  // light vector and the normal vector. A negative number means the​
  // light is on the other side of the surface.
  float lightDotNormal = lightv.dot(normalv);
  if (lightDotNormal < 0)
    return ambient;

  // Compute the diffuse contribution.
  Color diffuse = effectiveColor * material.diffuse * lightDotNormal;

  // reflectDotEye represents the cosine of the angle between the
  // reflection vector and the eye vector. A negative number means the
  // light reflects away from the eye.
  Vector reflectv = Vector(-lightv).reflect(normalv);
  float reflectDotEye = reflectv.dot(eyev);
  if (reflectDotEye <= 0)
    return ambient + diffuse;

  // Compute the specular contribution.
  float factor = powf(reflectDotEye, material.shininess);
  Color specular = light.intensity * material.specular * factor;
  return ambient + diffuse + specular;
}

} // namespace ray_tracer

#endif // LIGHT_H_
