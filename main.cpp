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
#include "kdtree.hpp"

using namespace ns_geo;

void foo_kdtree()
{
    PointSet3f ps({{3, 1, 4},
                   {2, 3, 7},
                   {2, 0, 3},
                   {2, 4, 5},
                   {1, 4, 4},
                   {0, 5, 7}});
    KdTree3<Point3f> kdtree(ps);
    kdtree.printKdTree();
    return;
}

int main(int argc, char *argv[])
{
    ::foo_kdtree();
    return 0;
}
