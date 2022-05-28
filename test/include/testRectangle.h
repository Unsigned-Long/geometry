#pragma once

#include "include/rectangle.hpp"
#include "helper.h"

TEST(Rectanglef, normalTesting) {
  ns_geo::Rectanglef rect(0.0f, 1.0f, 1.0f, 0.0f);

  test_point2f_eq(rect.topLeftPt, {0.0f, 1.0f});
  test_point2f_eq(rect.bottomRightPt, {1.0f, 0.0f});

  auto points = rect.points();
  test_point2f_eq(points[0], {0.0f, 1.0f});
  test_point2f_eq(points[1], {1.0f, 0.0f});

  rect = ns_geo::Rectanglef(points);

  EXPECT_FLOAT_EQ(rect.area(), 1.0f);
  EXPECT_FLOAT_EQ(rect.perimeter(), 4.0f);

  EXPECT_EQ(rect.type(), ns_geo::GeoType::RECTANGLE);
}

TEST(Rectanglef, typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::Rectanglef::value_type>();
  testing::StaticAssertTypeEq<ns_geo::Point2f,
                              ns_geo::Rectanglef::point_type>();
  testing::StaticAssertTypeEq<std::array<ns_geo::Point2f, 2>,
                              ns_geo::Rectanglef::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::Rectanglef,
                              ns_geo::Rectanglef::self_type>();
}

TEST_F(TestRefPointSet2f, refrectangle_normalTesting) {
  auto rect = _rps->createRefRectangle(0, 1);

  test_refpoint2f_eq(rect.topLeft(), {0, 0.0f, 2.0f});
  test_refpoint2f_eq(rect.bottomRight(), {1, 1.0f, 1.0f});

  auto refPoints = rect.refPoints();
  test_refpoint2f_eq(refPoints[0], {0, 0.0f, 2.0f});
  test_refpoint2f_eq(refPoints[1], {1, 1.0f, 1.0f});

  EXPECT_FLOAT_EQ(rect.area(), 1.0f);
  EXPECT_FLOAT_EQ(rect.perimeter(), 4.0f);

  EXPECT_EQ(_rps, rect.refPointSet());

  EXPECT_EQ(0, rect.topLeftPID);
  EXPECT_EQ(1, rect.bottomRightPID);

  EXPECT_EQ(rect.type(), ns_geo::GeoType::REF_RECTANGLE);
}

TEST_F(TestRefPointSet2f, refrectangle_typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::RefRectanglef::value_type>();
  testing::StaticAssertTypeEq<uint, ns_geo::RefRectanglef::id_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPoint2f,
                              ns_geo::RefRectanglef::refpoint_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPointSet2f,
                              ns_geo::RefRectanglef::refpointset_type>();
  testing::StaticAssertTypeEq<std::array<ns_geo::RefPoint2f, 2>,
                              ns_geo::RefRectanglef::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::RefRectanglef,
                              ns_geo::RefRectanglef::self_type>();
}
