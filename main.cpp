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

void foo_kdtree()
{
    std::default_random_engine e;
    std::uniform_real_distribution<float> u(-100.0, 100.0);
    std::fstream file1("../pyDrawer/kdtree/originPoints.csv", std::ios::out);
    std::fstream file2("../pyDrawer/kdtree/searchPoints.csv", std::ios::out);
    PointSet2f ps;
    for (int i = 0; i != 50; ++i)
    {
        ps.push_back({u(e), u(e)});
        file1 << ps.back().x() << ',' << ps.back().y() << std::endl;
    }
    KdTree2f Kdtree(ps);
    std::vector<float> dis;
    std::vector<Point2f> sps;
    Kdtree.radiusSearch({53, 25}, 65, sps, dis);
    for (int i = 0; i != dis.size(); ++i)
        file2 << sps.at(i).x() << ',' << sps.at(i).y() << ',' << dis.at(i) << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    ::foo_kdtree();
    return 0;
}
