#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"
#include "linestring.hpp"

using namespace ns_geo;

void foo_reftriangle3()
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
    auto tri = set.createRefTriangle3(0, 1, 2);
    std::cout << tri << std::endl;
    std::cout << tri.area() << std::endl;
    std::cout << tri.perimeter() << std::endl;
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
    ::foo_reftriangle3();
    return 0;
}
