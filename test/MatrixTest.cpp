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

TEST(MatrixTest, IdentityXMatrix) {
  M4x4 m = {{{0, 1, 2, 4}, {1, 2, 4, 8}, {2, 4, 8, 16}, {4, 8, 16, 32}}};
  EXPECT_TRUE(eq(mult(m, I4x4), m));
}

TEST(MatrixTest, IdentityXTuple) {
  Tuple t(1, 2, 3, 4);
  EXPECT_EQ(mult(I4x4, t), t);
}

TEST(MatrixTest, Transpose) {
  M4x4 m = {{{0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0, 5, 8}}};
  M4x4 t = {{{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}}};
  EXPECT_TRUE(eq(transpose(m), t));
}

TEST(MatrixTest, TransposeIdentity) { EXPECT_TRUE(eq(transpose(I4x4), I4x4)); }

TEST(MatrixTest, Determinant2x2) {
  M2x2 m = {{{1, 5}, {-3, 2}}};
  EXPECT_FLOAT_EQ(determinant(m), 17);
}

TEST(MatrixTest, SubmatrixM4x4) {
  M4x4 m = {{{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}}};
  M3x3 s = {{{-6, 1, 6}, {-8, 8, 6}, {-7, -1, 1}}};
  EXPECT_TRUE(eq(submatrix(m, 2, 1), s));
}

TEST(MatrixTest, SubmatrixM3x3) {
  M3x3 m = {{{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}}};
  M2x2 s = {{{-3, 2}, {0, 6}}};
  EXPECT_TRUE(eq(submatrix(m, 0, 2), s));
}

TEST(MatrixTest, Minor) {
  M3x3 m = {{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}}};
  EXPECT_FLOAT_EQ(minor(m, 1, 0), 25);
}

TEST(MatrixTest, Cofactor) {
  M3x3 m = {{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}}};
  EXPECT_FLOAT_EQ(cofactor(m, 0, 0), -12);
  EXPECT_FLOAT_EQ(cofactor(m, 1, 0), -25);
}

TEST(MatrixTest, Determinant3x3) {
  M3x3 m = {{{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}}};
  EXPECT_FLOAT_EQ(determinant(m), -196);
}

TEST(MatrixTest, Determinant4x4) {
  M4x4 m = {{{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}}};
  EXPECT_FLOAT_EQ(determinant(m), -4071);
}

TEST(MatrixTest, Invertible) {
  M4x4 m = {{{6, 4, 4, 4}, {5, 5, 7, 6}, {4, -9, 3, -7}, {9, 1, 7, -6}}};
  EXPECT_FLOAT_EQ(determinant(m), -2120);
  EXPECT_TRUE(isInvertible(m));
}

TEST(MatrixTest, NonInvertible) {
  M4x4 m = {{{-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1 - 5}, {0, 0, 0, 0}}};
  EXPECT_FLOAT_EQ(determinant(m), 0);
  EXPECT_FALSE(isInvertible(m));
}

TEST(MatrixTest, Inverse0) {
  M4x4 m = {{{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}}};
  M4x4 inv = {{{0.21805, 0.45113, 0.24060, -0.04511},
               {-0.80827, -1.45677, -0.44361, 0.52068},
               {-0.07895, -0.22368, -0.05263, 0.19737},
               {-0.52256, -0.81391, -0.30075, 0.30639}}};
  EXPECT_TRUE(eq(inverse(m), inv));
}

TEST(MatrixTest, Inverse1) {
  M4x4 m = {{{8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}}};
  M4x4 inv = {{{-0.15385, -0.15385, -0.28205, -0.53846},
               {-0.07692, 0.12308, 0.02564, 0.03077},
               {0.35897, 0.35897, 0.43590, 0.92308},
               {-0.69231, -0.69231, -0.76923, -1.92308}}};
  EXPECT_TRUE(eq(inverse(m), inv));
}

TEST(MatrixTest, Inverse2) {
  M4x4 m = {{{9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}}};
  M4x4 inv = {{{-0.04074, -0.07778, 0.14444, -0.22222},
               {-0.07778, 0.03333, 0.36667, -0.33333},
               {-0.02901, -0.14630, -0.10926, 0.12963},
               {0.17778, 0.06667, -0.26667, 0.33333}}};
  EXPECT_TRUE(eq(inverse(m), inv));
}

TEST(MatrixTest, Inverse3) {
  M4x4 a = {{{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}}};
  M4x4 b = {{{8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}}};
  M4x4 c = mult(a, b);
  EXPECT_TRUE(eq(mult(c, inverse(b)), a));
}
