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

TEST(RayTest, IntersectSphereFront) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = r.intersect(s);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_FLOAT_EQ(xs[0].t, 4);
  EXPECT_EQ(xs[0].object, &s);
  EXPECT_FLOAT_EQ(xs[1].t, 6);
  EXPECT_EQ(xs[1].object, &s);
}

TEST(RayTest, IntersectSphereTangent) {
  Ray r(Point(0, 1, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = r.intersect(s);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_FLOAT_EQ(xs[0].t, 5);
  EXPECT_EQ(xs[0].object, &s);
  EXPECT_FLOAT_EQ(xs[1].t, 5);
  EXPECT_EQ(xs[1].object, &s);
}

TEST(RayTest, NoIntersectSphere) {
  Ray r(Point(0, 2, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = r.intersect(s);
  EXPECT_EQ(xs.size(), 0);
}

TEST(RayTest, IntersectSphereInside) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = r.intersect(s);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_FLOAT_EQ(xs[0].t, -1);
  EXPECT_EQ(xs[0].object, &s);
  EXPECT_FLOAT_EQ(xs[1].t, 1);
  EXPECT_EQ(xs[1].object, &s);
}

TEST(RayTest, IntersectSphereBehind) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = r.intersect(s);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_FLOAT_EQ(xs[0].t, -6);
  EXPECT_EQ(xs[0].object, &s);
  EXPECT_FLOAT_EQ(xs[1].t, -4);
  EXPECT_EQ(xs[1].object, &s);
}

TEST(RayTest, HitAllPositive) {
  Sphere s;
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Intersections xs = {{1, &s}, {2, &s}};
  EXPECT_EQ(r.hit(xs), &xs[0]);
}

TEST(RayTest, HitSomeNegative) {
  Sphere s;
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Intersections xs = {{-1, &s}, {1, &s}};
  EXPECT_EQ(r.hit(xs), &xs[1]);
}

TEST(RayTest, HitAllNegative) {
  Sphere s;
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Intersections xs = {{-2, &s}, {-1, &s}};
  EXPECT_EQ(r.hit(xs), nullptr);
}

TEST(RayTest, HitLowestNonNegative) {
  Sphere s;
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Intersections xs = {{5, &s}, {7, &s}, {-3, &s}, {2, &s}};
  EXPECT_EQ(r.hit(xs), &xs[3]);
}

TEST(RayTest, Translate) {
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  Ray r2 = r.transform(translation(3, 4, 5));
  EXPECT_EQ(r2.origin, Point(4, 6, 8));
  EXPECT_EQ(r2.direction, Vector(0, 1, 0));
}

TEST(RayTest, Scaling) {
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  Ray r2 = r.transform(scaling(2, 3, 4));
  EXPECT_EQ(r2.origin, Point(2, 6, 12));
  EXPECT_EQ(r2.direction, Vector(0, 3, 0));
}

TEST(RayTest, SphereTransformation) {
  Sphere s;
  EXPECT_TRUE(eq(s.transform, I4x4));
  s.applyTransform(translation(2, 3, 4));
  EXPECT_TRUE(eq(s.transform, translation(2, 3, 4)));
}

TEST(RayTest, IntersectingScaledSphere) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  s.applyTransform(scaling(2, 2, 2));
  Intersections xs = r.intersect(s);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_FLOAT_EQ(xs[0].t, 3);
  EXPECT_FLOAT_EQ(xs[1].t, 7);
}

TEST(RayTest, IntersectingTranslatedSphere) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  s.applyTransform(translation(5, 0, 0));
  Intersections xs = r.intersect(s);
  EXPECT_EQ(xs.size(), 0);
}
