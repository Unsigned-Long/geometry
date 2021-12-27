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
    for (float rad = 0.0; rad < 10 * M_PI; rad += 0.5)
    {
        auto pos = RHandRule::polarCoorMap(Point2f(), rad * rad * rad / 100.0, rad);
        std::cout << pos.x() << ',' << pos.y() << std::endl;
    }
    return;
}

int main(int argc, char *argv[])
{
    ::foo_polarCoor();
    return 0;
}
