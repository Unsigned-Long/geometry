#pragma once

#include "include/line.hpp"
#include "helper.h"

TEST(Line2f, normalTesting) {
  ns_geo::Point2f p1(0.0f, 1.0f), p2(2.0f, 3.0f);
  ns_geo::Line2f line(0.0f, 1.0f, 2.0f, 3.0f);

  test_point2f_eq(line.p1, p1);
  test_point2f_eq(line.p2, p2);

  ns_geo::Point2f ps[2] = {{0.0f, 1.0f}, {2.0f, 3.0f}};

  line = ns_geo::Line2f(ps);
  test_point2f_eq(line.p1, ps[0]);
  test_point2f_eq(line.p2, ps[1]);

  std::array<ns_geo::Point2f, 2> ary;
  ary[0] = {0.0f, 1.0f}, ary[1] = {2.0f, 3.0f};

  line = ns_geo::Line2f(ary);
  test_point2f_eq(line.p1, p1);
  test_point2f_eq(line.p2, p2);

  auto points = line.points();
  test_point2f_eq(points[0], ary[0]);
  test_point2f_eq(points[1], ary[1]);

  line.reverse();
  test_point2f_eq(line.p1, ary[1]);
  test_point2f_eq(line.p2, ary[0]);

  auto l = line.reversed();
  test_point2f_eq(l.p1, ary[0]);
  test_point2f_eq(l.p2, ary[1]);

  EXPECT_EQ(l.type(), ns_geo::GeoType::LINE2);
}

TEST(Line2f, methodsTesting) {
  ns_geo::Point2f p1(0.0f, 0.0f), p2(2.0f, 3.0f);
  ns_geo::Line2f line(p1, p2);

  EXPECT_FLOAT_EQ(line.length(), std::sqrt(13.0f));

  EXPECT_FLOAT_EQ(line.azimuthRHR(), std::atan2(2.0f, 3.0f));

  EXPECT_FLOAT_EQ(line.azimuthLHR(), std::atan2(3.0f, 2.0f));
}

TEST(Line2f, typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::Line2f::value_type>();
  testing::StaticAssertTypeEq<ns_geo::Point2f, ns_geo::Line2f::point_type>();
  testing::StaticAssertTypeEq<std::array<ns_geo::Point2f, 2>,
                              ns_geo::Line2f::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::Line2f, ns_geo::Line2f::self_type>();
}

TEST(Line3f, normalTesting) {
  ns_geo::Point3f p1(0.0f, 1.0f, 1.0f), p2(2.0f, 3.0f, 1.0f);
  ns_geo::Line3f line(0.0f, 1.0f, 1.0f, 2.0f, 3.0f, 1.0f);

  test_point3f_eq(line.p1, p1);
  test_point3f_eq(line.p2, p2);

  ns_geo::Point3f ps[2] = {{0.0f, 1.0f, 1.0f}, {2.0f, 3.0f, 1.0f}};

  line = ns_geo::Line3f(ps);
  test_point3f_eq(line.p1, ps[0]);
  test_point3f_eq(line.p2, ps[1]);

  std::array<ns_geo::Point3f, 2> ary;
  ary[0] = {0.0f, 1.0f, 1.0f}, ary[1] = {2.0f, 3.0f, 1.0f};

  line = ns_geo::Line3f(ary);
  test_point3f_eq(line.p1, p1);
  test_point3f_eq(line.p2, p2);

  auto points = line.points();
  test_point3f_eq(points[0], ary[0]);
  test_point3f_eq(points[1], ary[1]);

  line.reverse();
  test_point3f_eq(line.p1, ary[1]);
  test_point3f_eq(line.p2, ary[0]);

  auto l = line.reversed();
  test_point3f_eq(l.p1, ary[0]);
  test_point3f_eq(l.p2, ary[1]);

  EXPECT_EQ(l.type(), ns_geo::GeoType::LINE3);
}

TEST(Line3f, methodsTesting) {
  ns_geo::Point3f p1(0.0f, 0.0f, 0.0f), p2(3.0f, 4.0f, 1.0f);
  ns_geo::Line3f line(p1, p2);

  EXPECT_FLOAT_EQ(line.length(), std::sqrt(26.0f));

  EXPECT_FLOAT_EQ(line.azimuthRHR(), std::atan2(3.0f, 4.0f));

  EXPECT_FLOAT_EQ(line.azimuthLHR(), std::atan2(4.0f, 3.0f));

  EXPECT_FLOAT_EQ(line.zenithRHR(), std::atan2(5.0f, 1.0f));

  EXPECT_FLOAT_EQ(line.zenithLHR(), std::atan2(5.0f, 1.0f));
}

TEST(Line3f, typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::Line3f::value_type>();
  testing::StaticAssertTypeEq<ns_geo::Point3f, ns_geo::Line3f::point_type>();
  testing::StaticAssertTypeEq<std::array<ns_geo::Point3f, 2>,
                              ns_geo::Line3f::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::Line3f, ns_geo::Line3f::self_type>();
}

TEST_F(TestRefPointSet2f, RefLine2f_normalTesting) {
  auto rl = _rps->createRefLine2(0, 1);
  test_point2f_eq(rl.p1(), _rps->at(0));
  test_point2f_eq(rl.p2(), _rps->at(1));

  EXPECT_EQ(rl.pid1, 0);
  EXPECT_EQ(rl.pid2, 1);

  EXPECT_EQ(_rps, rl.refPointSet());

  ns_geo::Line2f l(_rps->at(0), _rps->at(1));
  auto tl = static_cast<ns_geo::Line2f>(rl);

  test_point2f_eq(l.p1, tl.p1);
  test_point2f_eq(l.p2, tl.p2);

  rl.reverse();
  test_point2f_eq(rl.p1(), _rps->at(1));
  test_point2f_eq(rl.p2(), _rps->at(0));

  auto rvl = rl.reversed();
  test_point2f_eq(rvl.p1(), _rps->at(0));
  test_point2f_eq(rvl.p2(), _rps->at(1));

  auto ary = rl.refPoints();
  test_refpoint2f_eq(ary[0], _rps->at(1));
  test_refpoint2f_eq(ary[1], _rps->at(0));
}

TEST_F(TestRefPointSet2f, RefLine2f_methodsTesting) {
  auto rl = _rps->createRefLine2(0, 1);
  EXPECT_FLOAT_EQ(rl.length(), std::sqrt(2.0f));

  EXPECT_FLOAT_EQ(rl.azimuthRHR(), M_PI - std ::atan2(1.0f, 1.0f));
  EXPECT_FLOAT_EQ(rl.azimuthLHR(), 2 * M_PI - std ::atan2(1.0f, 1.0f));
}

TEST_F(TestRefPointSet2f, RefLine2f_typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::RefLine2f::value_type>();
  testing::StaticAssertTypeEq<uint, ns_geo::RefLine2f::id_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPoint2f,
                              ns_geo::RefLine2f::refpoint_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPointSet2f,
                              ns_geo::RefLine2f::refpointset_type>();
  testing::StaticAssertTypeEq<std::array<ns_geo::RefPoint2f, 2>,
                              ns_geo::RefLine2f::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::RefLine2f,
                              ns_geo::RefLine2f::self_type>();
}

TEST_F(TestRefPointSet3f, RefLine3f_normalTesting) {
  auto rl = _rps->createRefLine3(0, 1);
  test_point3f_eq(rl.p1(), _rps->at(0));
  test_point3f_eq(rl.p2(), _rps->at(1));

  EXPECT_EQ(rl.pid1, 0);
  EXPECT_EQ(rl.pid2, 1);

  EXPECT_EQ(_rps, rl.refPointSet());

  ns_geo::Line3f l(_rps->at(0), _rps->at(1));
  auto tl = static_cast<ns_geo::Line3f>(rl);

  test_point3f_eq(l.p1, tl.p1);
  test_point3f_eq(l.p2, tl.p2);

  rl.reverse();
  test_point3f_eq(rl.p1(), _rps->at(1));
  test_point3f_eq(rl.p2(), _rps->at(0));

  auto rvl = rl.reversed();
  test_point3f_eq(rvl.p1(), _rps->at(0));
  test_point3f_eq(rvl.p2(), _rps->at(1));

  auto ary = rl.refPoints();
  test_refpoint3f_eq(ary[0], _rps->at(1));
  test_refpoint3f_eq(ary[1], _rps->at(0));
}

TEST_F(TestRefPointSet3f, RefLine3f_methodsTesting) {
  auto rl = _rps->createRefLine3(0, 1);
  EXPECT_FLOAT_EQ(rl.length(), std::sqrt(2.0f));

  EXPECT_FLOAT_EQ(rl.azimuthRHR(), M_PI - std ::atan2(1.0f, 1.0f));
  EXPECT_FLOAT_EQ(rl.azimuthLHR(), 2 * M_PI - std ::atan2(1.0f, 1.0f));

  EXPECT_FLOAT_EQ(rl.zenithRHR(), 0.5 * M_PI);
  EXPECT_FLOAT_EQ(rl.zenithLHR(), 0.5 * M_PI);
}

TEST_F(TestRefPointSet3f, RefLine3f_typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::RefLine3f::value_type>();
  testing::StaticAssertTypeEq<uint, ns_geo::RefLine3f::id_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPoint3f,
                              ns_geo::RefLine3f::refpoint_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPointSet3f,
                              ns_geo::RefLine3f::refpointset_type>();
  testing::StaticAssertTypeEq<std::array<ns_geo::RefPoint3f, 2>,
                              ns_geo::RefLine3f::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::RefLine3f,
                              ns_geo::RefLine3f::self_type>();
}