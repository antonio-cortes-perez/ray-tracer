#include <gtest/gtest.h>

#include "Color.h"

using namespace ray_tracer;

TEST(ColorTest, Creation) {
  Color c(-0.5, 0.4, 1.7);
  EXPECT_FLOAT_EQ(c.r, -0.5);
  EXPECT_FLOAT_EQ(c.g, 0.4);
  EXPECT_FLOAT_EQ(c.b, 1.7);
}

TEST(ColorTest, Addition) {
  Color c0(0.9, 0.6, 0.75);
  Color c1(0.7, 0.1, 0.25);
  EXPECT_EQ(c0 + c1, Color(1.6, 0.7, 1.0));
}

TEST(ColorTest, Subtraction) {
  Color c0(0.9, 0.6, 0.75);
  Color c1(0.7, 0.1, 0.25);
  EXPECT_EQ(c0 - c1, Color(0.2, 0.5, 0.5));
}

TEST(ColorTest, MultByScalar) {
  Color c(0.2, 0.3, 0.4);
  EXPECT_EQ(c * 2, Color(0.4, 0.6, 0.8));
}

TEST(ColorTest, Mult) {
  Color c0(1, 0.2, 0.4);
  Color c1(0.9, 1, 0.1);
  EXPECT_EQ(c0 * c1, Color(0.9, 0.2, 0.04));
}
