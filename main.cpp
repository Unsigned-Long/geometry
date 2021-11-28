#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include "rectangle.hpp"

using namespace ns_geo;

void foo_azimuth()
{
    ns_geo::Point2f from(0, 0), to(-1, -2);
    std::cout << azimuthLHR(from, to) * 180.0 / M_PI << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    ::foo_azimuth();
    return 0;
}
