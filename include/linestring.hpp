#pragma once

/**
 * \brief the details
 *       [1] class type
 *              0. LineString2<_Ty>, LineString3<_Ty>
 *              1. RefLineString2<_Ty>, RefLineString3<_Ty>
 * 
 *       [2] methods for LineString
 *              0. length
 *              2. operator "<<" for LineString2<_Ty>, LineString3<_Ty>
 *              3. operator "<<" for RefLineString2<_Ty>, RefLineString3<_Ty>
 */

#include "point.hpp"

namespace ns_geo
{
#pragma region LineString2
    template <typename _Ty>
    class LineString2;
    /**
     * \brief some Commonly used LineString2 types
     */
    using LineString2d = LineString2<double>;
    using LineString2f = LineString2<float>;
    using LineString2i = LineString2<int>;

    template <typename _Ty>
    class LineString2 : public PointSet2<_Ty>
    {
    public:
        using value_type = _Ty;
        using pointset_type = PointSet2<value_type>;
        /**
         * \brief using pointset_type's constructors
         */
        using pointset_type::pointset_type;

        float length() const
        {
            float len = 0.0;
            for (auto iter = this->cbegin(); iter != --this->cend();)
                len += distance(*iter, *(iter++));
            return len;
        }
    };
    /**
     * \brief overload operator "<<" for LineString2
     */
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

#pragma region LineString3
    template <typename _Ty>
    class LineString3;
    /**
     * \brief some Commonly used LineString3 types
     */
    using LineString3d = LineString3<double>;
    using LineString3f = LineString3<float>;
    using LineString3i = LineString3<int>;

    template <typename _Ty>
    class LineString3 : public PointSet3<_Ty>
    {
    public:
        using value_type = _Ty;
        using pointset_type = PointSet3<value_type>;
        /**
         * \brief using pointset_type's constructors
         */
        using pointset_type::pointset_type;

        float length() const
        {
            float len = 0.0;
            for (auto iter = this->cbegin(); iter != --this->cend();)
                len += distance(*iter, *(iter++));
            return len;
        }
    };
    /**
     * \brief overload operator "<<" for LineString3
     */
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

#pragma region RefLineString2
    /**
     * \brief some Commonly used RefLineString2 types
     */
    using RefLineString2d = RefLineString2<double>;
    using RefLineString2f = RefLineString2<float>;
    using RefLineString2i = RefLineString2<int>;

    template <typename _Ty>
    class RefLineString2 : public std::vector<uint>
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
        RefLineString2(const std::initializer_list<id_type> &pidls, const refpointset_type *rps)
            : pointidset_type(pidls), _rps(rps) {}

        RefLineString2() = delete;

    public:
        const refpointset_type *refPointSet() const { return this->_rps; };

        float length() const
        {
            float len = 0.0;
            for (auto iter = this->cbegin(); iter != --this->cend();)
                len += distance(_rps->at(*iter), _rps->at(*(iter++)));
            return len;
        }
    };
    /**
     * \brief overload operator "<<" for RefLineString2
     */
    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const RefLineString2<_Ty> &ls)
    {
        auto rps = ls.refPointSet();
        os << '{';
        for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter)
        {
            auto &p = rps->at(*iter);
            os << p.id() << ": [" << p.x() << ", " << p.y() << ']' << ", ";
        }
        auto &p = rps->at(ls.back());
        os << p.id() << ": [" << p.x() << ", " << p.y() << "]}";
        return os;
    }
#pragma endregion

#pragma region RefLineString3
    /**
     * \brief some Commonly used RefLineString3 types
     */
    using RefLineString3d = RefLineString3<double>;
    using RefLineString3f = RefLineString3<float>;
    using RefLineString3i = RefLineString3<int>;

    template <typename _Ty>
    class RefLineString3 : public std::vector<uint>
    {
    public:
        using value_type = _Ty;
        using id_type = uint;
        using refpoint_type = RefPoint3<value_type>;
        using pointidset_type = std::vector<id_type>;
        using refpointset_type = RefPointSet3<value_type>;

    public:
        friend class RefPointSet3<value_type>;

    private:
        const refpointset_type *_rps;

    protected:
        /**
         * \brief constructors
         */
        RefLineString3(const std::initializer_list<id_type> &pidls, const refpointset_type *rps)
            : pointidset_type(pidls), _rps(rps) {}

        RefLineString3() = delete;

    public:
        const refpointset_type *refPointSet() const { return this->_rps; };

        float length() const
        {
            float len = 0.0;
            for (auto iter = this->cbegin(); iter != --this->cend();)
                len += distance(_rps->at(*iter), _rps->at(*(iter++)));
            return len;
        }
    };
    /**
     * \brief overload operator "<<" for RefLineString3
     */
    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const RefLineString3<_Ty> &ls)
    {
        auto rps = ls.refPointSet();
        os << '{';
        for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter)
        {
            auto &p = rps->at(*iter);
            os << p.id() << ": [" << p.x() << ", " << p.y() << ", " << p.z() << ']' << ", ";
        }
        auto &p = rps->at(ls.back());
        os << p.id() << ": [" << p.x() << ", " << p.y() << ", " << p.z() << "]}";
        return os;
    }
#pragma endregion
} // namespace ns_geo
