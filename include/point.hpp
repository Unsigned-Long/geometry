#pragma once

/**
 * \brief the details
 *       [1] class type
 *              0. Point2<_Ty>, Point3<_Ty>, PointSet2<_PointType>
 *              1. Point2f, Point3f
 *              2. Point2d, Point3d
 *              3. Point2i, Point3i
 *              4. PointSet<>
 *              5. RefPoint2<>, RefPoint3<>
 *              6. RefPointSet<>
 * 
 *       [2] methods
 *              0. writeBinaryData, readBinaryData
 *              1. azimuthRHR, azimuthLHR
 *              2. distance
 *              3. writePoints2, readPoints2
 *              4. writePoints3, readPoints3
 *              5. operator "<<" for Point2<_Ty>, Point3<_Ty>
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <exception>
#include <algorithm>
#include <array>
#include <vector>
#include <unordered_map>

namespace ns_geo
{
#pragma region global

    template <typename PointContainer>
    void writeBinaryData(const PointContainer &ls, std::ofstream &file)
    {
        using PointType = typename PointContainer::point_type;
        for (const auto &elem : ls)
            file.write((const char *)(&elem), sizeof(PointType));
        return;
    }

    template <typename PointContainer>
    void readBinaryData(PointContainer &ls, std::ifstream &file)
    {
        using PointType = typename PointContainer::point_type;
        PointType elem;
        file.seekg(0, std::ios::end);
        auto size = file.tellg() / sizeof(PointType);
        file.seekg(0, std::ios::beg);
        int count = 0;
        while (!file.eof() && count < size)
        {
            file.read((char *)(&elem), sizeof(PointType));
            ls.push_back(elem);
            ++count;
        }
    }

#pragma region global for Point2 < _Ty>
    template <typename _Ty>
    class Point2;

    /**
     * \brief some commonly used 2D point classes
     */
    using Point2f = Point2<float>;
    using Point2d = Point2<double>;
    using Point2i = Point2<int>;

    /**
     * \brief calculate the azimuth according the right hand rule
     */
    template <typename _Ty>
    float azimuthRHR(const Point2<_Ty> &from, const Point2<_Ty> &to)
    {
        float detaX = to.x() - from.x();
        float detaY = to.y() - from.y();
        float angle = std::atan2(detaX, detaY);
        if (detaX < 0.0)
            angle += 2 * M_PI;
        return angle;
    }

    /**
     * \brief calculate the azimuth according the left hand rule
     */
    template <typename _Ty>
    float azimuthLHR(const Point2<_Ty> &from, const Point2<_Ty> &to)
    {
        float detaX = to.x() - from.x();
        float detaY = to.y() - from.y();
        float angle = std::atan2(detaY, detaX);
        if (detaY < 0.0)
            angle += 2 * M_PI;
        return angle;
    }

    /**
     * \brief Calculate the distance between two points
     */
    template <typename _Ty>
    float distance(const Point2<_Ty> &p1, const Point2<_Ty> &p2)
    {
        return static_cast<float>(std::sqrt(std::pow(p1.x() - p2.x(), 2) + std::pow(p1.y() - p2.y(), 2)));
    }

#pragma endregion

#pragma region global for Point3 < _Ty>

    template <typename _Ty>
    class Point3;
    /**
     * \brief some commonly used 3D point classes
     */
    using Point3f = Point3<float>;
    using Point3d = Point3<double>;
    using Point3i = Point3<int>;

    /**
     * \brief Calculate the distance between two points
     */
    template <typename _Ty>
    float distance(const Point3<_Ty> &p1, const Point3<_Ty> &p2)
    {
        return static_cast<float>(std::sqrt(std::pow(p1.x() - p2.x(), 2) + std::pow(p1.y() - p2.y(), 2) + std::pow(p1.z() - p2.z(), 2)));
    }

#pragma endregion

#pragma endregion

#pragma region class Point2 < _Ty>
    /**
     * \brief a sample template class to describe the 2-dime points
     */
    template <typename _Ty = float>
    class Point2
    {
    public:
        using value_type = _Ty;
        using ary_type = std::array<_Ty, 2>;

    private:
        value_type _x;
        value_type _y;

    public:
        Point2() = default;
        Point2(value_type x, value_type y) : _x(x), _y(y) {}
        Point2(const ary_type &p) : _x(p[0]), _y(p[1]) {}
        Point2(const value_type p[2]) : _x(p[0]), _y(p[1]) {}

        operator ary_type() const { return ary_type{this->_x, this->_y}; }

        value_type &x() { return this->_x; }
        value_type &y() { return this->_y; }

        const value_type &x() const { return this->_x; }
        const value_type &y() const { return this->_y; }
    };

    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const Point2<_Ty> &p)
    {
        os << '[' << p.x() << ", " << p.y() << ']';
        return os;
    }
#pragma endregion

#pragma region class Point3 < _Ty>
    /**
     * \brief a sample template class to describe the 3-dime points
     */
    template <typename _Ty = float>
    class Point3
    {
    public:
        using value_type = _Ty;
        using ary_type = std::array<_Ty, 3>;

    private:
        value_type _x;
        value_type _y;
        value_type _z;

    public:
        Point3() = default;
        Point3(value_type x, value_type y, value_type z) : _x(x), _y(y), _z(z) {}
        Point3(const ary_type &p) : _x(p[0]), _y(p[1]), _z(p[2]) {}
        Point3(const value_type p[3]) : _x(p[0]), _y(p[1]), _z(p[2]) {}

        operator ary_type() const { return ary_type{this->_x, this->_y, this->_z}; }

        value_type &x() { return this->_x; }
        value_type &y() { return this->_y; }
        value_type &z() { return this->_z; }

        const value_type &x() const { return this->_x; }
        const value_type &y() const { return this->_y; }
        const value_type &z() const { return this->_z; }
    };

    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const Point3<_Ty> &p)
    {
        os << '[' << p.x() << ", " << p.y() << ", " << p.z() << ']';
        return os;
    }
#pragma endregion

#pragma region PointSet2

    template <typename _Ty, typename _Alloc = std::allocator<Point2<_Ty>>>
    class PointSet2 : public std::vector<Point2<_Ty>, _Alloc>
    {
    public:
        using value_type = _Ty;
        using point_type = Point2<value_type>;
        using container_type = std::vector<point_type, _Alloc>;
        using container_type::container_type;

    public:
        void write(const std::string &filePath, std::ios_base::openmode mode = std::ios::out | std::ios::binary) const
        {
            std::ofstream file(filePath, mode);
            if (!file.is_open())
                throw std::ios_base::failure("File Open Failed");
            if (std::ios::binary == (mode & std::ios::binary))
                ns_geo::writeBinaryData(*this, file);
            else
                for (const auto &point : *this)
                    file << point.x() << ',' << point.y() << '\n';
            return;
        }

        void read(const std::string &filePath, std::ios_base::openmode mode = std::ios::in | std::ios::binary)
        {
            std::ifstream file(filePath, mode);
            if (!file.is_open())
                throw std::ios_base::failure("File Open Failed");
            if (std::ios::binary == (mode & std::ios::binary))
                ns_geo::readBinaryData(*this, file);
            else
            {
                Point2<value_type> point;
                std::string str;
                while (!file.eof())
                {
                    std::getline(file, str);
                    if (str.empty())
                        continue;
                    auto iter = std::find(str.cbegin(), str.cend(), ',');
                    point.x() = static_cast<value_type>(std::stod(std::string(str.cbegin(), iter)));
                    point.y() = static_cast<value_type>(std::stod(std::string(++iter, str.cend())));
                    this->push_back(point);
                }
            }
        }
    };

    using PointSet2i = PointSet2<int>;
    using PointSet2f = PointSet2<float>;
    using PointSet2d = PointSet2<double>;

#pragma endregion

#pragma region PointSet3

    template <typename _Ty, typename _Alloc = std::allocator<Point3<_Ty>>>
    class PointSet3 : public std::vector<Point3<_Ty>, _Alloc>
    {
    public:
        using value_type = _Ty;
        using point_type = Point3<value_type>;
        using container_type = std::vector<point_type, _Alloc>;
        using container_type::container_type;

    public:
        void write(const std::string &filePath, std::ios_base::openmode mode = std::ios::out | std::ios::binary) const
        {
            std::ofstream file(filePath, mode);
            if (!file.is_open())
                throw std::ios_base::failure("File Open Failed");
            if (std::ios::binary == (mode & std::ios::binary))
                ns_geo::writeBinaryData(*this, file);
            else
                for (const auto &point : *this)
                    file << point.x() << ',' << point.y() << ',' << point.z() << '\n';
            return;
        }

        void read(const std::string &filePath, std::ios_base::openmode mode = std::ios::in | std::ios::binary)
        {
            std::ifstream file(filePath, mode);
            if (!file.is_open())
                throw std::ios_base::failure("File Open Failed");
            if (std::ios::binary == (mode & std::ios::binary))
                ns_geo::readBinaryData(*this, file);
            else
            {
                Point3<value_type> point;
                std::string str;
                while (!file.eof())
                {
                    std::getline(file, str);
                    if (str.empty())
                        continue;
                    auto iter = std::find(str.cbegin(), str.cend(), ',');
                    point.x() = static_cast<value_type>(std::stod(std::string(str.cbegin(), iter)));
                    auto iter2 = std::find(++iter, str.cend(), ',');
                    point.y() = static_cast<value_type>(std::stod(std::string(iter, iter2)));
                    point.z() = static_cast<value_type>(std::stod(std::string(++iter2, str.cend())));
                    this->push_back(point);
                }
            }
        }
    };

    using PointSet3i = PointSet3<int>;
    using PointSet3f = PointSet3<float>;
    using PointSet3d = PointSet3<double>;
#pragma endregion

#pragma region RefPoint
    template <typename _Ty>
    class RefPoint2 : public Point2<_Ty>
    {
    public:
        using id_type = uint;
        using value_type = _Ty;
        using ary_type = std::array<_Ty, 2>;

    private:
        id_type _id;

    public:
        RefPoint2() = default;
        RefPoint2(id_type id, value_type x, value_type y)
            : _id(id), Point2<_Ty>(x, y) {}
        RefPoint2(id_type id, const ary_type &p)
            : _id(id), Point2<_Ty>(p[0], p[1]) {}
        RefPoint2(id_type id, const value_type p[2])
            : _id(id), Point2<_Ty>(p[0], p[1]) {}
        const id_type &id() const { return this->_id; }
    };

    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const RefPoint2<_Ty> &p)
    {
        os << '{' << p.id() << ": " << '[' << p.x() << ", " << p.y() << ']' << '}';
        return os;
    }

    using RefPoint2f = RefPoint2<float>;
    using RefPoint2d = RefPoint2<double>;
    using RefPoint2i = RefPoint2<int>;

    template <typename _Ty>
    class RefPoint3 : public Point3<_Ty>
    {
    public:
        using id_type = uint;
        using value_type = _Ty;
        using ary_type = std::array<_Ty, 3>;

    private:
        id_type _id;

    public:
        RefPoint3() = default;
        RefPoint3(id_type id, value_type x, value_type y, value_type z)
            : _id(id), Point3<_Ty>(x, y, z) {}
        RefPoint3(id_type id, const ary_type &p)
            : _id(id), Point3<_Ty>(p[0], p[1], p[2]) {}
        RefPoint3(id_type id, const value_type p[3])
            : _id(id), Point3<_Ty>(p[0], p[1], p[2]) {}

        const id_type &id() const { return this->_id; }
    };

    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const RefPoint3<_Ty> &p)
    {
        os << '{' << p.id() << ": " << '[' << p.x() << ", " << p.y() << ", " << p.z() << ']' << '}';
        return os;
    }

    using RefPoint3f = RefPoint3<float>;
    using RefPoint3d = RefPoint3<double>;
    using RefPoint3i = RefPoint3<int>;
#pragma endregion

#pragma region RefPointSet2
    /**
     * \brief declare here for the reference geometry objects
     */
    template <typename _Ty>
    class RefLine2;
    template <typename _Ty>
    class RefRectangle;
    template <typename _Ty>
    class RefTriangle2;

    template <typename _Ty,
              typename _Hash = std::hash<uint>,
              typename _Pred = std::equal_to<uint>,
              typename _Alloc = std::allocator<std::pair<const uint, RefPoint2<_Ty>>>>
    class RefPointSet2 : public std::unordered_map<uint, RefPoint2<_Ty>, _Hash, _Pred, _Alloc>
    {
    public:
        using value_type = _Ty;
        using refpoint_type = RefPoint2<value_type>;
        using container_type = std::unordered_map<uint, refpoint_type, _Hash, _Pred, _Alloc>;
        using container_type::container_type;

        auto insert(const refpoint_type &p)
        {
            return container_type::insert(std::make_pair(p.id(), p));
        }

        /**
         * \brief create reference line[2d] by the reference point set
         */
        RefLine2<value_type> createRefLine2(uint pid1, uint pid2) { return RefLine2<value_type>(pid1, pid2, this); }

        RefRectangle<value_type> createRefRectangle(uint topLeftID, uint lowerRightID) { return RefRectangle<value_type>(topLeftID, lowerRightID, this); }

        RefTriangle2<value_type> createRefTriangle2(uint pid1, uint pid2, uint pid3) { return RefTriangle2<value_type>(pid1, pid2, pid3, this); }

    private:
        /**
         * \brief dangerous function has been deleted
         */
        refpoint_type &
        operator[](const uint &id) = delete;
    };

    using RefPointSet2i = RefPointSet2<int>;
    using RefPointSet2f = RefPointSet2<float>;
    using RefPointSet2d = RefPointSet2<double>;
#pragma endregion

#pragma region RefPointSet3
    /**
     * \brief declare here for the reference geometry objects
     */
    template <typename _Ty>
    class RefLine3;
    template <typename _Ty>
    class RefTriangle3;

    template <typename _Ty,
              typename _Hash = std::hash<uint>,
              typename _Pred = std::equal_to<uint>,
              typename _Alloc = std::allocator<std::pair<const uint, RefPoint3<_Ty>>>>
    class RefPointSet3 : public std::unordered_map<uint, RefPoint3<_Ty>, _Hash, _Pred, _Alloc>
    {
    public:
        using value_type = _Ty;
        using refpoint_type = RefPoint3<value_type>;
        using container_type = std::unordered_map<uint, refpoint_type, _Hash, _Pred, _Alloc>;
        using container_type::container_type;

        auto insert(const refpoint_type &p)
        {
            return container_type::insert(std::make_pair(p.id(), p));
        }

        /**
         * \brief create reference line[3d] by the reference point set
         */
        RefLine3<value_type> createRefLine3(uint pid1, uint pid2) { return RefLine3<value_type>(pid1, pid2, this); }

        RefTriangle3<value_type> createRefTriangle3(uint pid1, uint pid2, uint pid3) { return RefTriangle3<value_type>(pid1, pid2, pid3, this); }

    private:
        /**
         * \brief dangerous function has been deleted
         */
        refpoint_type &operator[](const uint &id) = delete;
    };

    using RefPointSet3i = RefPointSet3<int>;
    using RefPointSet3f = RefPointSet3<float>;
    using RefPointSet3d = RefPointSet3<double>;
#pragma endregion
} // namespace ns_geo
