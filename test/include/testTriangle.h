#pragma once

#include "../../include/triangle.hpp"
#include "helper.h"

TEST(Triangle2f, normalTesting) {
  ns_geo::Triangle2f tri({0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f});

  test_point2f_eq(tri.p1(), {0.0f, 0.0f});
  test_point2f_eq(tri.p2(), {0.0f, 1.0f});
  test_point2f_eq(tri.p3(), {1.0f, 0.0f});

  tri = ns_geo::Triangle2f(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

  test_point2f_eq(tri.p1(), {0.0f, 0.0f});
  test_point2f_eq(tri.p2(), {0.0f, 1.0f});
  test_point2f_eq(tri.p3(), {1.0f, 0.0f});

  auto s1 = tri.side12();
  test_point2f_eq(s1.p1(), tri.p1());
  test_point2f_eq(s1.p2(), tri.p2());
  auto s2 = tri.side13();
  test_point2f_eq(s2.p1(), tri.p1());
  test_point2f_eq(s2.p2(), tri.p3());
  auto s3 = tri.side23();
  test_point2f_eq(s3.p1(), tri.p2());
  test_point2f_eq(s3.p2(), tri.p3());

  auto points = tri.points();
  tri = ns_geo::Triangle2f(points);

  EXPECT_FLOAT_EQ(tri.area(), 0.5f);
  EXPECT_FLOAT_EQ(tri.perimeter(), 2.0f + std::sqrt(2.0f));

  auto cir = tri.circumCircle();
  auto ins = tri.inscribedCircle();

  test_point2f_eq(cir.first, {0.5f, 0.5f});
  EXPECT_FLOAT_EQ(cir.second, 0.5f * std::sqrt(2.0f));

  test_point2f_eq(ins.first,
                  {(0.5f * std::sqrt(2.0f)) / (1.0f + std::sqrt(2.0f)),
                   (0.5f * std::sqrt(2.0f)) / (1.0f + std::sqrt(2.0f))});
  EXPECT_FLOAT_EQ(ins.second,
                  (0.5f * std::sqrt(2.0f)) / (1.0f + std::sqrt(2.0f)));

  EXPECT_EQ(tri.type(), ns_geo::GeoType::TRIANGLE2D);
}

TEST(Triangle2f, typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::Triangle2f::value_type>();
  testing::StaticAssertTypeEq<ns_geo::Point2f,
                              ns_geo::Triangle2f::point_type>();
  testing::StaticAssertTypeEq<std::array<ns_geo::Point2f, 3>,
                              ns_geo::Triangle2f::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::Triangle2f,
                              ns_geo::Triangle2f::self_type>();
}

TEST(Triangle3f, normalTesting) {
  ns_geo::Triangle3f tri({0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f},
                         {1.0f, 0.0f, 1.0f});

  test_point3f_eq(tri.p1(), {0.0f, 0.0f, 1.0f});
  test_point3f_eq(tri.p2(), {0.0f, 1.0f, 1.0f});
  test_point3f_eq(tri.p3(), {1.0f, 0.0f, 1.0f});

  tri =
      ns_geo::Triangle3f(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);

  test_point3f_eq(tri.p1(), {0.0f, 0.0f, 1.0f});
  test_point3f_eq(tri.p2(), {0.0f, 1.0f, 1.0f});
  test_point3f_eq(tri.p3(), {1.0f, 0.0f, 1.0f});

  auto s1 = tri.side12();
  test_point3f_eq(s1.p1(), tri.p1());
  test_point3f_eq(s1.p2(), tri.p2());
  auto s2 = tri.side13();
  test_point3f_eq(s2.p1(), tri.p1());
  test_point3f_eq(s2.p2(), tri.p3());
  auto s3 = tri.side23();
  test_point3f_eq(s3.p1(), tri.p2());
  test_point3f_eq(s3.p2(), tri.p3());

  auto points = tri.points();
  tri = ns_geo::Triangle3f(points);

  EXPECT_FLOAT_EQ(tri.area(), 0.5f);
  EXPECT_FLOAT_EQ(tri.perimeter(), 2.0f + std::sqrt(2.0f));

  EXPECT_EQ(tri.type(), ns_geo::GeoType::TRIANGLE3D);
}

TEST(Triangle3f, typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::Triangle3f::value_type>();
  testing::StaticAssertTypeEq<ns_geo::Point3f,
                              ns_geo::Triangle3f::point_type>();
  testing::StaticAssertTypeEq<std::array<ns_geo::Point3f, 3>,
                              ns_geo::Triangle3f::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::Triangle3f,
                              ns_geo::Triangle3f::self_type>();
}

TEST_F(TestRefPointSet2f, refTriangle2f_normalTesting) {
  auto tri = _rps->createRefTriangle2(0, 1, 5);

  EXPECT_EQ(_rps, tri.refPointSet());

  auto t = static_cast<ns_geo::Triangle2f>(tri);

  test_point2f_eq(t.p1(), tri.p1());
  test_point2f_eq(t.p2(), tri.p2());
  test_point2f_eq(t.p3(), tri.p3());

  EXPECT_EQ(0, tri.pid1());
  EXPECT_EQ(1, tri.pid2());
  EXPECT_EQ(5, tri.pid3());

  auto s1 = tri.side12();
  test_refpoint2f_eq(s1.p1(), tri.p1());
  test_refpoint2f_eq(s1.p2(), tri.p2());
  auto s2 = tri.side13();
  test_refpoint2f_eq(s2.p1(), tri.p1());
  test_refpoint2f_eq(s2.p2(), tri.p3());
  auto s3 = tri.side23();
  test_refpoint2f_eq(s3.p1(), tri.p2());
  test_refpoint2f_eq(s3.p2(), tri.p3());

  auto ary = tri.refPoints();
  test_refpoint2f_eq(ary[0], tri.p1());
  test_refpoint2f_eq(ary[1], tri.p2());
  test_refpoint2f_eq(ary[2], tri.p3());

  EXPECT_EQ(tri.type(), ns_geo::GeoType::REFTRIANGLE2D);

  EXPECT_FLOAT_EQ(tri.area(), 1.5f);
  EXPECT_FLOAT_EQ(tri.perimeter(), std::sqrt(2.0f) + 3.0f + std::sqrt(5.0f));
}

TEST_F(TestRefPointSet2f, refTriangle2f_typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::RefTriangle2f::value_type>();
  testing::StaticAssertTypeEq<uint, ns_geo::RefTriangle2f::id_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPoint2f,
                              ns_geo::RefTriangle2f::refpoint_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPointSet2f,
                              ns_geo::RefTriangle2f::refpointset_type>();
  testing::StaticAssertTypeEq<std::array<ns_geo::RefPoint2f, 3>,
                              ns_geo::RefTriangle2f::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::RefTriangle2f,
                              ns_geo::RefTriangle2f::self_type>();
}

TEST_F(TestRefPointSet3f, refTriangle3f_normalTesting) {
  auto tri = _rps->createRefTriangle3(0, 1, 5);

  EXPECT_EQ(_rps, tri.refPointSet());

  auto t = static_cast<ns_geo::Triangle3f>(tri);

  test_point3f_eq(t.p1(), tri.p1());
  test_point3f_eq(t.p2(), tri.p2());
  test_point3f_eq(t.p3(), tri.p3());

  EXPECT_EQ(0, tri.pid1());
  EXPECT_EQ(1, tri.pid2());
  EXPECT_EQ(5, tri.pid3());

  auto s1 = tri.side12();
  test_refpoint3f_eq(s1.p1(), tri.p1());
  test_refpoint3f_eq(s1.p2(), tri.p2());
  auto s2 = tri.side13();
  test_refpoint3f_eq(s2.p1(), tri.p1());
  test_refpoint3f_eq(s2.p2(), tri.p3());
  auto s3 = tri.side23();
  test_refpoint3f_eq(s3.p1(), tri.p2());
  test_refpoint3f_eq(s3.p2(), tri.p3());

  auto ary = tri.refPoints();
  test_refpoint3f_eq(ary[0], tri.p1());
  test_refpoint3f_eq(ary[1], tri.p2());
  test_refpoint3f_eq(ary[2], tri.p3());

  EXPECT_EQ(tri.type(), ns_geo::GeoType::REFTRIANGLE3D);

  EXPECT_FLOAT_EQ(tri.area(), 1.5f);
  EXPECT_FLOAT_EQ(tri.perimeter(), std::sqrt(2.0f) + 3.0f + std::sqrt(5.0f));
}

TEST_F(TestRefPointSet3f, refTriangle3f_typeTesting) {
  testing::StaticAssertTypeEq<float, ns_geo::RefTriangle3f::value_type>();
  testing::StaticAssertTypeEq<uint, ns_geo::RefTriangle3f::id_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPoint3f,
                              ns_geo::RefTriangle3f::refpoint_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPointSet3f,
                              ns_geo::RefTriangle3f::refpointset_type>();
  testing::StaticAssertTypeEq<std::array<ns_geo::RefPoint3f, 3>,
                              ns_geo::RefTriangle3f::ary_type>();
  testing::StaticAssertTypeEq<ns_geo::RefTriangle3f,
                              ns_geo::RefTriangle3f::self_type>();
}