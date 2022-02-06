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

namespace ns_geo {
#pragma region Rectangle

/**
 * \brief a sample template class to describe the 2-dime rectangles
 */
template <typename _Ty = float>
class Rectangle {
 public:
  using value_type = _Ty;
  using point_type = ns_geo::Point2<value_type>;
  using ary_type = std::array<point_type, 2>;
  using self_type = Rectangle<value_type>;

 private:
  // top left point
  point_type _tplp;
  // lower right point
  point_type _bmrp;

 public:
  /**
   * \brief constructors
   */
  Rectangle() = default;
  Rectangle(const point_type &topLeft, const point_type &bottomRight)
      : _tplp(topLeft), _bmrp(bottomRight) {}
  Rectangle(const point_type points[2]) : _tplp(points[0]), _bmrp(points[1]) {}
  Rectangle(const ary_type &points) : _tplp(points[0]), _bmrp(points[1]) {}
  Rectangle(value_type tlx, value_type tly, value_type lrx, value_type lry)
      : _tplp(tlx, tly), _bmrp(lrx, lry) {}

  ary_type points() const { return ary_type{this->_tplp, this->_bmrp}; }

  const point_type &topLeft() const { return this->_tplp; }

  point_type &topLeft() { return this->_tplp; }

  const point_type &bottomRight() const { return this->_bmrp; }

  point_type &bottomRight() { return this->_bmrp; }

  float area() const {
    return std::abs(this->_tplp.x() - this->_bmrp.x()) *
           std::abs(this->_tplp.y() - this->_bmrp.y());
  }

  float perimeter() const {
    return 2.0 * (std::abs(this->_tplp.x() - this->_bmrp.x()) +
                  std::abs(this->_tplp.y() - this->_bmrp.y()));
  }

  static ns_geo::GeometryType type() { return GeometryType::RECTANGLE; }
};
/**
 * \brief overload operator "<<" for Rectangle
 */
template <typename _Ty = float>
std::ostream &operator<<(std::ostream &os, const Rectangle<_Ty> &rect) {
  os << '{';
  os << rect.topLeft() << ", ";
  os << rect.bottomRight() << '}';
  return os;
}
#pragma endregion

#pragma region RefRectangle

template <typename _Ty = float>
class RefRectangle {
 public:
  using value_type = _Ty;
  using id_type = uint;
  using refpoint_type = ns_geo::RefPoint2<value_type>;
  using refpointset_type = RefPointSet2<value_type>;
  using ary_type = std::array<refpoint_type, 2>;
  using self_type = RefRectangle<value_type>;

 public:
  friend class RefPointSet2<value_type>;

 private:
  // top left point's id
  id_type _tplpid;
  // lower right point's id
  id_type _bmrpid;
  // thr reference point set's pointer
  const refpointset_type *const _rps;

 protected:
  /**
   * \brief constructors
   */
  RefRectangle(id_type topLeftID, id_type bottomRightID,
               const refpointset_type *const refpointset)
      : _tplpid(topLeftID), _bmrpid(bottomRightID), _rps(refpointset) {}

  RefRectangle() = delete;

 public:
  const refpointset_type *const refPointSet() const { return this->_rps; };

  operator Rectangle<value_type>() {
    return Rectangle<value_type>(this->topLeft(), this->bottomRight());
  }

  ary_type refPoints() const {
    return ary_type{_rps->at(this->_tplpid), _rps->at(this->_bmrpid)};
  }

  const refpoint_type &topLeft() const { return _rps->at(this->_tplpid); }

  const refpoint_type &bottomRight() const { return _rps->at(this->_bmrpid); }

  const id_type &topLeftID() const { return this->_tplpid; }

  const id_type &bottomRightID() const { return this->_bmrpid; }

  float area() const {
    return std::abs(this->topLeft().x() - this->bottomRight().x()) *
           std::abs(this->topLeft().y() - this->bottomRight().y());
  }

  float perimeter() const {
    return 2.0 * (std::abs(this->topLeft().x() - this->bottomRight().x()) +
                  std::abs(this->topLeft().y() - this->bottomRight().y()));
  }

  static RefGeometryType type() {
    return ns_geo::RefGeometryType::REFRECTANGLE;
  }
};
/**
 * \brief overload operator "<<" for RefRectangle
 */
template <typename _Ty = float>
std::ostream &operator<<(std::ostream &os, const RefRectangle<_Ty> &rect) {
  auto p1 = rect.topLeft();
  auto p2 = rect.bottomRight();
  os << '{';
  os << p1.id() << ": [" << p1.x() << ", " << p1.y() << ']' << ", ";
  os << p2.id() << ": [" << p2.x() << ", " << p2.y() << "]}";
  return os;
}
#pragma endregion
}  // namespace ns_geo
