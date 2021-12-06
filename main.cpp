/**
 * @file main.cpp
 * @author csl (3079625093@qq.com)
 * @brief main source code file
 * @version 0.1
 * @date 2021-12-06
 * @copyright Copyright (c) 2021
 */

#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"
#include "linestring.hpp"

using namespace ns_geo;

void foo_distance()
{
    Point2d p1(1, 1);
    Point2d p2(2, 2);
    Line2d line({0, 0, 0, 1});
    std::cout << "p1 -> p2 : " << distance(p1, p2) << std::endl;
    std::cout << "p1 -> line : " << distance(p1, line) << std::endl;
    double ary2[2] = {2, 3};
    RefPointSet2d rps;
    rps.insert({0, RefPoint2d::ary_type{0, 0}});
    rps.insert({1, ary2});
    rps.insert({2, RefPoint2d::ary_type{0, 0}});
    rps.insert({4, ary2});
    auto refline = rps.createRefLine2(0, 1);
    std::cout << "p1 -> refline : " << distance(p1, Line2d(refline)) << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    ::foo_distance();
    return 0;
}
