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
 *              3. operator "<<" for RefPolygon<_Ty>
 */

#include "point.hpp"

namespace ns_geo
{
#pragma region Polygon
    template <typename _Ty>
    class Polygon;
    /**
     * \brief some Commonly used Polygon types
     */
    using Polygond = Polygon<double>;
    using Polygonf = Polygon<float>;
    using Polygoni = Polygon<int>;

    template <typename _Ty>
    class Polygon : public PointSet2<_Ty>
    {
    public:
        using value_type = _Ty;
        using pointset_type = PointSet2<value_type>;
        /**
         * \brief using pointset_type's constructors
         */
        using pointset_type::pointset_type;

        float perimeter() const
        {
            float len = 0.0;
            for (auto iter = this->cbegin(); iter != --this->cend();)
                len += distance(*iter, *(iter++));
            len += distance(this->front(), this->back());
            return len;
        }

        float area() const
        {
            float S = 0.0;
            for (int i = 0; i != this->size() - 1; ++i)
            {
                auto &pi = this->at(i);
                auto &pii = this->at(i + 1);
                S += (pi.x() * pii.y() - pii.x() * pi.y());
            }
            S = 0.5 * std::abs(S);
            return S;
        }
    };
    /**
     * \brief overload operator "<<" for Polygon
     */
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

#pragma region RefPolygon
    /**
     * \brief some Commonly used RefPolygon types
     */
    using RefPolygond = RefPolygon<double>;
    using RefPolygonf = RefPolygon<float>;
    using RefPolygoni = RefPolygon<int>;

    template <typename _Ty>
    class RefPolygon : public std::vector<uint>
    {
    public:
        using value_type = _Ty;
        using id_type = uint;
        using refpoint_type = RefPoint2<value_type>;
        using pointidset_type = std::vector<id_type>;
        using refpointset_type = RefPointSet2<value_type>;

    public:
        friend class RefPointSet2<value_type>;

    private:
        const refpointset_type *_rps;

    protected:
        /**
         * \brief constructors
         */
        RefPolygon(const std::initializer_list<id_type> &pidls, const refpointset_type *rps)
            : pointidset_type(pidls), _rps(rps) {}

        RefPolygon() = delete;

    public:
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
    /**
     * \brief overload operator "<<" for RefPolygon
     */
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
