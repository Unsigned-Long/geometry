#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"
#include "linestring.hpp"

using namespace ns_geo;

void foo_refrectangle()
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
    auto rect = set.createRefRectangle(0, 1);
    std::cout << rect << std::endl;
    std::cout << rect.area() << std::endl;
    std::cout << rect.perimeter() << std::endl;
}

int main(int argc, char *argv[])
{
    ::foo_refrectangle();
    return 0;
}
