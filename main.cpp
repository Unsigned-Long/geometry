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
#include <random>
#include <fstream>

using namespace ns_geo;

void foo_kdtreeNearestKSearch()
{
    RefPointSet2f ps;
    ps.insert({0, {2, 3}});
    ps.insert({1, {5, 4}});
    ps.insert({2, {9, 6}});
    ps.insert({3, {4, 7}});
    ps.insert({4, {8, 1}});
    ps.insert({5, {7, 2}});
    RefKdTree2f kdtree(ps);
    kdtree.printKdTree();
    std::vector<RefPoint2f> sps;
    std::vector<float> dis;
    kdtree.nearestKSearch({2, 4.5}, 1, sps, dis);
    std::cout << sps.front() << ' ' << dis.front() << std::endl;
}

int main(int argc, char *argv[])
{
    ::foo_kdtreeNearestKSearch();
    return 0;
}
