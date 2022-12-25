#include <gtest/gtest.h>

#include "Ray.h"

using namespace ray_tracer;

TEST(RayTest, Creation) {
  Point p(1, 2, 3);
  Vector v(4, 5, 6);
  Ray r(p, v);
  EXPECT_EQ(r.origin, p);
  EXPECT_EQ(r.direction, v);
}

TEST(RayTest, Position) {
  Ray r(Point(2, 3, 4), Vector(1, 0, 0));
  EXPECT_EQ(r.position(0), Point(2, 3, 4));
  EXPECT_EQ(r.position(1), Point(3, 3, 4));
  EXPECT_EQ(r.position(-1), Point(1, 3, 4));
  EXPECT_EQ(r.position(2.5), Point(4.5, 3, 4));
}

TEST(RayTest, IntersectSphere) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  std::vector<float> xs = r.intersect(s);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_FLOAT_EQ(xs[0], 4);
  EXPECT_FLOAT_EQ(xs[1], 6);
}
