#pragma once
#include "point.hpp"

namespace ns_geo
{
    template <typename _Ty>
    class Polygon;
    using Polygond = Polygon<double>;
    using Polygonf = Polygon<float>;
    using Polygoni = Polygon<int>;

    template <typename _Ty>
    class Polygon : public PointSet<Point2<_Ty>>
    {
    public:
        using value_type = _Ty;
        using pointset_type = PointSet<Point2<_Ty>>;
        using pointset_type::pointset_type;
    };
    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const Polygon<_Ty> &polygon)
    {
        os << '{';
        for (auto iter = polygon.cbegin(); iter != --polygon.cend(); ++iter)
            os << *iter << ", ";
        os << polygon.back() << '}';
        return os;
    }
} // namespace ns_geo
