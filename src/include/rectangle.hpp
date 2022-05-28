#pragma once

/**
 * @file rectangle.hpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 */

#include "point.hpp"

namespace ns_geo {
#pragma region Rectangle

  /**
   * @brief a sample template class to describe the 2-dime rectangles
   */
  template <typename Ty = float>
  class Rectangle : protected Geometry {
  public:
    using value_type = Ty;
    using point_type = ns_geo::Point2<value_type>;
    using ary_type = std::array<point_type, 2>;
    using self_type = Rectangle<value_type>;

  public:
    // top left point
    point_type topLeftPt;
    // lower right point
    point_type bottomRightPt;

  public:
    /**
     * @brief constructors
     */
    Rectangle() = default;
    Rectangle(const point_type &topLeft, const point_type &bottomRight)
        : topLeftPt(topLeft), bottomRightPt(bottomRight) {}
    explicit Rectangle(const point_type points[2]) : topLeftPt(points[0]), bottomRightPt(points[1]) {}
    explicit Rectangle(const ary_type &points) : topLeftPt(points[0]), bottomRightPt(points[1]) {}
    Rectangle(value_type tlx, value_type tly, value_type lrx, value_type lry)
        : topLeftPt(tlx, tly), bottomRightPt(lrx, lry) {}

    inline ary_type points() const { return ary_type{this->topLeftPt, this->bottomRightPt}; }

    [[nodiscard]] inline float area() const {
      return std::abs(this->topLeftPt.x - this->bottomRightPt.x) *
             std::abs(this->topLeftPt.y - this->bottomRightPt.y);
    }

    [[nodiscard]] inline float perimeter() const {
      return 2.0 * (std::abs(this->topLeftPt.x - this->bottomRightPt.x) +
                    std::abs(this->topLeftPt.y - this->bottomRightPt.y));
    }

    [[nodiscard]] inline ns_geo::GeoType type() const override {
      return GeoType::RECTANGLE;
    }
  };
  /**
   * @brief overload operator "<<" for Rectangle<_Ty>
   */
  template <typename Ty = float>
  std::ostream &operator<<(std::ostream &os, const Rectangle<Ty> &rect) {
    os << '{';
    os << rect.topLeftPt << ", ";
    os << rect.bottomRightPt << '}';
    return os;
  }
#pragma endregion

#pragma region RefRectangle

  template <typename Ty = float>
  class RefRectangle : protected Geometry {
  public:
    using value_type = Ty;
    using id_type = uint;
    using refpoint_type = ns_geo::RefPoint2<value_type>;
    using refpointset_type = RefPointSet2<value_type>;
    using ary_type = std::array<refpoint_type, 2>;
    using self_type = RefRectangle<value_type>;

  public:
    friend class RefPointSet2<value_type>;

  public:
    // top left point's id
    id_type topLeftPID;
    // lower right point's id
    id_type bottomRightPID;
    // thr reference point set's pointer
    const refpointset_type *const _rps;

  protected:
    /**
     * @brief constructors
     */
    RefRectangle(id_type topLeftID, id_type bottomRightID,
                 const refpointset_type *const refpointset)
        : topLeftPID(topLeftID), bottomRightPID(bottomRightID), _rps(refpointset) {}


  public:
    inline const refpointset_type *refPointSet() const {
      return this->_rps;
    };

    explicit operator Rectangle<value_type>() {
      return Rectangle<value_type>(this->topLeft(), this->bottomRight());
    }

    inline ary_type refPoints() const {
      return ary_type{_rps->at(this->topLeftPID), _rps->at(this->bottomRightPID)};
    }

    inline const refpoint_type &topLeft() const {
      return _rps->at(this->topLeftPID);
    }

    inline const refpoint_type &bottomRight() const {
      return _rps->at(this->bottomRightPID);
    }

    [[nodiscard]] inline float area() const {
      return std::abs(this->topLeft().x - this->bottomRight().x) *
             std::abs(this->topLeft().y - this->bottomRight().y);
    }

    [[nodiscard]] inline float perimeter() const {
      return 2.0 * (std::abs(this->topLeft().x - this->bottomRight().x) +
                    std::abs(this->topLeft().y - this->bottomRight().y));
    }

    [[nodiscard]] inline ns_geo::GeoType type() const override {
      return GeoType::REF_RECTANGLE;
    }
  };
  /**
   * @brief overload operator "<<" for RefRectangle<_Ty>
   */
  template <typename Ty = float>
  std::ostream &operator<<(std::ostream &os, const RefRectangle<Ty> &rect) {
    auto p1 = rect.topLeft();
    auto p2 = rect.bottomRight();
    os << '{';
    os << p1.id << ": [" << p1.x << ", " << p1.y << ']' << ", ";
    os << p2.id << ": [" << p2.x << ", " << p2.y << "]}";
    return os;
  }
#pragma endregion
} // namespace ns_geo
