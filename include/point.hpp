#pragma once

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <exception>
#include <algorithm>
#include <array>
#include <vector>

namespace ns_geo
{
#pragma region global

    template <typename PointContainer>
    void writeBinaryData(const PointContainer &ls, std::ofstream &file)
    {
        using PointType = typename PointContainer::value_type;
        for (const auto &elem : ls)
            file.write((const char *)(&elem), sizeof(PointType));
        return;
    }

    template <typename PointContainer>
    void readBinaryData(PointContainer &ls, std::ifstream &file)
    {
        using PointType = typename PointContainer::value_type;
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
     * \brief Calculate the distance between two points
     */
    template <typename _Ty>
    float distance(const Point2<_Ty> &p1, const Point2<_Ty> &p2)
    {
        return static_cast<float>(std::sqrt(std::pow(p1.x() - p2.x(), 2) + std::pow(p1.y() - p2.y(), 2)));
    }

    /**
     * \brief Writes a 2D point set to a file
     */
    template <typename PointContainer>
    void writePoints2(const PointContainer &points, const std::string &filePath, std::ios_base::openmode mode = std::ios::out | std::ios::binary)
    {
        std::ofstream file(filePath, mode);
        if (!file.is_open())
            throw std::ios_base::failure("File Open Failed");
        if (std::ios::binary == (mode & std::ios::binary))
        {
            ns_geo::writeBinaryData(points, file);
        }
        else
        {
            for (const auto &point : points)
            {
                file << point.x() << ',' << point.y() << '\n';
            }
        }
    }

    /**
     * \brief Read the 2D point set from the file to the program
     */
    template <typename PointContainer>
    void readPoints2(PointContainer &points, const std::string &filePath, std::ios_base::openmode mode = std::ios::in | std::ios::binary)
    {
        using PointType = typename PointContainer::value_type;
        using PointValueType = typename PointType::value_type;
        std::ifstream file(filePath, mode);
        if (!file.is_open())
            throw std::ios_base::failure("File Open Failed");
        if (std::ios::binary == (mode & std::ios::binary))
        {
            ns_geo::readBinaryData(points, file);
        }
        else
        {
            Point2<PointValueType> point;
            std::string str;
            while (!file.eof())
            {
                std::getline(file, str);
                if (str.empty())
                    continue;
                auto iter = std::find(str.cbegin(), str.cend(), ',');
                point.x() = static_cast<PointValueType>(std::stod(std::string(str.cbegin(), iter)));
                point.y() = static_cast<PointValueType>(std::stod(std::string(++iter, str.cend())));
                points.push_back(point);
            }
        }
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

    /**
     * \brief Writes a 3D point set to a file
     */
    template <typename PointContainer>
    void writePoints3(const PointContainer &points, const std::string &filePath, std::ios_base::openmode mode = std::ios::out | std::ios::binary)
    {
        std::ofstream file(filePath, mode);
        if (!file.is_open())
            throw std::ios_base::failure("File Open Failed");
        if (std::ios::binary == (mode & std::ios::binary))
        {
            ns_geo::writeBinaryData(points, file);
        }
        else
        {
            for (const auto &point : points)
            {
                file << point.x() << ',' << point.y() << ',' << point.z() << '\n';
            }
        }
    }

    /**
     * \brief Read the 3D point set from the file to the program
     */
    template <typename PointContainer>
    void readPoints3(PointContainer &points, const std::string &filePath, std::ios_base::openmode mode = std::ios::in | std::ios::binary)
    {
        using PointType = typename PointContainer::value_type;
        using PointValueType = typename PointType::value_type;
        std::ifstream file(filePath, mode);
        if (!file.is_open())
            throw std::ios_base::failure("File Open Failed");
        if (std::ios::binary == (mode & std::ios::binary))
        {
            ns_geo::readBinaryData(points, file);
        }
        else
        {
            Point3<PointValueType> point;
            std::string str;
            while (!file.eof())
            {
                std::getline(file, str);
                if (str.empty())
                    continue;
                auto iter = std::find(str.cbegin(), str.cend(), ',');
                point.x() = static_cast<PointValueType>(std::stod(std::string(str.cbegin(), iter)));
                auto iter2 = std::find(++iter, str.cend(), ',');
                point.y() = static_cast<PointValueType>(std::stod(std::string(iter, iter2)));
                point.z() = static_cast<PointValueType>(std::stod(std::string(++iter2, str.cend())));
                points.push_back(point);
            }
        }
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

        operator ary_type() const { return ary_type{this->_x, this->_y}; }

        value_type &x() { return this->_x; }
        value_type &y() { return this->_y; }

        const value_type &x() const { return this->_x; }
        const value_type &y() const { return this->_y; }
    };

    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const Point2<_Ty> &p)
    {
        os << '[' << p.x() << ',' << p.y() << ']';
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
        os << '[' << p.x() << ',' << p.y() << ',' << p.z() << ']';
        return os;
    }
#pragma endregion

#pragma region PointSet
    template <typename _PointType, typename _Alloc = std::allocator<_PointType>>
    class PointSet : public std::vector<_PointType, _Alloc>
    {
        using point_type = _PointType;
        using value_type = typename _PointType::value_type;
        using container_type = std::vector<_PointType, _Alloc>;
        using container_type::container_type;
    };

    using PointSet2i = PointSet<Point2i>;
    using PointSet2f = PointSet<Point2f>;
    using PointSet2d = PointSet<Point2d>;
    using PointSet3i = PointSet<Point3i>;
    using PointSet3f = PointSet<Point3f>;
    using PointSet3d = PointSet<Point3d>;
#pragma endregion

} // namespace ns_geo
