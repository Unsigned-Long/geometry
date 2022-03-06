#pragma once

/**
 * @file testPoint.h
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "helper.h"

TEST(Point2f, normalTesting) {
  const ns_geo::Point2f p1(1.0f, 2.0f);
  EXPECT_FLOAT_EQ(1.0f, p1.x());
  EXPECT_FLOAT_EQ(2.0f, p1.y());

  ns_geo::Point2f p2(3.0f, 4.0f);
  EXPECT_FLOAT_EQ(3.0f, p2.x());
  EXPECT_FLOAT_EQ(4.0f, p2.y());

  p2.x() = 10.0f;
  EXPECT_FLOAT_EQ(10.0f, p2.x());

  auto ary = static_cast<ns_geo::Point2f::ary_type>(p2);
  EXPECT_FLOAT_EQ(10.0f, ary[0]);
  EXPECT_FLOAT_EQ(4.0f, ary[1]);

  auto ps = ns_geo::Point2f(1.0f, 2.0f);
  ps.transpose();
  EXPECT_FLOAT_EQ(ps.x(), 2.0f);
  EXPECT_FLOAT_EQ(ps.y(), 1.0f);

  EXPECT_EQ(ns_geo::GeoType::POINT2D, p1.type());
}

TEST(Point2f, typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::Point2f::value_type>();
  testing::StaticAssertTypeEq<std::array<float, 2>,
                              ns_geo::Point2f::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::Point2f, ns_geo::Point2f::self_type>();
}

TEST(Point3f, normalTesting) {
  const ns_geo::Point3f p1(1.0f, 2.0f, 3.0f);
  EXPECT_FLOAT_EQ(1.0f, p1.x());
  EXPECT_FLOAT_EQ(2.0f, p1.y());
  EXPECT_FLOAT_EQ(3.0f, p1.z());

  ns_geo::Point3f p2(3.0f, 4.0f, 5.0f);
  EXPECT_FLOAT_EQ(3.0f, p2.x());
  EXPECT_FLOAT_EQ(4.0f, p2.y());
  EXPECT_FLOAT_EQ(5.0f, p2.z());

  p2.x() = 10.0f;
  EXPECT_FLOAT_EQ(10.0f, p2.x());

  auto ary = static_cast<ns_geo::Point3f::ary_type>(p2);
  EXPECT_FLOAT_EQ(10.0f, ary[0]);
  EXPECT_FLOAT_EQ(4.0f, ary[1]);
  EXPECT_FLOAT_EQ(5.0f, ary[2]);

  EXPECT_EQ(ns_geo::GeoType::POINT3D, p1.type());
}

TEST(Point3f, typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::Point3f::value_type>();
  testing::StaticAssertTypeEq<std::array<float, 3>,
                              ns_geo::Point3f::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::Point3f, ns_geo::Point3f::self_type>();
}

TEST(PointSet2f, writeAndRead) {
  ns_geo::PointSet2f ps1, ps2;
  ps1.push_back(ns_geo::Point2f(1.0f, 2.0f));
  ps1.push_back(ns_geo::Point2f(2.0f, 3.0f));

  ps1.write("../output/pointset.csv", std::ios::out);
  ps2.read("../output/pointset.csv", std::ios::in);

  EXPECT_EQ(ps1.size(), ps2.size());

  for (int i = 0; i != ps2.size(); ++i)
    test_point2f_eq(ps1[i], ps2[i]);

  ps2.write("../output/pointset.bin");
  ps1.clear();
  ps1.read("../output/pointset.bin");

  EXPECT_EQ(ps1.size(), ps2.size());

  for (int i = 0; i != ps2.size(); ++i)
    test_point2f_eq(ps1[i], ps2[i]);
}

TEST(PointSet2f, randomGenerator) {
  auto foo = [](const ns_geo::Point2f &p) -> bool { return p.x() > 0.5f; };

  auto ps = ns_geo::PointSet2f::randomGenerator(10, 0.0f, 10.0f, 0.0f, 10.0f, foo);

  EXPECT_EQ(ps.size(), 10);

  for (const auto &elem : ps)
    EXPECT_TRUE(foo(elem));
}

TEST(PointSet2f, typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::PointSet2f::value_type>();
  testing::StaticAssertTypeEq<ns_geo::Point2f,
                              ns_geo::PointSet2f::point_type>();
  testing::StaticAssertTypeEq<std::vector<ns_geo::Point2f>,
                              ns_geo::PointSet2f::container_type>();
}

TEST(PointSet3f, writeAndRead) {
  ns_geo::PointSet3f ps1, ps2;
  ps1.push_back(ns_geo::Point3f(1.0f, 2.0f, 1.0f));
  ps1.push_back(ns_geo::Point3f(2.0f, 3.0f, 0.0f));

  ps1.write("../output/pointset.csv", std::ios::out);
  ps2.read("../output/pointset.csv", std::ios::in);

  EXPECT_EQ(ps1.size(), ps2.size());

  for (int i = 0; i != ps2.size(); ++i)
    test_point3f_eq(ps1[i], ps2[i]);

  ps2.write("../output/pointset.bin");
  ps1.clear();
  ps1.read("../output/pointset.bin");

  EXPECT_EQ(ps1.size(), ps2.size());

  for (int i = 0; i != ps2.size(); ++i)
    test_point3f_eq(ps1[i], ps2[i]);
}

TEST(PointSet3f, randomGenerator) {
  auto foo = [](const ns_geo::Point3f &p) -> bool { return p.x() > 0.5f; };

  auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 10.0f, 0.0f, 10.0f,
                                                0.0f, 10.0f, foo);

  EXPECT_EQ(ps.size(), 10);

  for (const auto &elem : ps)
    EXPECT_TRUE(foo(elem));
}

TEST(PointSet3f, typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::PointSet3f::value_type>();
  testing::StaticAssertTypeEq<ns_geo::Point3f,
                              ns_geo::PointSet3f::point_type>();
  testing::StaticAssertTypeEq<std::vector<ns_geo::Point3f>,
                              ns_geo::PointSet3f::container_type>();
}

TEST(RefPoint2f, normalTesting) {
  const ns_geo::RefPoint2d p1(0, ns_geo::RefPoint2d::ary_type{0.0f, 0.0f});

  EXPECT_EQ(0, p1.id());
  EXPECT_FLOAT_EQ(0.0f, p1.x());
  EXPECT_FLOAT_EQ(0.0f, p1.y());

  double ary[2] = {1.0f, 2.0f};
  ns_geo::RefPoint2d p2(1, ary);

  EXPECT_EQ(1, p2.id());
  EXPECT_FLOAT_EQ(1.0f, p2.x());
  EXPECT_FLOAT_EQ(2.0f, p2.y());

  EXPECT_EQ(ns_geo::GeoType::REFPOINT2D, p2.type());
}

TEST(RefPoint2f, typeTesting) {
  testing::StaticAssertTypeEq<uint, ns_geo::RefPoint2f::id_type>();
  testing::StaticAssertTypeEq<float, ns_geo::RefPoint2f::value_type>();
  testing::StaticAssertTypeEq<std::array<float, 2>,
                              ns_geo::RefPoint2f::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPoint2f,
                              ns_geo::RefPoint2f::self_type>();
}

TEST(RefPoint3f, normalTesting) {
  const ns_geo::RefPoint3d p1(0,
                              ns_geo::RefPoint3d::ary_type{0.0f, 0.0f, 0.0f});

  EXPECT_EQ(0, p1.id());
  EXPECT_FLOAT_EQ(0.0f, p1.x());
  EXPECT_FLOAT_EQ(0.0f, p1.y());
  EXPECT_FLOAT_EQ(0.0f, p1.z());

  double ary[3] = {1.0f, 2.0f, 3.0f};
  ns_geo::RefPoint3d p2(1, ary);

  EXPECT_EQ(1, p2.id());
  EXPECT_FLOAT_EQ(1.0f, p2.x());
  EXPECT_FLOAT_EQ(2.0f, p2.y());
  EXPECT_FLOAT_EQ(3.0f, p2.z());

  EXPECT_EQ(ns_geo::GeoType::REFPOINT3D, p2.type());
}

TEST(RefPoint3f, typeTesting) {
  testing::StaticAssertTypeEq<uint, ns_geo::RefPoint3f::id_type>();
  testing::StaticAssertTypeEq<float, ns_geo::RefPoint3f::value_type>();
  testing::StaticAssertTypeEq<std::array<float, 3>,
                              ns_geo::RefPoint3f::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPoint3f,
                              ns_geo::RefPoint3f::self_type>();
}

TEST(RefPointSet2f, normalTesting) {
  float ary[2] = {2.0f, 3.0f};
  ns_geo::RefPointSet2f rps;
  rps.insert({0, ns_geo::RefPoint2f::ary_type{0.0f, 0.0f}});
  rps.insert({1, ary});
  rps.insert({2, ns_geo::RefPoint2f::ary_type{0.0f, 0.0f}});
  rps.insert({4, ary});

  test_refpoint2f_eq(ns_geo::RefPoint2f(0, 0.0f, 0.0f), rps.at(0));
  test_refpoint2f_eq(ns_geo::RefPoint2f(4, 2.0f, 3.0f), rps.at(4));
}

TEST(RefPointSet2f, randomGenerator) {
  auto foo = [](const ns_geo::RefPoint2f &p) -> bool { return p.x() > 0.5f; };

  auto ps =
      ns_geo::RefPointSet2f::randomGenerator(10, 0.0f, 10.0f, 0.0f, 10.0f, foo);

  EXPECT_EQ(ps.size(), 10);

  for (const auto &elem : ps)
    EXPECT_TRUE(foo(elem.second));
}

TEST(RefPointSet2f, typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::RefPointSet2f::value_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPoint2f,
                              ns_geo::RefPointSet2f::refpoint_type>();
  testing::StaticAssertTypeEq<uint, ns_geo::RefPointSet2f::id_type>();
  testing::StaticAssertTypeEq<std::unordered_map<uint, ns_geo::RefPoint2f>,
                              ns_geo::RefPointSet2f::container_type>();
}

TEST(RefPointSet2f, writeAndRead) {
  float ary[2] = {2.0f, 3.0f};
  ns_geo::RefPointSet2f rps1, rps2;
  rps1.insert({0, ns_geo::RefPoint2f::ary_type{0.0f, 0.0f}});
  rps1.insert({1, ary});
  rps1.insert({2, ns_geo::RefPoint2f::ary_type{0.0f, 0.0f}});
  rps1.insert({3, ary});

  rps1.write("../output/refpointset.csv", std::ios::out);
  rps2.read("../output/refpointset.csv", std::ios::in);

  for (int i = 0; i != 4; ++i)
    test_refpoint2f_eq(rps1.at(i), rps2.at(i));
}

TEST(RefPointSet3f, normalTesting) {
  float ary[3] = {2.0f, 3.0f, 1.0f};
  ns_geo::RefPointSet3f rps;
  rps.insert({0, ns_geo::RefPoint3f::ary_type{0.0f, 0.0f, 0.0f}});
  rps.insert({1, ary});
  rps.insert({2, ns_geo::RefPoint3f::ary_type{0.0f, 0.0f, 0.0f}});
  rps.insert({4, ary});

  test_refpoint3f_eq(ns_geo::RefPoint3f(0, 0.0f, 0.0f, 0.0f), rps.at(0));
  test_refpoint3f_eq(ns_geo::RefPoint3f(4, 2.0f, 3.0f, 1.0f), rps.at(4));
}

TEST(RefPointSet3f, randomGenerator) {
  auto foo = [](const ns_geo::RefPoint3f &p) -> bool { return p.x() > 0.5f; };

  auto ps = ns_geo::RefPointSet3f::randomGenerator(10, 0.0f, 10.0f, 0.0f, 10.0f,
                                                   0.0f, 10.0f, foo);

  EXPECT_EQ(ps.size(), 10);

  for (const auto &elem : ps)
    EXPECT_TRUE(foo(elem.second));
}

TEST(RefPointSet3f, typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::RefPointSet3f::value_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPoint3f,
                              ns_geo::RefPointSet3f::refpoint_type>();
  testing::StaticAssertTypeEq<uint, ns_geo::RefPointSet3f::id_type>();
  testing::StaticAssertTypeEq<std::unordered_map<uint, ns_geo::RefPoint3f>,
                              ns_geo::RefPointSet3f::container_type>();
}

TEST(RefPointSet3f, writeAndRead) {
  float ary[3] = {2.0f, 3.0f, 1.0f};
  ns_geo::RefPointSet3f rps1, rps2;
  rps1.insert({0, ns_geo::RefPoint3f::ary_type{0.0f, 0.0f, 0.0f}});
  rps1.insert({1, ary});
  rps1.insert({2, ns_geo::RefPoint3f::ary_type{0.0f, 0.0f, 0.0f}});
  rps1.insert({3, ary});

  rps1.write("../output/refpointset.csv", std::ios::out);
  rps2.read("../output/refpointset.csv", std::ios::in);

  for (int i = 0; i != 4; ++i)
    test_refpoint3f_eq(rps1.at(i), rps2.at(i));
}
