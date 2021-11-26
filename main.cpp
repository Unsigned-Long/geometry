#include "point.hpp"
#include "triangle.hpp"
#include <list>

using namespace ns_geo;

void foo_point2()
{
    Point2f p1(0.6, 0.4);
    Point2f p2(1.9, 2.7);
    Point2f p3(0.6, 0.4);
    Point2f p4(1.9, 2.7);
    std::list<Point2f> ls = {p1, p2, p3, p4};
    try
    {
        // distance between tow points
        std::cout << distance(p1, p2) << std::endl;
        // write and read point data
        // way one.
        // default write mode : std::ios::out | std::ios::binary
        writePoints2(ls, "../output/point2.bin");
        ls.clear();
        // default read mode : std::ios::in | std::ios::binary
        readPoints2(ls, "../output/point2.bin");
        // way two.
        // write mode : std::ios::out
        writePoints2(ls, "../output/point2.txt", std::ios::out);
        ls.clear();
        // read mode : std::ios::in
        readPoints2(ls, "../output/point2.txt", std::ios::in);
        // print points
        for (const auto &elem : ls)
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

void foo_point3()
{
    Point3f p1(0.6, 0.4, 1.1);
    Point3f p2(1.9, 2.7, 2.3);
    Point3f p3(0.6, 0.4, 3.5);
    Point3f p4(1.9, 2.7, 4.6);
    std::list<Point3f> ls = {p1, p2, p3, p4};
    try
    {
        // distance between tow points
        std::cout << distance(p1, p2) << std::endl;
        // write and read point data
        // way one.
        // default write mode : std::ios::out | std::ios::binary
        writePoints3(ls, "../output/point3.bin");
        ls.clear();
        // default read mode : std::ios::in | std::ios::binary
        readPoints3(ls, "../output/point3.bin");

        // way two.
        // write mode : std::ios::out
        writePoints3(ls, "../output/point3.txt", std::ios::out);
        ls.clear();
        // read mode : std::ios::in
        readPoints3(ls, "../output/point3.txt", std::ios::in);
        // print points
        for (const auto &elem : ls)
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

void foo_ponitCast_test()
{
    Point3f p(1, 2, 6);
    Point2f p2(2, 6);
    auto ary = static_cast<Point3f::ary_type>(p);
    auto ary2 = static_cast<Point2f::ary_type>(p2);

    std::cout << ary[0] << ',' << ary[1] << ',' << ary[2] << std::endl;
    std::cout << ary2[0] << ',' << ary2[1] << std::endl;

    std::cout << Point3f(ary) << std::endl;
    std::cout << Point2f(ary2) << std::endl;

    return;
}

void foo_triangle2()
{
    // construct the triangle-2d
    ns_geo::Point2<double> points[3] = {
        Point2d(0, 0),
        Point2d(2, 2),
        Point2d(2, 0)};
    ns_geo::Triangle2d tri(points);
    tri = ns_geo::Triangle2d(points[0], points[1], points[2]);
    tri = ns_geo::Triangle2d(Point2d(0, 0), Point2d(2, 2), Point2d(2, 0));
    // output
    std::cout << tri << std::endl;
    // calculate the area and perimeter
    std::cout << "area : " << tri.area() << std::endl;
    std::cout << "perimeter : " << tri.perimeter() << std::endl;
    return;
}

void foo_triangle3()
{
    // construct the triangle-3d
    ns_geo::Point3<double> points[3] = {
        Point3d(0, 0, 0),
        Point3d(2, 2, 2),
        Point3d(2, 0, 0)};
    ns_geo::Triangle3d tri(points);
    tri = ns_geo::Triangle3d(points[0], points[1], points[2]);
    tri = ns_geo::Triangle3d(Point3d(0, 0, 0), Point3d(2, 2, 2), Point3d(2, 0, 0));
    // output
    std::cout << tri << std::endl;
    // calculate the area and perimeter
    std::cout << "area : " << tri.area() << std::endl;
    std::cout << "perimeter : " << tri.perimeter() << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    ::foo_triangle2();
    ::foo_triangle3();
    return 0;
}
