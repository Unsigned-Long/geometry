/**
 * @file main.cpp
 * @author csl (3079625093@qq.com)
 * @brief main source code file
 * @version 0.1
 * @date 2021-12-06
 * @copyright Copyright (c) 2021
 */

#include "point.hpp"
#include "line.hpp"
#include "triangle.hpp"
#include "rectangle.hpp"

using namespace ns_geo;

void foo_polarCoor()
{
    Point3f p1(0.0, 0.0, 0.0);
    Point3f p2(10.0, 40.0, -2.0);
    std::cout << LHandRule::polarCoorMethod(p1, distance(p1, p2),
                                            LHandRule::azimuth(p1, p2),
                                            LHandRule::zenith(p1, p2))
              << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    ::foo_polarCoor();
    return 0;
}
