#ifndef TEST_SLINE_H
#define TEST_SLINE_H

#include "helper.h"
#include "include/sline.hpp"

TEST(SLine2, normalTesting) {
  ns_geo::SLine2 l({0, 0}, {1, 1});
  test_point2d_eq(l.nearest({0, 1}), {0.5, 0.5});

  EXPECT_DOUBLE_EQ(l.distance({0, 1}), std::sqrt(2) / 2.0);

  auto l1 = ns_geo::SLine2::ransac({{0, 0}, {1, 1}}, 2);
  auto l2 = ns_geo::SLine2::fit({{0, 0}, {1, 1}}, 2);

  EXPECT_TRUE(std::abs(std::abs(l1.a) - std::abs(l2.a) < 1E-10));
  EXPECT_TRUE(std::abs(std::abs(l1.b) - std::abs(l2.b) < 1E-10));
  EXPECT_TRUE(std::abs(std::abs(l1.c) - std::abs(l2.c) < 1E-10));

  EXPECT_EQ(l.type(), ns_geo::GeoType::SLINE2);
}

#endif