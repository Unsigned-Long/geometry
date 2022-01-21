#pragma once

#include "helper.h"
#include "../../include/utility.hpp"
#include "../../include/point.hpp"
#include "../../include/line.hpp"

TEST_F(TestPointSet, utility_2DIME)
{
    auto p1 = _ps2f->at(0);
    auto p2 = _ps2f->at(1);
    auto line = ns_geo::Line2f(p1, p2);
    auto st = ns_geo::stride(p1, p2);

    EXPECT_FLOAT_EQ(st[0], 1.0f);
    EXPECT_FLOAT_EQ(st[1], -1.0f);

    EXPECT_FLOAT_EQ(ns_geo::distance(p1, p2), ns_geo::distance(p2, p1));
    EXPECT_FLOAT_EQ(ns_geo::distance(p1, p2), std::sqrt(2.0f));
    EXPECT_FLOAT_EQ(ns_geo::distance(p1, p2, 2.0f), std::sqrt(2.0f));
    EXPECT_FLOAT_EQ(ns_geo::distance(p1, p2, 1.0f), 0.0f);

    EXPECT_FLOAT_EQ(ns_geo::distance({0.0f, 0.0f}, line), std::sqrt(2.0f));
}

TEST(utility, vector)
{
    std::array<float, 3> vec1 = {1.0f, 3.0f, -5.0f};
    std::array<float, 3> vec2 = {4.0f, -2.0f, -1.0f};

    auto res = ns_geo::dot(vec1, vec2);

    EXPECT_FLOAT_EQ(res, 3.0f);

    std::array<float, 3> vec3 = {1.0f, 3.0f, -4.0f};
    std::array<float, 3> vec4 = {2.0f, -5.0f, 8.0f};
    auto res2 = ns_geo::cross(vec3, vec4);

    EXPECT_FLOAT_EQ(res2[0], 4.0f);
    EXPECT_FLOAT_EQ(res2[1], -16.0f);
    EXPECT_FLOAT_EQ(res2[2], -11.0f);

    std::array<float, 3> vec5 = {3.0f, 4.0f, 0.0f};
    auto nor = ns_geo::norm(vec5);

    EXPECT_FLOAT_EQ(nor, 5.0f);
    auto vec6 = ns_geo::normalized(vec5);
    EXPECT_FLOAT_EQ(ns_geo::norm(vec6), 1.0f);

    ns_geo::normalize(vec5);
    EXPECT_FLOAT_EQ(ns_geo::norm(vec5), 1.0f);
}

TEST_F(TestPointSet, utility_3DIME)
{
    auto p1 = _ps3f->at(0);
    auto p2 = _ps3f->at(1);
    auto line = ns_geo::Line3f(p1, p2);
    auto st = ns_geo::stride(p1, p2);

    EXPECT_FLOAT_EQ(st[0], 1.0f);
    EXPECT_FLOAT_EQ(st[1], -1.0f);
    EXPECT_FLOAT_EQ(st[2], 0.0f);

    EXPECT_FLOAT_EQ(ns_geo::distance(p1, p2), ns_geo::distance(p2, p1));
    EXPECT_FLOAT_EQ(ns_geo::distance(p1, p2), std::sqrt(2.0f));
    EXPECT_FLOAT_EQ(ns_geo::distance(p1, p2, 2.0f), std::sqrt(2.0f));
    EXPECT_FLOAT_EQ(ns_geo::distance(p1, p2, 1.0f), 0.0f);

    EXPECT_FLOAT_EQ(ns_geo::distance({0.0f, 0.0f, 0.0f}, line), std::sqrt(3.0f));
}

TEST_F(TestPointSet, utility_RHandRule)
{
    auto p1 = _ps2f->at(0);
    auto p2 = _ps2f->at(1);
    auto p3 = _ps3f->at(0);
    auto p4 = _ps3f->at(1);

    auto line2f = ns_geo::Line2f(p1, p2);

    EXPECT_FLOAT_EQ(ns_geo::RHandRule::azimuth(p1, p2), M_PI * 0.75f);
    EXPECT_FLOAT_EQ(ns_geo::RHandRule::azimuth(p3, p4), M_PI * 0.75f);

    EXPECT_EQ(ns_geo::RHandRule::palleft({0.0f, 0.0f}, line2f), false);
    EXPECT_EQ(ns_geo::RHandRule::palright({0.0f, 0.0f}, line2f), true);

    test_point2f_eq(ns_geo::RHandRule::polarCoorMap(p1, std::sqrt(2.0f), M_PI_4), {1.0f, 3.0f});
    test_point3f_eq(ns_geo::RHandRule::polarCoorMap(p3, std::sqrt(2.0f), M_PI_4, M_PI_2), {1.0f, 3.0f, 1.0f});
}

TEST_F(TestPointSet, utility_LHandRule)
{
    auto p1 = _ps2f->at(0);
    auto p2 = _ps2f->at(1);
    auto p3 = _ps3f->at(0);
    auto p4 = _ps3f->at(1);

    auto line2f = ns_geo::Line2f(p1, p2);

    EXPECT_FLOAT_EQ(ns_geo::LHandRule::azimuth(p1, p2), M_PI * 1.75f);
    EXPECT_FLOAT_EQ(ns_geo::LHandRule::azimuth(p3, p4), M_PI * 1.75f);

    EXPECT_EQ(ns_geo::LHandRule::palleft({0.0f, 0.0f}, line2f), true);
    EXPECT_EQ(ns_geo::LHandRule::palright({0.0f, 0.0f}, line2f), false);

    test_point2f_eq(ns_geo::LHandRule::polarCoorMap(p1, std::sqrt(2.0f), M_PI_4), {1.0f, 3.0f});
    test_point3f_eq(ns_geo::LHandRule::polarCoorMap(p3, std::sqrt(2.0f), M_PI_4, M_PI_2), {1.0f, 3.0f, 1.0f});
}
