#include <gtest/gtest.h>

#include "Object.h"

using namespace ray_tracer;

TEST(ObjectTest, SphereNormalXAxis) {
  Sphere s;
  Vector n = s.normalAt(Point(1, 0, 0));
  EXPECT_EQ(n, Vector(1, 0, 0));
  EXPECT_EQ(n, n.normalize());
}

TEST(ObjectTest, SphereNormalYAxis) {
  Sphere s;
  Vector n = s.normalAt(Point(0, 1, 0));
  EXPECT_EQ(n, Vector(0, 1, 0));
  EXPECT_EQ(n, n.normalize());
}

TEST(ObjectTest, SphereNormalZAxis) {
  Sphere s;
  Vector n = s.normalAt(Point(0, 0, 1));
  EXPECT_EQ(n, Vector(0, 0, 1));
  EXPECT_EQ(n, n.normalize());
}

TEST(ObjectTest, SphereNormalNonAxial) {
  Sphere s;
  float f = sqrtf(3) / 3;
  Vector n = s.normalAt(Point(f, f, f));
  EXPECT_EQ(n, Vector(f, f, f));
  EXPECT_EQ(n, n.normalize());
}

TEST(ObjectTest, SphereNormalTranslation) {
  Sphere s;
  s.applyTransform(translation(0, 1, 0));
  EXPECT_EQ(s.normalAt(Point(0, 1.70711, -0.70711)),
            Vector(0, 0.70711, -0.70711));
}

TEST(ObjectTest, SphereNormalTransform) {
  Sphere s;
  s.applyTransform(rotationZ(PI / 5));
  s.applyTransform(scaling(1, 0.5, 1));
  EXPECT_EQ(s.normalAt(Point(0, sqrtf(2) / 2, -sqrtf(2) / 2)),
            Vector(0, 0.97014, -0.24254));
}
