#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"
#include "linestring.hpp"

using namespace ns_geo;

void foo_refline2()
{
    double ary2[2] = {2, 3};
    RefPoint2d p1(0, RefPoint2d::ary_type{0, 0});
    RefPoint2d p2(1, ary2);
    RefPoint2d p3(2, RefPoint2d::ary_type{0, 0});
    RefPoint2d p4(4, ary2);
    RefPointSet2d set;
    set.insert(p2);
    set.insert(p4);
    set.insert(p3);
    set.insert(p1);
    for (const auto &refp : set)
        std::cout << refp.second << std::endl;
    auto refline = set.createRefLine2(0, 1);
    std::cout << refline << std::endl;
    std::cout << refline.length() << std::endl;
}

void foo_refline3()
{
    RefPoint3d p1(0, RefPoint3d::ary_type{0, 0, 0});
    RefPoint3d p2(1, RefPoint3d::ary_type{0, 1, 0});
    RefPoint3d p3(2, RefPoint3d::ary_type{0, 0, 1});
    RefPoint3d p4(4, RefPoint3d::ary_type{1, 0, 0});
    RefPointSet3d set;
    set.insert(p2);
    set.insert(p4);
    set.insert(p3);
    set.insert(p1);
    for (const auto &refp : set)
        std::cout << refp.second << std::endl;
    auto refline = set.createRefLine3(0, 1);
    std::cout << refline << std::endl;
    std::cout << refline.length() << std::endl;
    auto ary = refline.points();
}

int main(int argc, char *argv[])
{
    ::foo_refline2();
    ::foo_refline3();
    return 0;
}
