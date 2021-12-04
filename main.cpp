#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"
#include "linestring.hpp"

using namespace ns_geo;

void foo_point3()
{
    Point3f p1(0.6, 0.4, 1.1);
    Point3f p2(1.9, 2.7, 2.3);
    Point3f p3(0.6, 0.4, 3.5);
    Point3f p4(1.9, 2.7, 4.6);
    PointSet3f ps = {p1, p2, p3, p4};
    try
    {
        // distance between tow points
        std::cout << distance(p1, p2) << std::endl;
        // write and read point data
        // way one.
        // default write mode : std::ios::out | std::ios::binary
        ps.write("../output/point3.bin");
        ps.clear();
        // default read mode : std::ios::in | std::ios::binary
        ps.read("../output/point3.bin");

        // way two.
        // write mode : std::ios::out
        ps.write("../output/point3.txt", std::ios::out);
        ps.clear();
        // read mode : std::ios::in
        ps.read("../output/point3.txt", std::ios::in);
        // print points
        for (const auto &elem : ps)
        {
            std::cout << elem << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return;
}
int main(int argc, char *argv[])
{
    /** output
     * {1: [0, 1, 0]}
     * {4: [1, 0, 0]}
     * {2: [0, 0, 1]}
     * {0: [0, 0, 0]}
     */
    ::foo_point3();
    return 0;
}
