#ifndef MATRIX_H_
#define MATRIX_H_

#include <cmath>

#include "Tuple.h"

namespace ray_tracer {

using M2x2 = std::array<std::array<float, 2>, 2>;
using M3x3 = std::array<std::array<float, 3>, 3>;
using M4x4 = std::array<std::array<float, 4>, 4>;

static constexpr M4x4 I4x4 = {
    {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};

template <unsigned long M>
inline bool eq(const std::array<std::array<float, M>, M> &m0,
               const std::array<std::array<float, M>, M> &m1) {
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < M; ++j) {
      if (!eqf(m0[i][j], m1[i][j]))
        return false;
    }
  }
  return true;
}

inline M4x4 mult(const M4x4 &a, const M4x4 &b) {
  M4x4 c;
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      c[row][col] = a[row][0] * b[0][col] + a[row][1] * b[1][col] +
                    a[row][2] * b[2][col] + a[row][3] * b[3][col];
    }
  }
  return c;
}

inline Tuple mult(const M4x4 &m, const Tuple &t) {
  Tuple r;
  r.x = m[0][0] * t.x + m[0][1] * t.y + m[0][2] * t.z + m[0][3] * t.w;
  r.y = m[1][0] * t.x + m[1][1] * t.y + m[1][2] * t.z + m[1][3] * t.w;
  r.z = m[2][0] * t.x + m[2][1] * t.y + m[2][2] * t.z + m[2][3] * t.w;
  r.w = m[3][0] * t.x + m[3][1] * t.y + m[3][2] * t.z + m[3][3] * t.w;
  return r;
}

inline M4x4 transpose(const M4x4 &m) {
  M4x4 t;
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      t[col][row] = m[row][col];
    }
  }
  return t;
}

inline float determinant(const M2x2 &m) {
  return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

template <unsigned long M>
inline std::array<std::array<float, M - 1>, M - 1>
submatrix(const std::array<std::array<float, M>, M> &m, int skipRow,
          int skipCol) {
  std::array<std::array<float, M - 1>, M - 1> s;
  for (int row = 0, subRow = 0; row < M; ++row) {
    if (row == skipRow)
      continue;
    for (int col = 0, subCol = 0; col < M; ++col) {
      if (col == skipCol)
        continue;
      s[subRow][subCol] = m[row][col];
      ++subCol;
    }
    ++subRow;
  }
  return s;
}

template <unsigned long M>
inline float determinant(const std::array<std::array<float, M>, M> &m) {
  float det = 0;
  for (int col = 0; col < M; ++col) {
    float minor = determinant(submatrix(m, 0, col));
    float cofactor = (col % 2 == 0) ? minor : -minor;
    det += m[0][col] * cofactor;
  }
  return det;
}

template <unsigned long M>
inline float minor(const std::array<std::array<float, M>, M> &m, int row,
                   int col) {
  return determinant(submatrix(m, row, col));
}

template <unsigned long M>
inline float cofactor(const std::array<std::array<float, M>, M> &m, int row,
                      int col) {
  return ((row + col) % 2 == 0) ? minor(m, row, col) : -minor(m, row, col);
}

inline bool isInvertible(const M4x4 &m) { return !eqf(determinant(m), 0); }

inline M4x4 inverse(const M4x4 &m) {
  float det = determinant(m);
  assert(!eqf(det, 0));

  M4x4 result;
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      float cof = cofactor(m, row, col);
      result[col][row] = cof / det;
    }
  }
  return result;
}

} // namespace ray_tracer

#endif // MATRIX_H_