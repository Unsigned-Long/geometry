#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include <list>
#include "rectangle.hpp"

using namespace ns_geo;

void foo_rectangle2()
{
    ns_geo::Rectangle2d rect(0, 4, 1, 0);
    std::cout << rect << std::endl;
    std::cout << "area : " << rect.area() << std::endl;
    return;
}

void foo_pointset()
{
    PointSet2f set;
    set.push_back(Point2f(1, 2));
    set.push_back(Point2f(2, 3));
    writePoints2(set, "../output/pointset.csv", std::ios::out);
    set.clear();
    readPoints2(set, "../output/pointset.csv", std::ios::in);
        for (const auto &point : set)
        std::cout << point << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    ::foo_pointset();
    return 0;
}
