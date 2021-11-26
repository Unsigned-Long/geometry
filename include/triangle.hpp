#pragma once

#include "point.hpp"

namespace ns_geo
{
#pragma region triangle2
    template <typename _Ty>
    class Triangle2;
    using Triangle2d = Triangle2<double>;
    using Triangle2f = Triangle2<float>;
    using Triangle2i = Triangle2<int>;

    /**
     * \brief a sample template class to describe the 2-dime triangles
     */
    template <typename _Ty = float>
    class Triangle2
    {
    public:
        using value_type = _Ty;
        using point_type = ns_geo::Point2<_Ty>;

    private:
        point_type _p1;
        point_type _p2;
        point_type _p3;

    public:
        Triangle2() = default;
        Triangle2(const point_type &p1, const point_type &p2, const point_type &p3)
            : _p1(p1), _p2(p2), _p3(p3) {}
        Triangle2(const point_type points[3])
            : _p1(points[0]), _p2(points[1]), _p3(points[2]) {}

        const point_type &p1() const { return this->_p1; }
        point_type &p1() { return this->_p1; }

        const point_type &p2() const { return this->_p2; }
        point_type &p2() { return this->_p2; }

        const point_type &p3() const { return this->_p3; }
        point_type &p3() { return this->_p3; }

        std::array<point_type, 3> points() const { return std::array<point_type, 3>{this->_p1, this->p2, this->_p3}; }

        double area() const
        {
            double v12_x = _p2.x() - _p1.x();
            double v12_y = _p2.y() - _p1.y();
            double v13_x = _p3.x() - _p1.x();
            double v13_y = _p3.y() - _p1.y();
            return std::abs(v12_x * v13_y - v12_y * v13_x) * 0.5;
        }

        double perimeter() const
        {
            return ns_geo::distance(_p1, _p2) +
                   ns_geo::distance(_p1, _p3) +
                   ns_geo::distance(_p2, _p3);
        }
    };

    template <typename _Ty = float>
    std::ostream &operator<<(std::ostream &os, const Triangle2<_Ty> &tri)
    {
        os << '{';
        os << tri.p1() << ", ";
        os << tri.p2() << ", ";
        os << tri.p3() << '}';
        return os;
    }
#pragma endregion

#pragma region triangle3
    template <typename _Ty>
    class Triangle3;
    using Triangle3d = Triangle3<double>;
    using Triangle3f = Triangle3<float>;
    using Triangle3i = Triangle3<int>;

    /**
     * \brief a sample template class to describe the 3-dime triangles
     */
    template <typename _Ty = float>
    class Triangle3
    {
    public:
        using value_type = _Ty;
        using point_type = ns_geo::Point3<_Ty>;

    private:
        point_type _p1;
        point_type _p2;
        point_type _p3;

    public:
        Triangle3() = default;
        Triangle3(const point_type &p1, const point_type &p2, const point_type &p3)
            : _p1(p1), _p2(p2), _p3(p3) {}
        Triangle3(const point_type points[3])
            : _p1(points[0]), _p2(points[1]), _p3(points[2]) {}

        const point_type &p1() const { return this->_p1; }
        point_type &p1() { return this->_p1; }

        const point_type &p2() const { return this->_p2; }
        point_type &p2() { return this->_p2; }

        const point_type &p3() const { return this->_p3; }
        point_type &p3() { return this->_p3; }

        std::array<point_type, 3> points() const { return std::array<point_type, 3>{this->_p1, this->p2, this->_p3}; }

        double area() const
        {
            double v12_x = _p2.x() - _p1.x();
            double v12_y = _p2.y() - _p1.y();
            double v12_z = _p2.z() - _p1.z();
            double v13_x = _p3.x() - _p1.x();
            double v13_y = _p3.y() - _p1.y();
            double v13_z = _p3.z() - _p1.z();
            auto val1 = std::pow(v12_y * v13_z - v12_z * v13_y, 2);
            auto val2 = std::pow(v13_x * v12_z - v12_x * v13_z, 2);
            auto val3 = std::pow(v12_x * v13_y - v12_y * v13_x, 2);
            return std::sqrt(val1 + val2 + val3) * 0.5;
        }

        double perimeter() const
        {
            return ns_geo::distance(_p1, _p2) +
                   ns_geo::distance(_p1, _p3) +
                   ns_geo::distance(_p2, _p3);
        }
    };

    template <typename _Ty = float>
    std::ostream &operator<<(std::ostream &os, const Triangle3<_Ty> &tri)
    {
        os << '{';
        os << tri.p1() << ", ";
        os << tri.p2() << ", ";
        os << tri.p3() << '}';
        return os;
    }
#pragma endregion

} // namespace ns_geo
