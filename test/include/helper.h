#pragma once

/**
 * @file helper.h
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "gtest/gtest.h"
#include "../../include/point.hpp"

void test_point2f_eq(const ns_geo::Point2f &p1, const ns_geo::Point2f &p2)
{
    EXPECT_FLOAT_EQ(p1.x(), p2.x());
    EXPECT_FLOAT_EQ(p1.y(), p2.y());
    EXPECT_EQ(p1.type(), p2.type());
    return;
}

void test_point3f_eq(const ns_geo::Point3f &p1, const ns_geo::Point3f &p2)
{
    EXPECT_FLOAT_EQ(p1.x(), p2.x());
    EXPECT_FLOAT_EQ(p1.y(), p2.y());
    EXPECT_FLOAT_EQ(p1.z(), p2.z());
    EXPECT_EQ(p1.type(), p2.type());
    return;
}

void test_refpoint2f_eq(const ns_geo::RefPoint2f &p1, const ns_geo::RefPoint2f &p2)
{
    EXPECT_EQ(p1.id(), p2.id());
    EXPECT_FLOAT_EQ(p1.x(), p2.x());
    EXPECT_FLOAT_EQ(p1.y(), p2.y());
    EXPECT_EQ(p1.type(), p2.type());
    return;
}

void test_refpoint3f_eq(const ns_geo::RefPoint3f &p1, const ns_geo::RefPoint3f &p2)
{
    EXPECT_EQ(p1.id(), p2.id());
    EXPECT_FLOAT_EQ(p1.x(), p2.x());
    EXPECT_FLOAT_EQ(p1.y(), p2.y());
    EXPECT_FLOAT_EQ(p1.z(), p2.z());
    EXPECT_EQ(p1.type(), p2.type());
    return;
}