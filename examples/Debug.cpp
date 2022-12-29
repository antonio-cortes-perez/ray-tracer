#include <iostream>

#include "Light.h"

using namespace ray_tracer;

int main() {
  Point point(0, 0, 0);
  Vector eyev(0, sqrtf(2) / 2, -sqrtf(2) / 2);
  Vector normalv(0, 0, -1);
  Point lightPosition(0, 0, -10);

  Vector lightv = Vector(lightPosition - point).normalize();
  std::cout << "lightv = " << lightv << "\n";
  float lightDotNormal = lightv.dot(normalv);
  std::cout << "lightDotNormal = " << lightDotNormal << "\n";

  Vector reflectv = Vector(-lightv).reflect(normalv);
  std::cout << "reflectv = " << reflectv << "\n";
  float reflectDotEye = reflectv.dot(eyev);
  std::cout << "reflectDotEye = " << reflectDotEye << "\n";

  return 0;
}
