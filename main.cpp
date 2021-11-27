#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include <list>

using namespace ns_geo;

void foo_line2()
{
    ns_geo::Line2d line(Point2d(0, 0), Point2d(2, 2));
    std::cout << line << std::endl;
    std::cout << "length : " << line.length() << std::endl;
    return;
}

void foo_line3()
{
    ns_geo::Line3d line(Point3d(0, 0, 0), Point3d(2, 2, 2));
    std::cout << line << std::endl;
    std::cout << "length : " << line.length() << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    ::foo_line2();
    ::foo_line3();
    return 0;
}
