#pragma once

/**
 * \brief the details
 *       [1] class type
 *              0. Polygon<_Ty>
 *              1. RefPolygon<_Ty>
 * 
 *       [2] methods for Polygon
 *              0. perimeter
 *              2. operator "<<" for Polygon<_Ty>
 *              2. operator "<<" for RefPolygon<_Ty>
 */

#include "point.hpp"

namespace ns_geo
{
#pragma region Polygon
    template <typename _Ty>
    class Polygon;
    using Polygond = Polygon<double>;
    using Polygonf = Polygon<float>;
    using Polygoni = Polygon<int>;

    template <typename _Ty>
    class Polygon : public PointSet2<_Ty>
    {
    public:
        using value_type = _Ty;
        using pointset_type = PointSet2<value_type>;
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
#pragma endregion

#pragma region RefPolgon

    using RefPolygond = RefPolygon<double>;
    using RefPolygonf = RefPolygon<float>;
    using RefPolygoni = RefPolygon<int>;

    template <typename _Ty>
    class RefPolygon : public std::vector<uint>
    {
    public:
        using value_type = _Ty;
        using refpoint_type = RefPoint2<value_type>;
        using pointidset_type = std::vector<uint>;
        using refpointset_type = RefPointSet2<value_type>;

    public:
        friend class RefPointSet2<value_type>;

    private:
        const refpointset_type *_rps;

    protected:
        RefPolygon(const std::initializer_list<uint> &pidls, const refpointset_type *rps)
            : pointidset_type(pidls), _rps(rps) {}

    public:
        RefPolygon() = delete;

        const refpointset_type *refPointSet() const { return this->_rps; };

        float perimeter() const
        {
            float len = 0.0;
            int i = 0;
            for (auto iter = this->cbegin(); iter != --this->cend();)
            {
                auto curPoint = _rps->at(*iter);
                auto nextPoint = _rps->at(*(++iter));
                len += distance(curPoint, nextPoint);
            }
            len += distance(_rps->at(this->front()),
                            _rps->at(this->back()));
            return len;
        }
    };

    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const RefPolygon<_Ty> &polygon)
    {
        auto rps = polygon.refPointSet();
        os << '{';
        for (auto iter = polygon.cbegin(); iter != --polygon.cend(); ++iter)
        {
            auto &p = rps->at(*iter);
            os << p.id() << ": [" << p.x() << ", " << p.y() << ']' << ", ";
        }
        auto &p = rps->at(polygon.back());
        os << p.id() << ": [" << p.x() << ", " << p.y() << "]}";
        return os;
    }
#pragma endregion
} // namespace ns_geo
