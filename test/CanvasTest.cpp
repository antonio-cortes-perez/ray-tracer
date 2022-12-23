#include <gtest/gtest.h>

#include "Canvas.h"

using namespace ray_tracer;

TEST(CanvasTest, Creation) {
  Canvas cv(10, 20);
  EXPECT_EQ(cv.width, 10);
  EXPECT_EQ(cv.height, 20);
  for (auto &c : cv) {
    EXPECT_EQ(c, Color(0, 0, 0));
  }
}

TEST(CanvasTest, SetPixel) {
  Canvas cv(10, 20);
  Color r(1, 0, 0);
  cv.set(2, 3, r);
  EXPECT_EQ(cv.get(2, 3), r);
}

TEST(CanvasTest, ToPPM) {
  Canvas cv(5, 3);
  cv.set(0, 0, {1.5, 0, 0});
  cv.set(2, 1, {0, 0.5, 0});
  cv.set(4, 2, {-0.5, 0, 1});
  EXPECT_EQ(cv.toPPM(), "P3\n"
                        "5 3\n"
                        "255\n"
                        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n");
}

TEST(CanvasTest, ToPPMLongLines) {
  Canvas cv(10, 2);
  for (Color &c : cv) {
    c.r = 1;
    c.g = 0.8;
    c.b = 0.6;
  }
  EXPECT_EQ(
      cv.toPPM(),
      "P3\n"
      "10 2\n"
      "255\n"
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
      "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
      "153 255 204 153 255 204 153 255 204 153 255 204 153\n");
}
