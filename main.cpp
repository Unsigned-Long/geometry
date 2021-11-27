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

int main(int argc, char *argv[])
{
    ::foo_rectangle2();
    return 0;
}
