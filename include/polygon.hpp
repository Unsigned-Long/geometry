#pragma once

/**
 * \brief the details
 *       [1] class type
 *              0. Polygon<_Ty>
 *              1. Polygond
 *              2. Polygonf
 *              3. Polygoni
 * 
 *       [2] methods for Polygon
 *              0. perimeter
 *              2. operator "<<" for Polygon<_Ty>
 */

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

        float perimeter() const
        {
            float len = 0.0;
            for (auto iter = this->cbegin(); iter != --this->cend();)
                len += distance(*iter, *(iter++));
            len += distance(this->front(), this->back());
            return len;
        }
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
