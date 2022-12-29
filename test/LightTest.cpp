#include <gtest/gtest.h>

#include "Light.h"

using namespace ray_tracer;

// Lighting with the eye between the light and the surface.
TEST(LightTest, Lighting0) {
  Material m;
  Point position(0, 0, 0);
  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 0, -10), Color(1, 1, 1));
  EXPECT_EQ(lighting(m, light, position, eyev, normalv), Color(1.9, 1.9, 1.9));
}

// Lighting with the eye between light and surface, eye offset 45 degrees.
TEST(LightTest, Lighting1) {
  Material m;
  Point position(0, 0, 0);
  Vector eyev(0, sqrtf(2) / 2, -sqrtf(2) / 2);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 0, -10), Color(1, 1, 1));
  EXPECT_EQ(lighting(m, light, position, eyev, normalv), Color(1.0, 1.0, 1.0));
}

// Lighting with eye opposite surface, light offset 45 degrees.
TEST(LightTest, Lighting2) {
  Material m;
  Point position(0, 0, 0);
  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 10, -10), Color(1, 1, 1));
  EXPECT_EQ(lighting(m, light, position, eyev, normalv),
            Color(0.7364, 0.7364, 0.7364));
}

// Lighting with eye in the path of the reflection vector.
TEST(LightTest, Lighting3) {
  Material m;
  Point position(0, 0, 0);
  Vector eyev(0, -sqrtf(2) / 2, -sqrtf(2) / 2);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 10, -10), Color(1, 1, 1));
  EXPECT_EQ(lighting(m, light, position, eyev, normalv),
            Color(1.63639, 1.63639, 1.63639));
}

// Lighting with the light behind the surface.
TEST(LightTest, Lighting4) {
  Material m;
  Point position(0, 0, 0);
  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 0, 10), Color(1, 1, 1));
  EXPECT_EQ(lighting(m, light, position, eyev, normalv), Color(0.1, 0.1, 0.1));
}
