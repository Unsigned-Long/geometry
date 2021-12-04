#pragma once

/**
 * \brief the details
 *       [1] class type
 *              0. Triangle2<_Ty>, Triangle3<_Ty>
 *              1. RefTriangle2<_Ty>, RefTriangle3<_Ty>
 * 
 *       [2] methods for Line
 *              0. area
 *              1. perimeter
 *              2. operator "<<" for Triangle2<_Ty>, Triangle3<_Ty>
 *              3. operator "<<" for RefTriangle2<_Ty>, RefTriangle3<_Ty>
 */

#include "point.hpp"

namespace ns_geo
{
#pragma region Triangle2
    template <typename _Ty>
    class Triangle2;
    /**
     * \brief some Commonly used Triangle2 types
     */
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
        using point_type = ns_geo::Point2<value_type>;
        using ary_type = std::array<point_type, 3>;

    private:
        point_type _p1;
        point_type _p2;
        point_type _p3;

    public:
        /**
         * \brief constructors
         */
        Triangle2() = default;
        Triangle2(const point_type &p1, const point_type &p2, const point_type &p3)
            : _p1(p1), _p2(p2), _p3(p3) {}
        Triangle2(const point_type points[3])
            : _p1(points[0]), _p2(points[1]), _p3(points[2]) {}
        Triangle2(const ary_type &points)
            : _p1(points[0]), _p2(points[1]), _p3(points[2]) {}
        Triangle2(value_type p1x, value_type p1y,
                  value_type p2x, value_type p2y,
                  value_type p3x, value_type p3y)
            : _p1(p1x, p1y), _p2(p2x, p2y), _p3(p3x, p3y) {}

        const point_type &p1() const { return this->_p1; }
        point_type &p1() { return this->_p1; }

        const point_type &p2() const { return this->_p2; }
        point_type &p2() { return this->_p2; }

        const point_type &p3() const { return this->_p3; }
        point_type &p3() { return this->_p3; }

        ary_type points() const { return ary_type{this->_p1, this->_p2, this->_p3}; }

        float area() const
        {
            float v12_x = _p2.x() - _p1.x();
            float v12_y = _p2.y() - _p1.y();
            float v13_x = _p3.x() - _p1.x();
            float v13_y = _p3.y() - _p1.y();
            return std::abs(v12_x * v13_y - v12_y * v13_x) * 0.5;
        }

        float perimeter() const
        {
            return ns_geo::distance(_p1, _p2) +
                   ns_geo::distance(_p1, _p3) +
                   ns_geo::distance(_p2, _p3);
        }
    };
    /**
     * \brief overload operator "<<" for Triangle2
     */
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

#pragma region RefTriangle2
    /**
     * \brief some Commonly used RefTriangle2 types
     */
    using RefTriangle2d = RefTriangle2<double>;
    using RefTriangle2f = RefTriangle2<float>;
    using RefTriangle2i = RefTriangle2<int>;

    /**
     * \brief a sample template class to describe the 2-dime triangles
     */
    template <typename _Ty = float>
    class RefTriangle2
    {
    public:
        using value_type = _Ty;
        using id_type = uint;
        using refpoint_type = ns_geo::RefPoint2<value_type>;
        using refpointset_type = RefPointSet2<value_type>;
        using ary_type = std::array<refpoint_type, 3>;

    public:
        friend class RefPointSet2<value_type>;

    private:
        id_type _pid1;
        id_type _pid2;
        id_type _pid3;
        // thr reference point set's pointer
        const refpointset_type *_rps;

    protected:
        /**
         * \brief constructors
         */
        RefTriangle2(const id_type &pid1, const id_type &pid2, const id_type &pid3, const refpointset_type *refpointset)
            : _pid1(pid1), _pid2(pid2), _pid3(pid3), _rps(refpointset) {}

        RefTriangle2() = delete;

    public:
        const refpointset_type *refPointSet() const { return this->_rps; };

        const refpoint_type &p1() const { return this->_rps->at(_pid1); }
        refpoint_type &p1() { return this->_rps->at(_pid1); }

        const refpoint_type &p2() const { return this->_rps->at(_pid2); }
        refpoint_type &p2() { return this->_rps->at(_pid2); }

        const refpoint_type &p3() const { return this->_rps->at(_pid3); }
        refpoint_type &p3() { return this->_rps->at(_pid3); }

        ary_type points() const { return ary_type{this->p1(), this->p2(), this->p3()}; }

        float area() const
        {
            auto p1 = this->p1();
            auto p2 = this->p2();
            auto p3 = this->p3();
            float v12_x = p2.x() - p1.x();
            float v12_y = p2.y() - p1.y();
            float v13_x = p3.x() - p1.x();
            float v13_y = p3.y() - p1.y();
            return std::abs(v12_x * v13_y - v12_y * v13_x) * 0.5;
        }

        float perimeter() const
        {
            auto p1 = this->p1();
            auto p2 = this->p2();
            auto p3 = this->p3();
            return ns_geo::distance(p1, p2) +
                   ns_geo::distance(p1, p3) +
                   ns_geo::distance(p2, p3);
        }
    };
    /**
     * \brief overload operator "<<" for RefTriangle2
     */
    template <typename _Ty = float>
    std::ostream &operator<<(std::ostream &os, const RefTriangle2<_Ty> &tri)
    {
        auto p1 = tri.p1();
        auto p2 = tri.p2();
        auto p3 = tri.p3();
        os << '{';
        os << p1.id() << ": [" << p1.x() << ", " << p1.y() << ']' << ", ";
        os << p2.id() << ": [" << p2.x() << ", " << p2.y() << ']' << ", ";
        os << p3.id() << ": [" << p3.x() << ", " << p3.y() << "]}";
        return os;
    }
#pragma endregion

#pragma region Triangle3
    template <typename _Ty>
    class Triangle3;
    /**
     * \brief some Commonly used Triangle3 types
     */
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
        using point_type = ns_geo::Point3<value_type>;
        using ary_type = std::array<point_type, 3>;

    private:
        point_type _p1;
        point_type _p2;
        point_type _p3;

    public:
        /**
         * \brief constructors
         */
        Triangle3() = default;
        Triangle3(const point_type &p1, const point_type &p2, const point_type &p3)
            : _p1(p1), _p2(p2), _p3(p3) {}
        Triangle3(const point_type points[3])
            : _p1(points[0]), _p2(points[1]), _p3(points[2]) {}
        Triangle3(const ary_type &points)
            : _p1(points[0]), _p2(points[1]), _p3(points[2]) {}
        Triangle3(value_type p1x, value_type p1y, value_type p1z,
                  value_type p2x, value_type p2y, value_type p2z,
                  value_type p3x, value_type p3y, value_type p3z)
            : _p1(p1x, p1y, p1z), _p2(p2x, p2y, p2z), _p3(p3x, p3y, p3z) {}

        const point_type &p1() const { return this->_p1; }
        point_type &p1() { return this->_p1; }

        const point_type &p2() const { return this->_p2; }
        point_type &p2() { return this->_p2; }

        const point_type &p3() const { return this->_p3; }
        point_type &p3() { return this->_p3; }

        ary_type points() const { return ary_type{this->_p1, this->_p2, this->_p3}; }

        float area() const
        {
            float v12_x = _p2.x() - _p1.x();
            float v12_y = _p2.y() - _p1.y();
            float v12_z = _p2.z() - _p1.z();
            float v13_x = _p3.x() - _p1.x();
            float v13_y = _p3.y() - _p1.y();
            float v13_z = _p3.z() - _p1.z();
            auto val1 = std::pow(v12_y * v13_z - v12_z * v13_y, 2);
            auto val2 = std::pow(v13_x * v12_z - v12_x * v13_z, 2);
            auto val3 = std::pow(v12_x * v13_y - v12_y * v13_x, 2);
            return std::sqrt(val1 + val2 + val3) * 0.5;
        }

        float perimeter() const
        {
            return ns_geo::distance(_p1, _p2) +
                   ns_geo::distance(_p1, _p3) +
                   ns_geo::distance(_p2, _p3);
        }
    };
    /**
     * \brief overload operator "<<" for Triangle3
     */
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

#pragma region RefTriangle3
    /**
     * \brief some Commonly used RefTriangle3 types
     */
    using RefTriangle3d = RefTriangle3<double>;
    using RefTriangle3f = RefTriangle3<float>;
    using RefTriangle3i = RefTriangle3<int>;

    /**
     * \brief a sample template class to describe the 3-dime triangles
     */
    template <typename _Ty = float>
    class RefTriangle3
    {
    public:
        using value_type = _Ty;
        using id_type = uint;
        using refpoint_type = ns_geo::RefPoint3<value_type>;
        using refpointset_type = RefPointSet3<value_type>;
        using ary_type = std::array<refpoint_type, 3>;

    public:
        friend class RefPointSet3<value_type>;

    private:
        id_type _pid1;
        id_type _pid2;
        id_type _pid3;
        // the reference point set's pointer
        const refpointset_type *_rps;

    protected:
        /**
         * \brief constructors
         */
        RefTriangle3(const id_type &pid1, const id_type &pid2, const id_type &pid3, const refpointset_type *refpointset)
            : _pid1(pid1), _pid2(pid2), _pid3(pid3), _rps(refpointset) {}

        RefTriangle3() = delete;

    public:
        const refpointset_type *refPointSet() const { return this->_rps; };

        const refpoint_type &p1() const { return this->_rps->at(_pid1); }
        refpoint_type &p1() { return this->_rps->at(_pid1); }

        const refpoint_type &p2() const { return this->_rps->at(_pid2); }
        refpoint_type &p2() { return this->_rps->at(_pid2); }

        const refpoint_type &p3() const { return this->_rps->at(_pid3); }
        refpoint_type &p3() { return this->_rps->at(_pid3); }

        ary_type points() const { return ary_type{this->p1(), this->p2(), this->p3()}; }

        float area() const
        {
            auto p1 = this->p1();
            auto p2 = this->p2();
            auto p3 = this->p3();
            float v12_x = p2.x() - p1.x();
            float v12_y = p2.y() - p1.y();
            float v12_z = p2.z() - p1.z();
            float v13_x = p3.x() - p1.x();
            float v13_y = p3.y() - p1.y();
            float v13_z = p3.z() - p1.z();
            auto val1 = std::pow(v12_y * v13_z - v12_z * v13_y, 2);
            auto val2 = std::pow(v13_x * v12_z - v12_x * v13_z, 2);
            auto val3 = std::pow(v12_x * v13_y - v12_y * v13_x, 2);
            return std::sqrt(val1 + val2 + val3) * 0.5;
        }

        float perimeter() const
        {
            auto p1 = this->p1();
            auto p2 = this->p2();
            auto p3 = this->p3();
            return ns_geo::distance(p1, p2) +
                   ns_geo::distance(p1, p3) +
                   ns_geo::distance(p2, p3);
        }
    };
    /**
     * \brief overload operator "<<" for RefTriangle3
     */
    template <typename _Ty = float>
    std::ostream &operator<<(std::ostream &os, const RefTriangle3<_Ty> &tri)
    {
        auto p1 = tri.p1();
        auto p2 = tri.p2();
        auto p3 = tri.p3();
        os << '{';
        os << p1.id() << ": [" << p1.x() << ", " << p1.y() << ", " << p1.z() << ']' << ", ";
        os << p2.id() << ": [" << p2.x() << ", " << p2.y() << ", " << p2.z() << ']' << ", ";
        os << p3.id() << ": [" << p3.x() << ", " << p3.y() << ", " << p3.z() << "]}";
        return os;
    }
#pragma endregion
} // namespace ns_geo
