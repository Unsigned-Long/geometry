#pragma once
#include "point.hpp"

namespace ns_geo
{
#pragma region LineString
    template <typename _PointType>
    class LineString;
    using LineString2d = LineString<Point2d>;
    using LineString2f = LineString<Point2f>;
    using LineString2i = LineString<Point2i>;
    using LineString3d = LineString<Point3d>;
    using LineString3f = LineString<Point3f>;
    using LineString3i = LineString<Point3i>;

    template <typename _PointType>
    class LineString : public PointSet<_PointType>
    {
    public:
        using value_type = typename _PointType::value_type;
        using pointset_type = PointSet<_PointType>;
        using pointset_type::pointset_type;
        
        float length() const
        {
            float len = 0.0;
            for (auto iter = this->cbegin(); iter != --this->cend();)
                len += distance(*iter, *(iter++));
            return len;
        }
    };
    template <typename _PointType>
    std::ostream &operator<<(std::ostream &os, const LineString<_PointType> &ls)
    {
        os << '{';
        for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter)
            os << *iter << ", ";
        os << ls.back() << '}';
        return os;
    }
#pragma endregion

} // namespace ns_geo
