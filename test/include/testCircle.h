#ifndef TEST_CIRCLE_H
#define TEST_CIRCLE_H

#include "helper.h"
#include "include/circle.hpp"

TEST(Circle2, normalTesting) {
  ns_geo::Circlef cir({1.0, 1.0}, 1.0);
  test_point2f_eq(cir.cen, {1.0, 1.0});
  EXPECT_FLOAT_EQ(cir.rad, 1.0);

  float dis = cir.distance(ns_geo::Point2f(0.0, 0.0));
  EXPECT_FLOAT_EQ(dis + 1.0, ns_geo::distance(cir.cen, {0.0, 0.0}));

  cir = ns_geo::Circlef::fit({{0.0, 1.0}, {1.0, 0.0}, {1.0, 2.0}});
  test_point2f_eq(cir.cen, {1.0, 1.0});
  EXPECT_FLOAT_EQ(cir.rad, 1.0);

  cir = ns_geo::Circlef::ransac({{0.0, 1.0}, {1.0, 0.0}, {1.0, 2.0}});
  test_point2f_eq(cir.cen, {1.0, 1.0});
  EXPECT_FLOAT_EQ(cir.rad, 1.0);

  test_point2f_eq(cir.nearest({-1.0, 1.0}), {0.0, 1.0});
}

#endif