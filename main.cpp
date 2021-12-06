#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"
#include "linestring.hpp"

using namespace ns_geo;

void foo_polygon()
{
    RefPointSet2d rps;
    rps.insert({0, RefPoint2d::ary_type{0, 0}});
    rps.insert({1, RefPoint2d::ary_type{1, 0}});
    rps.insert({2, RefPoint2d::ary_type{1, 1}});
    rps.insert({4, RefPoint2d::ary_type{0, 1}});

    auto polygon = rps.createRefPolygon({2, 1, 0, 4});
    std::cout << polygon << std::endl;
    std::cout << "first refPoint : " << polygon.indexAt(0) << std::endl;
    std::cout << "first refPoint : " << polygon.idAt(2) << std::endl;
    std::cout << "perimeter : " << polygon.perimeter() << std::endl;
    std::cout << "area : " << polygon.area() << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    ::foo_polygon();
    return 0;
}
