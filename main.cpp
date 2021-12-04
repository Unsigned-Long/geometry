#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"
#include "linestring.hpp"

using namespace ns_geo;

void foo_reflinestring2()
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
    auto ls = rps.createRefLineString2({0, 1, 2, 4});
    std::cout << ls << std::endl;
    std::cout << "length : " << ls.length() << std::endl;
}
void foo_reflinestring3()
{
    RefPoint3d p1(0, RefPoint3d::ary_type{0, 0, 0});
    RefPoint3d p2(1, RefPoint3d::ary_type{0, 1, 0});
    RefPoint3d p3(2, RefPoint3d::ary_type{0, 0, 1});
    RefPoint3d p4(4, RefPoint3d::ary_type{1, 0, 0});
    RefPointSet3d rps;
    rps.insert(p2);
    rps.insert(p4);
    rps.insert(p3);
    rps.insert(p1);
    auto ls = rps.createRefLineString3({0, 1, 2, 4});
    std::cout << ls << std::endl;
    std::cout << "length : " << ls.length() << std::endl;
}
int main(int argc, char *argv[])
{
    /** output
     * {0: [0, 0, 0], 1: [0, 1, 0], 2: [0, 0, 1], 4: [1, 0, 0]}
     * length : 3.82843
     */
    ::foo_reflinestring3();
    return 0;
}
