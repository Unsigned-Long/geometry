#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"
#include "linestring.hpp"

using namespace ns_geo;

void foo_refpolygon()
{
    RefPoint2d p1(0, RefPoint2d::ary_type{0, 0});
    RefPoint2d p2(1, RefPoint2d::ary_type{1, 0});
    RefPoint2d p3(2, RefPoint2d::ary_type{1, 1});
    RefPoint2d p4(4, RefPoint2d::ary_type{0, 1});
    RefPointSet2d rps;
    rps.insert(p2);
    rps.insert(p4);
    rps.insert(p3);
    rps.insert(p1);
    auto polygon = rps.createRefPolygon({0, 1, 2, 4});
    std::cout << polygon << std::endl;
    std::cout << polygon.perimeter() << std::endl;
    polygon.insert(polygon.begin(), 1);
}

int main(int argc, char *argv[])
{
    /** output
     * {0: [0, 0, 0]}
     * {2: [0, 0, 1]}
     * {4: [1, 0, 0]}
     * {1: [0, 1, 0]}
     * {0: [0, 0, 0], 1: [0, 1, 0], 2: [0, 0, 1]}
     * 0.5
     * 3.41421
     */
    ::foo_refpolygon();
    return 0;
}
