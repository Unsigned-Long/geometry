#pragma once

#include "include/polygon.hpp"
#include "helper.h"

TEST_F(TestPointSet, polygonf_normalTestign) {
  auto polygon = ns_geo::Polygonf{_ps2f->at(0), _ps2f->at(1), _ps2f->at(5)};

  test_point2f_eq(polygon.at(0), _ps2f->at(0));
  test_point2f_eq(polygon.at(1), _ps2f->at(1));
  test_point2f_eq(polygon.at(2), _ps2f->at(5));

  EXPECT_FLOAT_EQ(polygon.area(), 1.5f);
  EXPECT_FLOAT_EQ(polygon.perimeter(),
                  std::sqrt(2.0f) + 3.0f + std::sqrt(5.0f));

  EXPECT_EQ(polygon.type(), ns_geo::GeoType::POLYGON);
}

TEST_F(TestPointSet, polygonf_typeTestign) {
  testing::StaticAssertTypeEq<float, ns_geo::Polygonf::value_type>();
  testing::StaticAssertTypeEq<ns_geo::PointSet2f,
                              ns_geo::Polygonf::pointset_type>();
  testing::StaticAssertTypeEq<ns_geo::Polygonf, ns_geo::Polygonf::self_type>();
}

TEST_F(TestRefPointSet2f, refpolygonf_normalTestign) {
  auto polygon = _rps->createRefPolygon({0, 1, 5});

  test_point2f_eq(polygon.idAt(0), _rps->at(0));
  test_point2f_eq(polygon.idAt(1), _rps->at(1));
  test_point2f_eq(polygon.idAt(5), _rps->at(5));

  test_point2f_eq(polygon.indexAt(0), _rps->at(0));
  test_point2f_eq(polygon.indexAt(1), _rps->at(1));
  test_point2f_eq(polygon.indexAt(2), _rps->at(5));

  auto ids = polygon.pids();
  EXPECT_EQ(ids[0], 0);
  EXPECT_EQ(ids[1], 1);
  EXPECT_EQ(ids[2], 5);

  EXPECT_FLOAT_EQ(polygon.area(), 1.5f);
  EXPECT_FLOAT_EQ(polygon.perimeter(),
                  std::sqrt(2.0f) + 3.0f + std::sqrt(5.0f));

  EXPECT_EQ(polygon.type(), ns_geo::GeoType::REF_POLYGON);
}

TEST_F(TestRefPointSet2f, refpolygonf_typeTestign) {
  testing::StaticAssertTypeEq<float, ns_geo::RefPolygonf::value_type>();
  testing::StaticAssertTypeEq<uint, ns_geo::RefPolygonf::id_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPoint2f,
                              ns_geo::RefPolygonf::refpoint_type>();
  testing::StaticAssertTypeEq<std::vector<uint>,
                              ns_geo::RefPolygonf::pointidset_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPointSet2f,
                              ns_geo::RefPolygonf::refpointset_type>();
  testing::StaticAssertTypeEq<ns_geo::RefPolygonf,
                              ns_geo::RefPolygonf::self_type>();
}
