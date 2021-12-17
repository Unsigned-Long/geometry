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

using namespace ns_geo;

void foo()
{
    Point2f p1(0.0, 0.0), p2(0.0, 1.0), p3(1.0, 0.0);
    auto p = Triangle2f(p1, p2, p3).circumCircle();
    std::cout << p.first << ',' << p.second << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    ::foo();
    return 0;
}
