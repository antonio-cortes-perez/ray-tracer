#include <gtest/gtest.h>

#include "Matrix.h"

using namespace ray_tracer;

TEST(MatrixTest, Equal) {
  M4x4 m0 = {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}};
  M4x4 m1 = {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}};
  EXPECT_TRUE(eq(m0, m1));
}

TEST(MatrixTest, NotEqual) {
  M4x4 m0 = {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}};
  M4x4 m1 = {{{2, 3, 4, 5}, {6, 7, 8, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}}};
  EXPECT_FALSE(eq(m0, m1));
}

TEST(MatrixTest, Mult) {
  M4x4 a = {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}};
  M4x4 b = {{{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}}};
  M4x4 c = {{{20, 22, 50, 48},
             {44, 54, 114, 108},
             {40, 58, 110, 102},
             {16, 26, 46, 42}}};
  EXPECT_TRUE(eq(mult(a, b), c));
}

TEST(MatrixTest, MatrixXTuple) {
  M4x4 m = {{{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}}};
  Tuple t(1, 2, 3, 1);
  EXPECT_EQ(mult(m, t), Tuple(18, 24, 33, 1));
}
