#ifndef TEST_CIRCLE_H
#define TEST_CIRCLE_H

#include "helper.h"
#include "include/circle.hpp"

TEST(Circle, normalTesting) {
  ns_geo::Circle cir({1.0, 1.0}, 1.0);
  test_point2d_eq(cir.cen, {1.0, 1.0});
  EXPECT_DOUBLE_EQ(cir.rad, 1.0);

  double dis = cir.distance(ns_geo::Point2d(0.0, 0.0));
  EXPECT_FLOAT_EQ(dis + 1.0, ns_geo::distance(cir.cen, {0.0, 0.0}));

  cir = ns_geo::Circle::fit({{0.0, 1.0}, {1.0, 0.0}, {1.0, 2.0}});
  test_point2d_eq(cir.cen, {1.0, 1.0});
  EXPECT_DOUBLE_EQ(cir.rad, 1.0);

  cir = ns_geo::Circle::ransac({{0.0, 1.0}, {1.0, 0.0}, {1.0, 2.0}});
  test_point2d_eq(cir.cen, {1.0, 1.0});
  EXPECT_DOUBLE_EQ(cir.rad, 1.0);

  test_point2d_eq(cir.nearest({-1.0, 1.0}), {0.0, 1.0});

  EXPECT_EQ(cir.type(), ns_geo::GeoType::CIRCLE);
}

#endif