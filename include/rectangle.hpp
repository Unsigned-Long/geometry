#pragma once

#include "point.hpp"

namespace ns_geo
{
    template <typename _Ty>
    class Rectangle;
    using Rectangled = Rectangle<double>;
    using Rectanglef = Rectangle<float>;
    using Rectanglei = Rectangle<int>;

    /**
     * \brief a sample template class to describe the 2-dime rectangles
     */
    template <typename _Ty = float>
    class Rectangle
    {
    public:
        using value_type = _Ty;
        using point_type = ns_geo::Point2<_Ty>;

    private:
        // top left point
        point_type _tplp;
        // lower right point
        point_type _lwrp;

    public:
        Rectangle() = default;
        Rectangle(const point_type &topLeft, const point_type &lowerRight)
            : _tplp(topLeft), _lwrp(lowerRight) {}
        Rectangle(const point_type points[2])
            : _tplp(points[0]), _lwrp(points[1]) {}
        Rectangle(const std::array<point_type, 2> &points)
            : _tplp(points[0]), _lwrp(points[1]) {}
        Rectangle(value_type tlx, value_type tly, value_type lrx, value_type lry)
            : _tplp(tlx, tly), _lwrp(lrx, lry) {}

        std::array<point_type, 2> points() const { return std::array<point_type, 2>{this->_tplp, this->_lwrp}; }

        const point_type &topLeft() const { return this->_tplp; }
        
        point_type &topLeft() { return this->_tplp; }

        const point_type &lowerRight() const { return this->_lwrp; }
        
        point_type &lowerRight() { return this->_lwrp; }

        float area() const { return std::abs(this->_tplp.x() - this->_lwrp.x()) * std::abs(this->_tplp.y() - this->_lwrp.y()); }

        float perimeter() const
        {
            return 2.0 * (ns_geo::distance(point_type(_tplp.x(), _lwrp.y()), _lwrp) +
                          ns_geo::distance(point_type(_tplp.x(), _lwrp.y()), _tplp));
        }
    };

    template <typename _Ty = float>
    std::ostream &operator<<(std::ostream &os, const Rectangle<_Ty> &rect)
    {
        os << '{';
        os << rect.topLeft() << ", ";
        os << rect.lowerRight() << '}';
        return os;
    }
} // namespace ns_geo
