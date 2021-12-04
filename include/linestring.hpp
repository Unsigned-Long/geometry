#pragma once

/**
 * \brief the details
 *       [1] class type
 *              0. LineString<_PointType>
 * 
 *       [2] methods for LineString
 *              0. length
 *              2. operator "<<" for LineString<_PointType>
 */

#include "point.hpp"

namespace ns_geo
{
#pragma region LineString2
    template <typename _Ty>
    class LineString2;
    using LineString2d = LineString2<double>;
    using LineString2f = LineString2<float>;
    using LineString2i = LineString2<int>;

    template <typename _Ty>
    class LineString2 : public PointSet2<_Ty>
    {
    public:
        using value_type = _Ty;
        using pointset_type = PointSet2<value_type>;
        using pointset_type::pointset_type;

        float length() const
        {
            float len = 0.0;
            for (auto iter = this->cbegin(); iter != --this->cend();)
                len += distance(*iter, *(iter++));
            return len;
        }
    };
    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const LineString2<_Ty> &ls)
    {
        os << '{';
        for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter)
            os << *iter << ", ";
        os << ls.back() << '}';
        return os;
    }
#pragma endregion

#pragma region linestring3
    template <typename _Ty>
    class LineString3;
    using LineString3d = LineString3<double>;
    using LineString3f = LineString3<float>;
    using LineString3i = LineString3<int>;

    template <typename _Ty>
    class LineString3 : public PointSet3<_Ty>
    {
    public:
        using value_type = _Ty;
        using pointset_type = PointSet3<value_type>;
        using pointset_type::pointset_type;

        float length() const
        {
            float len = 0.0;
            for (auto iter = this->cbegin(); iter != --this->cend();)
                len += distance(*iter, *(iter++));
            return len;
        }
    };
    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const LineString3<_Ty> &ls)
    {
        os << '{';
        for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter)
            os << *iter << ", ";
        os << ls.back() << '}';
        return os;
    }
#pragma endregion

} // namespace ns_geo
