#pragma once

#include "helper.h"
#include "../../include/linestring.hpp"

TEST_F(TestPointSet, LineString2f_normalTesting)
{
    auto ls = ns_geo::LineString2f({_ps2f->at(0),
                                    _ps2f->at(1),
                                    _ps2f->at(2)});

    EXPECT_EQ(ls.type(), ns_geo::GeometryType::LINESTRING2D);
    EXPECT_FLOAT_EQ(ls.length(), ns_geo::distance(ls[0], ls[1]) +
                                     ns_geo::distance(ls[1], ls[2]));
}

TEST_F(TestPointSet, LineString2f_typeTesting)
{
    testing::StaticAssertTypeEq<float, ns_geo::LineString2f::value_type>();
    testing::StaticAssertTypeEq<ns_geo::PointSet2f, ns_geo::LineString2f::pointset_type>();
    testing::StaticAssertTypeEq<ns_geo::LineString2f, ns_geo::LineString2f::self_type>();
}

TEST_F(TestPointSet, LineString3f_normalTesting)
{
    auto ls = ns_geo::LineString3f({_ps3f->at(0),
                                    _ps3f->at(1),
                                    _ps3f->at(2)});

    EXPECT_EQ(ls.type(), ns_geo::GeometryType::LINESTRING3D);
    EXPECT_FLOAT_EQ(ls.length(), ns_geo::distance(ls[0], ls[1]) +
                                     ns_geo::distance(ls[1], ls[2]));
}

TEST_F(TestPointSet, LineString3f_typeTesting)
{
    testing::StaticAssertTypeEq<float, ns_geo::LineString3f::value_type>();
    testing::StaticAssertTypeEq<ns_geo::PointSet3f, ns_geo::LineString3f::pointset_type>();
    testing::StaticAssertTypeEq<ns_geo::LineString3f, ns_geo::LineString3f::self_type>();
}

TEST_F(TestRefPointSet2f, RefLineString2f_normalTesting)
{
    auto rls = _rps->createRefLineString2({0, 1, 2});

    EXPECT_EQ(rls.type(), ns_geo::RefGeometryType::REFLINESTRING2D);
    EXPECT_EQ(_rps, rls.refPointSet());

    test_refpoint2f_eq(rls.indexAt(0), _rps->at(0));
    test_refpoint2f_eq(rls.idAt(0), _rps->at(0));

    auto ls = static_cast<ns_geo::LineString2f>(rls);

    test_point2f_eq(ls[0], _rps->at(0));
    test_point2f_eq(ls[1], _rps->at(1));
    test_point2f_eq(ls[2], _rps->at(2));

    auto ids = rls.pids();
    EXPECT_EQ(ids[0], 0);
    EXPECT_EQ(ids[1], 1);
    EXPECT_EQ(ids[2], 2);

    EXPECT_FLOAT_EQ(rls.length(), ns_geo::distance(ls[0], ls[1]) +
                                      ns_geo::distance(ls[1], ls[2]));
}

TEST_F(TestRefPointSet2f, RefLineString2f_typeTesting)
{
    testing::StaticAssertTypeEq<float, ns_geo::RefLineString2f::value_type>();
    testing::StaticAssertTypeEq<uint, ns_geo::RefLineString2f::id_type>();
    testing::StaticAssertTypeEq<ns_geo::RefPoint2f, ns_geo::RefLineString2f::refpoint_type>();
    testing::StaticAssertTypeEq<std::vector<uint>, ns_geo::RefLineString2f::pointidset_type>();
    testing::StaticAssertTypeEq<ns_geo::RefPointSet2f, ns_geo::RefLineString2f::refpointset_type>();
    testing::StaticAssertTypeEq<ns_geo::RefLineString2f, ns_geo::RefLineString2f::self_type>();
}

TEST_F(TestRefPointSet3f, RefLineString3f_normalTesting)
{
    auto rls = _rps->createRefLineString3({0, 1, 2});

    EXPECT_EQ(rls.type(), ns_geo::RefGeometryType::REFLINESTRING3D);
    EXPECT_EQ(_rps, rls.refPointSet());

    test_refpoint3f_eq(rls.indexAt(0), _rps->at(0));
    test_refpoint3f_eq(rls.idAt(0), _rps->at(0));

    auto ls = static_cast<ns_geo::LineString3f>(rls);

    test_point3f_eq(ls[0], _rps->at(0));
    test_point3f_eq(ls[1], _rps->at(1));
    test_point3f_eq(ls[2], _rps->at(2));

    auto ids = rls.pids();
    EXPECT_EQ(ids[0], 0);
    EXPECT_EQ(ids[1], 1);
    EXPECT_EQ(ids[2], 2);

    EXPECT_FLOAT_EQ(rls.length(), ns_geo::distance(ls[0], ls[1]) +
                                      ns_geo::distance(ls[1], ls[2]));
}

TEST_F(TestRefPointSet3f, RefLineString3f_typeTesting)
{
    testing::StaticAssertTypeEq<float, ns_geo::RefLineString3f::value_type>();
    testing::StaticAssertTypeEq<uint, ns_geo::RefLineString3f::id_type>();
    testing::StaticAssertTypeEq<ns_geo::RefPoint3f, ns_geo::RefLineString3f::refpoint_type>();
    testing::StaticAssertTypeEq<std::vector<uint>, ns_geo::RefLineString3f::pointidset_type>();
    testing::StaticAssertTypeEq<ns_geo::RefPointSet3f, ns_geo::RefLineString3f::refpointset_type>();
    testing::StaticAssertTypeEq<ns_geo::RefLineString3f, ns_geo::RefLineString3f::self_type>();
}