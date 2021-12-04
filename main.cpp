#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"
#include "linestring.hpp"

using namespace ns_geo;

void foo()
{
    std::cout << RefPointSet3f({{0, {0, -10.0, 0.0, -1.0}},
                                {10, {10, 50.0, 10.0, 9.0}},
                                {22, {22, 1.0, -4.0, -4.0}},
                                {45, {45, 2.0, -5.0, -7.0}}})
                     .createRefTriangle3(10, 22, 45)
                     .area()
              << std::endl;
    return;
}
int main(int argc, char *argv[])
{
    ::foo();
    return 0;
}
