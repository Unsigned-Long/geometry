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
    std::default_random_engine e;
    std::uniform_real_distribution<float> u(-100.0f, 100.0f);
    PointSet2f ps;
    std::fstream file1("../pyDrawer/kdtree/nearest1.csv", std::ios::out);
    std::fstream file2("../pyDrawer/kdtree/nearest2.csv", std::ios::out);
    for (int i = 0; i != 50; ++i)
    {
        ps.push_back({u(e), u(e)});
        file1 << ps.back().x() << ',' << ps.back().y() << std::endl;
    }
    KdTree2f kdtree(ps);
    std::vector<float> dis;
    std::vector<Point2f> sps;
    kdtree.nearestKSearch({0, 0}, 5, sps, dis);
    for (int i = 0; i != dis.size(); ++i)
        file2 << sps.at(i).x() << ',' << sps.at(i).y() << ',' << dis.at(i) << std::endl;
    return;
}


int main(int argc, char *argv[])
{
    ::foo_kdtreeNearestKSearch();
    return 0;
}
