#include <gtest/gtest.h>

#include "Transformations.h"

using namespace ray_tracer;

TEST(TransformationsTest, Translation0) {
  M4x4 t = translation(5, -3, 2);
  Point p(-3, 4, 5);
  EXPECT_EQ(mult(t, p), Point(2, 1, 7));
}

TEST(TransformationsTest, Translation1) {
  M4x4 t = inverse(translation(5, -3, 2));
  Point p(-3, 4, 5);
  EXPECT_EQ(mult(t, p), Point(-8, 7, 3));
}

TEST(TransformationsTest, Translation2) {
  M4x4 t = translation(5, -3, 2);
  Vector v(-3, 4, 5);
  EXPECT_EQ(mult(t, v), v);
}

TEST(TransformationsTest, Scaling0) {
  M4x4 s = scaling(2, 3, 4);
  Point p(-4, 6, 8);
  EXPECT_EQ(mult(s, p), Point(-8, 18, 32));
}

TEST(TransformationsTest, Scaling1) {
  M4x4 s = scaling(2, 3, 4);
  Vector v(-4, 6, 8);
  EXPECT_EQ(mult(s, v), Vector(-8, 18, 32));
}

TEST(TransformationsTest, Scaling2) {
  M4x4 s = inverse(scaling(2, 3, 4));
  Vector v(-4, 6, 8);
  EXPECT_EQ(mult(s, v), Vector(-2, 2, 2));
}

TEST(TransformationsTest, Scaling3) {
  M4x4 s = scaling(-1, 1, 1);
  Point p(2, 3, 4);
  EXPECT_EQ(mult(s, p), Point(-2, 3, 4));
}

TEST(TransformationsTest, RotationX0) {
  M4x4 halfQuarter = rotationX(PI / 4);
  M4x4 fullQuarter = rotationX(PI / 2);
  Point p(0, 1, 0);
  EXPECT_EQ(mult(halfQuarter, p), Point(0, sqrtf(2) / 2, sqrtf(2) / 2));
  EXPECT_EQ(mult(fullQuarter, p), Point(0, 0, 1));
}

TEST(TransformationsTest, RotationX1) {
  M4x4 halfQuarter = inverse(rotationX(PI / 4));
  M4x4 fullQuarter = inverse(rotationX(PI / 2));
  Point p(0, 1, 0);
  EXPECT_EQ(mult(halfQuarter, p), Point(0, sqrtf(2) / 2, -sqrtf(2) / 2));
  EXPECT_EQ(mult(fullQuarter, p), Point(0, 0, -1));
}

TEST(TransformationsTest, RotationY0) {
  M4x4 halfQuarter = rotationY(PI / 4);
  M4x4 fullQuarter = rotationY(PI / 2);
  Point p(0, 0, 1);
  EXPECT_EQ(mult(halfQuarter, p), Point(sqrtf(2) / 2, 0, sqrtf(2) / 2));
  EXPECT_EQ(mult(fullQuarter, p), Point(1, 0, 0));
}

TEST(TransformationsTest, RotationY1) {
  M4x4 halfQuarter = inverse(rotationY(PI / 4));
  M4x4 fullQuarter = inverse(rotationY(PI / 2));
  Point p(0, 0, 1);
  EXPECT_EQ(mult(halfQuarter, p), Point(-sqrtf(2) / 2, 0, sqrtf(2) / 2));
  EXPECT_EQ(mult(fullQuarter, p), Point(-1, 0, 0));
}

TEST(TransformationsTest, RotationZ0) {
  M4x4 halfQuarter = rotationZ(PI / 4);
  M4x4 fullQuarter = rotationZ(PI / 2);
  Point p(0, 1, 0);
  EXPECT_EQ(mult(halfQuarter, p), Point(-sqrtf(2) / 2, sqrtf(2) / 2, 0));
  EXPECT_EQ(mult(fullQuarter, p), Point(-1, 0, 0));
}

TEST(TransformationsTest, RotationZ1) {
  M4x4 halfQuarter = inverse(rotationZ(PI / 4));
  M4x4 fullQuarter = inverse(rotationZ(PI / 2));
  Point p(0, 1, 0);
  EXPECT_EQ(mult(halfQuarter, p), Point(sqrtf(2) / 2, sqrtf(2) / 2, 0));
  EXPECT_EQ(mult(fullQuarter, p), Point(1, 0, 0));
}

TEST(TransformationsTest, ShearingXY) {
  M4x4 s = shearing(1, 0, 0, 0, 0, 0);
  Point p(2, 3, 4);
  EXPECT_EQ(mult(s, p), Point(5, 3, 4));
}

TEST(TransformationsTest, ShearingXZ) {
  M4x4 s = shearing(0, 1, 0, 0, 0, 0);
  Point p(2, 3, 4);
  EXPECT_EQ(mult(s, p), Point(6, 3, 4));
}

TEST(TransformationsTest, ShearingYX) {
  M4x4 s = shearing(0, 0, 1, 0, 0, 0);
  Point p(2, 3, 4);
  EXPECT_EQ(mult(s, p), Point(2, 5, 4));
}

TEST(TransformationsTest, ShearingYZ) {
  M4x4 s = shearing(0, 0, 0, 1, 0, 0);
  Point p(2, 3, 4);
  EXPECT_EQ(mult(s, p), Point(2, 7, 4));
}

TEST(TransformationsTest, ShearingZX) {
  M4x4 s = shearing(0, 0, 0, 0, 1, 0);
  Point p(2, 3, 4);
  EXPECT_EQ(mult(s, p), Point(2, 3, 6));
}

TEST(TransformationsTest, ShearingZY) {
  M4x4 s = shearing(0, 0, 0, 0, 0, 1);
  Point p(2, 3, 4);
  EXPECT_EQ(mult(s, p), Point(2, 3, 7));
}

TEST(TransformationsTest, Sequence0) {
  Point p0(1, 0, 1);
  Point p1 = mult(rotationX(PI / 2), p0);
  EXPECT_EQ(p1, Point(1, -1, 0));
  Point p2 = mult(scaling(5, 5, 5), p1);
  EXPECT_EQ(p2, Point(5, -5, 0));
  Point p3 = mult(translation(10, 5, 7), p2);
  EXPECT_EQ(p3, Point(15, 0, 7));
}

TEST(TransformationsTest, Sequence1) {
  Point p(1, 0, 1);
  M4x4 t =
      mult(translation(10, 5, 7), mult(scaling(5, 5, 5), rotationX(PI / 2)));
  EXPECT_EQ(mult(t, p), Point(15, 0, 7));
}
