#pragma once

/**
 * @file rectangle.hpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2021-12-06
 * @copyright Copyright (c) 2021
 * 
 * @brief the details
 *        [1] class type
 *              0. Rectangle<_Ty>
 *              1. RefRectangle<_Ty>
 * 
 *        [2] methods for Line
 *              0. area
 *              1. perimeter
 *              2. operator "<<" for Rectangle<_Ty>
 *              3. operator "<<" for RefRectangle<_Ty>
 */

#include "point.hpp"

namespace ns_geo
{
#pragma region Rectangle
    template <typename _Ty>
    class Rectangle;
    /**
     * \brief some Commonly used Rectangle types
     */
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
        using point_type = ns_geo::Point2<value_type>;
        using ary_type = std::array<point_type, 2>;

    private:
        // top left point
        point_type _tplp;
        // lower right point
        point_type _lwrp;

    public:
        /**
         * \brief constructors
         */
        Rectangle() = default;
        Rectangle(const point_type &topLeft, const point_type &lowerRight)
            : _tplp(topLeft), _lwrp(lowerRight) {}
        Rectangle(const point_type points[2])
            : _tplp(points[0]), _lwrp(points[1]) {}
        Rectangle(const ary_type &points)
            : _tplp(points[0]), _lwrp(points[1]) {}
        Rectangle(value_type tlx, value_type tly, value_type lrx, value_type lry)
            : _tplp(tlx, tly), _lwrp(lrx, lry) {}

        ary_type points() const { return ary_type{this->_tplp, this->_lwrp}; }

        const point_type &topLeft() const { return this->_tplp; }

        point_type &topLeft() { return this->_tplp; }

        const point_type &lowerRight() const { return this->_lwrp; }

        point_type &lowerRight() { return this->_lwrp; }

        float area() const { return std::abs(this->_tplp.x() - this->_lwrp.x()) * std::abs(this->_tplp.y() - this->_lwrp.y()); }

        float perimeter() const
        {
            return 2.0 * (std::abs(this->_tplp.x() - this->_lwrp.x()) + std::abs(this->_tplp.y() - this->_lwrp.y()));
        }
    };
    /**
     * \brief overload operator "<<" for Rectangle
     */
    template <typename _Ty = float>
    std::ostream &operator<<(std::ostream &os, const Rectangle<_Ty> &rect)
    {
        os << '{';
        os << rect.topLeft() << ", ";
        os << rect.lowerRight() << '}';
        return os;
    }
#pragma endregion

#pragma region RefRectangle
    /**
     * \brief some Commonly used RefRectangle types
     */
    using RefRectangled = RefRectangle<double>;
    using RefRectanglef = RefRectangle<float>;
    using RefRectanglei = RefRectangle<int>;

    template <typename _Ty = float>
    class RefRectangle
    {
    public:
        using value_type = _Ty;
        using id_type = uint;
        using refpoint_type = ns_geo::RefPoint2<value_type>;
        using refpointset_type = RefPointSet2<value_type>;
        using ary_type = std::array<refpoint_type, 2>;

    public:
        friend class RefPointSet2<value_type>;

    private:
        // top left point's id
        id_type _tplpid;
        // lower right point's id
        id_type _lwrpid;
        // thr reference point set's pointer
        const refpointset_type *_rps;

    protected:
        /**
         * \brief constructors
         */
        RefRectangle(id_type topLeftID, id_type lowerRightID, const refpointset_type *refpointset)
            : _tplpid(topLeftID), _lwrpid(lowerRightID), _rps(refpointset) {}

        RefRectangle() = delete;

    public:
        const refpointset_type *refPointSet() const { return this->_rps; };

        ary_type refPoints() const { return ary_type{_rps->at(this->_tplpid), _rps->at(this->_lwrpid)}; }

        const refpoint_type &topLeft() const { return _rps->at(this->_tplpid); }

        refpoint_type &topLeft() { return _rps->at(this->_tplpid); }

        const refpoint_type &lowerRight() const { return _rps->at(this->_lwrpid); }

        refpoint_type &lowerRight() { return _rps->at(this->_lwrpid); }

        float area() const
        {
            return std::abs(this->topLeft().x() - this->lowerRight().x()) *
                   std::abs(this->topLeft().y() - this->lowerRight().y());
        }

        float perimeter() const
        {
            return 2.0 * (std::abs(this->topLeft().x() - this->lowerRight().x()) +
                          std::abs(this->topLeft().y() - this->lowerRight().y()));
        }
    };
    /**
     * \brief overload operator "<<" for RefRectangle
     */
    template <typename _Ty = float>
    std::ostream &operator<<(std::ostream &os, const RefRectangle<_Ty> &rect)
    {
        auto p1 = rect.topLeft();
        auto p2 = rect.lowerRight();
        os << '{';
        os << p1.id() << ": [" << p1.x() << ", " << p1.y() << ']' << ", ";
        os << p2.id() << ": [" << p2.x() << ", " << p2.y() << "]}";
        return os;
    }
#pragma endregion
} // namespace ns_geo
