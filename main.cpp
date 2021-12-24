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
#include <memory>

using namespace ns_geo;

void foo()
{
    Point2f p(0.0, 0.0);
    std::cout << (p.type() == GeometryType::POINT2D) << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    ::foo();
    return 0;
}
