#pragma once

/**
 * @file triangle.hpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 */

#include "line.hpp"
#include "point.hpp"

namespace ns_geo {
#pragma region Triangle2

  /**
   * @brief a sample template class to describe the 2-dime triangles
   */
  template <typename _Ty = float>
  class Triangle2 : protected Geometry {
  public:
    using value_type = _Ty;
    using point_type = ns_geo::Point2<value_type>;
    using ary_type = std::array<point_type, 3>;
    using self_type = Triangle2<value_type>;

  private:
    point_type _p1;
    point_type _p2;
    point_type _p3;

  public:
    /**
     * @brief constructors
     */
    Triangle2() = default;
    Triangle2(const point_type &p1, const point_type &p2, const point_type &p3)
        : _p1(p1), _p2(p2), _p3(p3) {}
    Triangle2(const point_type points[3])
        : _p1(points[0]), _p2(points[1]), _p3(points[2]) {}
    Triangle2(const ary_type &points)
        : _p1(points[0]), _p2(points[1]), _p3(points[2]) {}
    Triangle2(value_type p1x, value_type p1y, value_type p2x, value_type p2y,
              value_type p3x, value_type p3y)
        : _p1(p1x, p1y), _p2(p2x, p2y), _p3(p3x, p3y) {}

    inline const point_type &p1() const { return this->_p1; }
    inline point_type &p1() { return this->_p1; }

    inline const point_type &p2() const { return this->_p2; }
    inline point_type &p2() { return this->_p2; }

    inline const point_type &p3() const { return this->_p3; }
    inline point_type &p3() { return this->_p3; }

    inline Line2<value_type> side12() const {
      return Line2<value_type>(_p1, _p2);
    }

    inline Line2<value_type> side13() const {
      return Line2<value_type>(_p1, _p3);
    }

    inline Line2<value_type> side23() const {
      return Line2<value_type>(_p2, _p3);
    }

    inline ary_type points() const {
      return ary_type{this->_p1, this->_p2, this->_p3};
    }

    inline float area() const {
      float v12_x = _p2.x() - _p1.x();
      float v12_y = _p2.y() - _p1.y();
      float v13_x = _p3.x() - _p1.x();
      float v13_y = _p3.y() - _p1.y();
      return std::abs(v12_x * v13_y - v12_y * v13_x) * 0.5;
    }

    inline float perimeter() const {
      return ns_geo::distance(_p1, _p2) + ns_geo::distance(_p1, _p3) +
             ns_geo::distance(_p2, _p3);
    }

    /**
     * @brief calculate the circumscribed circle of the triangle
     *
     * @return std::pair<Point2f, float> the center and the radius
     */
    std::pair<Point2f, float> circumCircle() const {
      auto x1 = _p1.x(), y1 = _p1.y();
      auto x2 = _p2.x(), y2 = _p2.y();
      auto x3 = _p3.x(), y3 = _p3.y();
      float a = ((y2 - y1) * (y3 * y3 - y1 * y1 + x3 * x3 - x1 * x1) -
                 (y3 - y1) * (y2 * y2 - y1 * y1 + x2 * x2 - x1 * x1)) /
                (2.0 * ((x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1)));
      float b = ((x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) -
                 (x3 - x1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)) /
                (2.0 * ((y3 - y1) * (x2 - x1) - (y2 - y1) * (x3 - x1)));
      float r = std::sqrt((x1 - a) * (x1 - a) + (y1 - b) * (y1 - b));
      return std::make_pair(Point2f(a, b), r);
    }

    /**
     * @brief calculate the inscribed circle of the triangle
     *
     * @return std::pair<Point2f, float> the center and the radius
     */
    std::pair<Point2f, float> inscribedCircle() const {
      float a = distance(_p3, _p2), b = distance(_p1, _p3),
            c = distance(_p1, _p2);
      float temp = 1.0 / (a + b + c);
      float x = (a * _p1.x() + b * _p2.x() + c * _p3.x()) * temp;
      float y = (a * _p1.y() + b * _p2.y() + c * _p3.y()) * temp;
      return std::make_pair(Point2f(x, y),
                            distance(Point2f(x, y), Line2f(_p1, _p2)));
    }

    inline virtual ns_geo::GeoType type() const override {
      return GeoType::TRIANGLE2D;
    }
  };
  /**
   * @brief overload operator "<<" for Triangle2<_Ty>
   */
  template <typename _Ty = float>
  std::ostream &operator<<(std::ostream &os, const Triangle2<_Ty> &tri) {
    os << '{';
    os << tri.p1() << ", ";
    os << tri.p2() << ", ";
    os << tri.p3() << '}';
    return os;
  }
#pragma endregion

#pragma region Triangle3

  /**
   * @brief a sample template class to describe the 3-dime triangles
   */
  template <typename _Ty = float>
  class Triangle3 : protected Geometry {
  public:
    using value_type = _Ty;
    using point_type = ns_geo::Point3<value_type>;
    using ary_type = std::array<point_type, 3>;
    using self_type = Triangle3<value_type>;

  private:
    point_type _p1;
    point_type _p2;
    point_type _p3;

  public:
    /**
     * @brief constructors
     */
    Triangle3() = default;
    Triangle3(const point_type &p1, const point_type &p2, const point_type &p3)
        : _p1(p1), _p2(p2), _p3(p3) {}
    Triangle3(const point_type points[3])
        : _p1(points[0]), _p2(points[1]), _p3(points[2]) {}
    Triangle3(const ary_type &points)
        : _p1(points[0]), _p2(points[1]), _p3(points[2]) {}
    Triangle3(value_type p1x, value_type p1y, value_type p1z, value_type p2x,
              value_type p2y, value_type p2z, value_type p3x, value_type p3y,
              value_type p3z)
        : _p1(p1x, p1y, p1z), _p2(p2x, p2y, p2z), _p3(p3x, p3y, p3z) {}

    inline const point_type &p1() const { return this->_p1; }
    inline point_type &p1() { return this->_p1; }

    inline const point_type &p2() const { return this->_p2; }
    inline point_type &p2() { return this->_p2; }

    inline const point_type &p3() const { return this->_p3; }
    inline point_type &p3() { return this->_p3; }

    inline Line3<value_type> side12() const {
      return Line3<value_type>(_p1, _p2);
    }

    inline Line3<value_type> side13() const {
      return Line3<value_type>(_p1, _p3);
    }

    inline Line3<value_type> side23() const {
      return Line3<value_type>(_p2, _p3);
    }

    inline ary_type points() const {
      return ary_type{this->_p1, this->_p2, this->_p3};
    }

    float area() const {
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

    inline float perimeter() const {
      return ns_geo::distance(_p1, _p2) + ns_geo::distance(_p1, _p3) +
             ns_geo::distance(_p2, _p3);
    }

    inline virtual ns_geo::GeoType type() const override {
      return GeoType::TRIANGLE3D;
    }
  };
  /**
   * @brief overload operator "<<" for Triangle3<_Ty>
   */
  template <typename _Ty = float>
  std::ostream &operator<<(std::ostream &os, const Triangle3<_Ty> &tri) {
    os << '{';
    os << tri.p1() << ", ";
    os << tri.p2() << ", ";
    os << tri.p3() << '}';
    return os;
  }
#pragma endregion

#pragma region RefTriangle2

  /**
   * @brief a sample template class to describe the 2-dime triangles
   */
  template <typename _Ty = float>
  class RefTriangle2 : protected Geometry {
  public:
    using value_type = _Ty;
    using id_type = uint;
    using refpoint_type = ns_geo::RefPoint2<value_type>;
    using refpointset_type = RefPointSet2<value_type>;
    using ary_type = std::array<refpoint_type, 3>;
    using self_type = RefTriangle2<value_type>;

  public:
    friend class RefPointSet2<value_type>;

  private:
    id_type _pid1;
    id_type _pid2;
    id_type _pid3;
    // thr reference point set's pointer
    const refpointset_type *const _rps;

  protected:
    /**
     * @brief constructors
     */
    RefTriangle2(const id_type &pid1, const id_type &pid2, const id_type &pid3,
                 const refpointset_type *const refpointset)
        : _pid1(pid1), _pid2(pid2), _pid3(pid3), _rps(refpointset) {}

    RefTriangle2() = delete;

  public:
    inline const refpointset_type *const refPointSet() const {
      return this->_rps;
    };

    operator Triangle2<value_type>() {
      return Triangle2<value_type>(this->p1(), this->p2(), this->p3());
    }

    inline const refpoint_type &p1() const { return this->_rps->at(_pid1); }

    inline const refpoint_type &p2() const { return this->_rps->at(_pid2); }

    inline const refpoint_type &p3() const { return this->_rps->at(_pid3); }

    inline const id_type &pid1() const { return this->_pid1; }

    inline const id_type &pid2() const { return this->_pid2; }

    inline const id_type &pid3() const { return this->_pid3; }

    inline RefLine2<value_type> side12() const {
      return this->_rps->createRefLine2(_pid1, _pid2);
    }

    inline RefLine2<value_type> side13() const {
      return this->_rps->createRefLine2(_pid1, _pid3);
    }

    inline RefLine2<value_type> side23() const {
      return this->_rps->createRefLine2(_pid2, _pid3);
    }

    inline ary_type refPoints() const {
      return ary_type{this->p1(), this->p2(), this->p3()};
    }

    inline float area() const {
      auto p1 = this->p1();
      auto p2 = this->p2();
      auto p3 = this->p3();
      float v12_x = p2.x() - p1.x();
      float v12_y = p2.y() - p1.y();
      float v13_x = p3.x() - p1.x();
      float v13_y = p3.y() - p1.y();
      return std::abs(v12_x * v13_y - v12_y * v13_x) * 0.5;
    }

    inline float perimeter() const {
      auto p1 = this->p1();
      auto p2 = this->p2();
      auto p3 = this->p3();
      return ns_geo::distance(p1, p2) + ns_geo::distance(p1, p3) +
             ns_geo::distance(p2, p3);
    }

    /**
     * @brief calculate the Circumscribed circle of the triangle
     *
     * @return std::pair<Point2f, float> the center and the radius
     */
    std::pair<Point2f, float> circumCircle() const {
      auto &p1 = this->p1(), p2 = this->p2(), p3 = this->p3();
      auto x1 = p1.x(), y1 = p1.y();
      auto x2 = p2.x(), y2 = p2.y();
      auto x3 = p3.x(), y3 = p3.y();
      float a = ((y2 - y1) * (y3 * y3 - y1 * y1 + x3 * x3 - x1 * x1) -
                 (y3 - y1) * (y2 * y2 - y1 * y1 + x2 * x2 - x1 * x1)) /
                (2.0 * ((x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1)));
      float b = ((x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) -
                 (x3 - x1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)) /
                (2.0 * ((y3 - y1) * (x2 - x1) - (y2 - y1) * (x3 - x1)));
      float r = std::sqrt((x1 - a) * (x1 - a) + (y1 - b) * (y1 - b));
      return std::make_pair(Point2f(a, b), r);
    }

    /**
     * @brief calculate the inscribed circle of the triangle
     *
     * @return std::pair<Point2f, float> the center and the radius
     */
    std::pair<Point2f, float> inscribedCircle() const {
      auto &p1 = this->p1(), p2 = this->p2(), p3 = this->p3();
      float a = distance(p3, p2), b = distance(p1, p3), c = distance(p1, p2);
      float temp = 1.0 / (a + b + c);
      float x = (a * p1.x() + b * p2.x() + c * p3.x()) * temp;
      float y = (a * p1.y() + b * p2.y() + c * p3.y()) * temp;
      return std::make_pair(Point2f(x, y),
                            distance(Point2f(x, y), Line2f(p1, p2)));
    }

    inline virtual ns_geo::GeoType type() const override {
      return GeoType::REFTRIANGLE2D;
    }
  };
  /**
   * @brief overload operator "<<" for RefTriangle2<_Ty>
   */
  template <typename _Ty = float>
  std::ostream &operator<<(std::ostream &os, const RefTriangle2<_Ty> &tri) {
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

#pragma region RefTriangle3

  /**
   * @brief a sample template class to describe the 3-dime triangles
   */
  template <typename _Ty = float>
  class RefTriangle3 : protected Geometry {
  public:
    using value_type = _Ty;
    using id_type = uint;
    using refpoint_type = ns_geo::RefPoint3<value_type>;
    using refpointset_type = RefPointSet3<value_type>;
    using ary_type = std::array<refpoint_type, 3>;
    using self_type = RefTriangle3<value_type>;

  public:
    friend class RefPointSet3<value_type>;

  private:
    id_type _pid1;
    id_type _pid2;
    id_type _pid3;
    // the reference point set's pointer
    const refpointset_type *const _rps;

  protected:
    /**
     * @brief constructors
     */
    RefTriangle3(const id_type &pid1, const id_type &pid2, const id_type &pid3,
                 const refpointset_type *const refpointset)
        : _pid1(pid1), _pid2(pid2), _pid3(pid3), _rps(refpointset) {}

    RefTriangle3() = delete;

  public:
    inline const refpointset_type *const refPointSet() const {
      return this->_rps;
    };

    operator Triangle3<value_type>() {
      return Triangle3<value_type>(this->p1(), this->p2(), this->p3());
    }

    inline const refpoint_type &p1() const { return this->_rps->at(_pid1); }

    inline const refpoint_type &p2() const { return this->_rps->at(_pid2); }

    inline const refpoint_type &p3() const { return this->_rps->at(_pid3); }

    inline const id_type &pid1() const { return this->_pid1; }

    inline const id_type &pid2() const { return this->_pid2; }

    inline const id_type &pid3() const { return this->_pid3; }

    inline RefLine3<value_type> side12() const {
      return this->_rps->createRefLine3(_pid1, _pid2);
    }

    inline RefLine3<value_type> side13() const {
      return this->_rps->createRefLine3(_pid1, _pid3);
    }

    inline RefLine3<value_type> side23() const {
      return this->_rps->createRefLine3(_pid2, _pid3);
    }

    inline ary_type refPoints() const {
      return ary_type{this->p1(), this->p2(), this->p3()};
    }

    float area() const {
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

    inline float perimeter() const {
      auto p1 = this->p1();
      auto p2 = this->p2();
      auto p3 = this->p3();
      return ns_geo::distance(p1, p2) + ns_geo::distance(p1, p3) +
             ns_geo::distance(p2, p3);
    }

    inline virtual ns_geo::GeoType type() const override {
      return GeoType::REFTRIANGLE3D;
    }
  };
  /**
   * @brief overload operator "<<" for RefTriangle3<_Ty>
   */
  template <typename _Ty = float>
  std::ostream &operator<<(std::ostream &os, const RefTriangle3<_Ty> &tri) {
    auto p1 = tri.p1();
    auto p2 = tri.p2();
    auto p3 = tri.p3();
    os << '{';
    os << p1.id() << ": [" << p1.x() << ", " << p1.y() << ", " << p1.z() << ']'
       << ", ";
    os << p2.id() << ": [" << p2.x() << ", " << p2.y() << ", " << p2.z() << ']'
       << ", ";
    os << p3.id() << ": [" << p3.x() << ", " << p3.y() << ", " << p3.z() << "]}";
    return os;
  }
#pragma endregion
} // namespace ns_geo
