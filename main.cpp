/**
 * @file main.cpp
 * @author csl (3079625093@qq.com)
 * @brief main source code file
 * @version 0.1
 * @date 2021-12-06
 * @copyright Copyright (c) 2021
 */

#include "point.hpp"

bool foo(const ns_geo::Point2f &p)
{
    return (ns_geo::distance(p, {2.0f, 2.0f}) > 1.5f) && (ns_geo::distance(p, {6.0f, 8.0f}) > 3.0f);
}

int main(int argc, char *argv[])
{
    auto ps2 = ns_geo::PointSet2f::randomGenerator(1000, 0, 10, 0, 10, foo);
    for (const auto &elem : ps2)
        std::cout << elem.x() << ',' << elem.y() << std::endl;
    return 0;
}
