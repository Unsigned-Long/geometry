#pragma once

/**
 * @file utility.hpp
 * @author csl (3079625093@qq.com)
 * @brief Provide operation support for point classes
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
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
#pragma region helpers
    template <typename _Ty>
    class Point2;
    template <typename _Ty>
    class Point3;

    /**
     * @brief calculate the azimuth according the left hand rule
     * 
     * @tparam _Ty the type of value
     * @param p1 one of two points
     * @param p2 one of two points
     * @return float the azimuth[radian]
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
     * @brief calculate the azimuth according the left hand rule
     * 
     * @tparam _Ty the type of value
     * @param p1 one of two points
     * @param p2 one of two points
     * @return float the azimuth[radian]
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
     * @brief Calculate the distance between two points
     * 
     * @tparam _Ty the type of value
     * @param p1 one of two points
     * @param p2 one of two points
     * @return float the distance between two points
     */
    template <typename _Ty>
    float distance(const Point2<_Ty> &p1, const Point2<_Ty> &p2)
    {
        return static_cast<float>(std::sqrt(std::pow(p1.x() - p2.x(), 2) + std::pow(p1.y() - p2.y(), 2)));
    }

    /**
     * @brief Calculate the distance between two points
     * 
     * @tparam _Ty the type of value
     * @param p1 one of two points
     * @param p2 one of two points
     * @return float the distance between two points
     */
    template <typename _Ty>
    float distance(const Point3<_Ty> &p1, const Point3<_Ty> &p2)
    {
        return static_cast<float>(std::sqrt(std::pow(p1.x() - p2.x(), 2) + std::pow(p1.y() - p2.y(), 2) + std::pow(p1.z() - p2.z(), 2)));
    }

    /**
     * @brief calculate the stride between the 'from' point to the 'to' point
     * 
     * @tparam _Ty the type of value
     * @param from the start point
     * @param to the end point
     * @return std::array<_Ty, 3> return a array contains three elements
     */
    template <typename _Ty>
    std::array<_Ty, 2> stride(const Point2<_Ty> &from, const Point2<_Ty> &to)
    {
        return std::array<_Ty, 2>{to.x() - from.x(), to.y() - from.y()};
    }

    /**
     * @brief calculate the stride between the 'from' point to the 'to' point
     * 
     * @tparam _Ty the type of value
     * @param from the start point
     * @param to the end point
     * @return std::array<_Ty, 3> return a array contains three elements
     */
    template <typename _Ty>
    std::array<_Ty, 3> stride(const Point3<_Ty> &from, const Point3<_Ty> &to)
    {
        return std::array<_Ty, 3>{to.x() - from.x(), to.y() - from.y(), to.z() - from.z()};
    }

#pragma endregion
} // namespace ns_geo
