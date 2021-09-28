#include "point.h"

using namespace ns_test;

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
        std::cout << ns_test::distance(p1, p2) << std::endl;
        // the azimuth from p3 to p4
        std::cout << ns_test::azimuth(p3, p4) << std::endl;
        // write and read point data
        // way one.
        // default write mode : std::ios::out | std::ios::binary
        ns_test::writePoints(ls, "../output/point2.bin");
        ls.clear();
        // default read mode : std::ios::in | std::ios::binary
        ns_test::readPoints(ls, "../output/point2.bin");
        // way two.
        // write mode : std::ios::out
        ns_test::writePoints(ls, "../output/point2.txt", std::ios::out);
        ls.clear();
        // read mode : std::ios::in
        ns_test::readPoints(ls, "../output/point2.txt", std::ios::in);
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
        std::cout << ns_test::distance(p1, p2) << std::endl;
        // write and read point data
        // way one.
        // default write mode : std::ios::out | std::ios::binary
        ns_test::writePoints(ls, "../output/point3.bin");
        ls.clear();
        // default read mode : std::ios::in | std::ios::binary
        ns_test::readPoints(ls, "../output/point3.bin");

        // way two.
        // write mode : std::ios::out
        ns_test::writePoints(ls, "../output/point3.txt", std::ios::out);
        ls.clear();
        // read mode : std::ios::in
        ns_test::readPoints(ls, "../output/point3.txt", std::ios::in);
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

void foo_cast_test()
{
    ns_test::Point3f p(1, 2, 6);
    ns_test::Point2f p2(2, 6);
    auto ary = static_cast<Point3f::ary_type>(p);
    auto ary2 = static_cast<Point2f::ary_type>(p2);

    std::cout << ary[0] << ',' << ary[1] << ',' << ary[2] << std::endl;
    std::cout << ary2[0] << ',' << ary2[1]  << std::endl;

    std::cout << Point3f(ary) << std::endl;
    std::cout << Point2f(ary2) << std::endl;

    return;
}

int main(int argc, char *argv[])
{
    // ::foo_point2();
    // ::foo_point3();
    ::foo_cast_test();
    return 0;
}
