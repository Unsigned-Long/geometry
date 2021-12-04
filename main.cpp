#include "point.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"
#include "linestring.hpp"

using namespace ns_geo;

void foo_refpointset2_write()
{
    RefPoint2d p1(0, RefPoint2d::ary_type{0, 0});
    RefPoint2d p2(1, RefPoint2d::ary_type{1, 0});
    RefPoint2d p3(2, RefPoint2d::ary_type{1, 1});
    RefPoint2d p4(4, RefPoint2d::ary_type{0, 1});
    RefPointSet2d rps;
    rps.insert(p2);
    rps.insert(p4);
    rps.insert(p3);
    rps.insert(p1);
    rps.write("../output/refpointset2.bin");
    rps.clear();
    rps.read("../output/refpointset2.bin");
    for (const auto &[id, refp] : rps)
        std::cout << refp << std::endl;
}
void foo_refpointset3_write()
{
    RefPoint3d p1(0, RefPoint3d::ary_type{0, 0, 0});
    RefPoint3d p2(1, RefPoint3d::ary_type{0, 1, 0});
    RefPoint3d p3(2, RefPoint3d::ary_type{0, 0, 1});
    RefPoint3d p4(4, RefPoint3d::ary_type{1, 0, 0});
    RefPointSet3d rps;
    rps.insert(p2);
    rps.insert(p4);
    rps.insert(p3);
    rps.insert(p1);
    rps.write("../output/refpointset3.bin");
    rps.clear();
    rps.read("../output/refpointset3.bin");
    for (const auto &[id, refp] : rps)
        std::cout << refp << std::endl;
}
int main(int argc, char *argv[])
{
    /** output
     * {1: [0, 1, 0]}
     * {4: [1, 0, 0]}
     * {2: [0, 0, 1]}
     * {0: [0, 0, 0]}
     */
    ::foo_refpointset2_write();
    ::foo_refpointset3_write();
    return 0;
}
