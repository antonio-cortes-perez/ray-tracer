#include <gtest/gtest.h>

#include "Tuple.h"

using namespace ray_tracer;

TEST(TupleTest, Point) {
  Point p(9.2, 45.7, -26.1);
  EXPECT_FLOAT_EQ(p.x, 9.2);
  EXPECT_FLOAT_EQ(p.y, 45.7);
  EXPECT_FLOAT_EQ(p.z, -26.1);
  EXPECT_FLOAT_EQ(p.w, 1.0);
}

TEST(TupleTest, Vector) {
  Vector v(-51.2, 9.4, 74.6);
  EXPECT_FLOAT_EQ(v.x, -51.2);
  EXPECT_FLOAT_EQ(v.y, 9.4);
  EXPECT_FLOAT_EQ(v.z, 74.6);
  EXPECT_FLOAT_EQ(v.w, 0.0);
}

TEST(TupleTest, Addition) {
  Tuple t0(3, -2, 5, 1);
  Tuple t1(-2, 3, 1, 0);
  EXPECT_EQ(t0 + t1, Tuple(1, 1, 6, 1));
}

TEST(TupleTest, PointMinusPoint) {
  Point p0(3, 2, 1);
  Point p1(5, 6, 7);
  EXPECT_EQ(p0 - p1, Vector(-2, -4, -6));
}

TEST(TupleTest, PointMinusVector) {
  Point p(3, 2, 1);
  Vector v(5, 6, 7);
  EXPECT_EQ(p - v, Point(-2, -4, -6));
}

TEST(TupleTest, VectorMinusVector) {
  Vector v0(3, 2, 1);
  Vector v1(5, 6, 7);
  EXPECT_EQ(v0 - v1, Vector(-2, -4, -6));
}

TEST(TupleTest, Negation) {
  Tuple t(1, -2, 3, -4);
  EXPECT_EQ(-t, Tuple(-1, 2, -3, 4));
}

TEST(TupleTest, MultByScalar) {
  Tuple t(1, -2, 3, -4);
  EXPECT_EQ(t * 3.5, Tuple(3.5, -7, 10.5, -14));
}

TEST(TupleTest, MultByFraction) {
  Tuple t(1, -2, 3, -4);
  EXPECT_EQ(t * 0.5, Tuple(0.5, -1, 1.5, -2));
}

TEST(TupleTest, DivByScalar) {
  Tuple t(1, -2, 3, -4);
  EXPECT_EQ(t / 2, Tuple(0.5, -1, 1.5, -2));
}

TEST(TupleTest, Magnitude0) {
  Vector v(1, 0, 0);
  EXPECT_FLOAT_EQ(v.magnitude(), 1);
}

TEST(TupleTest, Magnitude1) {
  Vector v(0, 1, 0);
  EXPECT_FLOAT_EQ(v.magnitude(), 1);
}

TEST(TupleTest, Magnitude2) {
  Vector v(0, 0, 1);
  EXPECT_FLOAT_EQ(v.magnitude(), 1);
}

TEST(TupleTest, Magnitude3) {
  Vector v(1, 2, 3);
  EXPECT_FLOAT_EQ(v.magnitude(), sqrtf(14));
}

TEST(TupleTest, Magnitude4) {
  Vector v(-1, -2, -3);
  EXPECT_FLOAT_EQ(v.magnitude(), sqrtf(14));
}

TEST(TupleTest, Normalize0) {
  Vector v(4, 0, 0);
  EXPECT_EQ(v.normalize(), Vector(1, 0, 0));
}

TEST(TupleTest, Normalize1) {
  Vector v(1, 2, 3);
  EXPECT_EQ(v.normalize(), Vector(1 / sqrtf(14), 2 / sqrtf(14), 3 / sqrtf(14)));
}

TEST(TupleTest, Normalize2) {
  Vector v(1, 2, 3);
  EXPECT_FLOAT_EQ(v.normalize().magnitude(), 1);
}

TEST(TupleTest, Dot) {
  Vector v0(1, 2, 3);
  Vector v1(2, 3, 4);
  EXPECT_FLOAT_EQ(v0.dot(v1), 20);
}

TEST(TupleTest, Cross) {
  Vector v0(1, 2, 3);
  Vector v1(2, 3, 4);
  EXPECT_EQ(v0.cross(v1), Vector(-1, 2, -1));
  EXPECT_EQ(v1.cross(v0), Vector(1, -2, 1));
}

TEST(TupleTest, Reflect0) {
  Vector v(1, -1, 0);
  Vector n(0, 1, 0);
  EXPECT_EQ(v.reflect(n), Vector(1, 1, 0));
}

TEST(TupleTest, Reflect1) {
  Vector v(0, -1, 0);
  Vector n(sqrtf(2) / 2, sqrtf(2) / 2, 0);
  EXPECT_EQ(v.reflect(n), Vector(1, 0, 0));
}
