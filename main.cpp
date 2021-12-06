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

void foo_stride()
{
    Point2i p1(0, 0);
    Point2i p2(5, 8);
    auto s1 = stride(p1, p2);
    std::cout << Point2i(s1) << std::endl;
    Point3d p3(0.0, 0.0, 0.0);
    Point3d p4(1.5, 8.2, 9.8);
    auto s2 = stride(p3, p4);
    std::cout << Point3d(s2) << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    ::foo_stride();
    return 0;
}
