#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

/**
 * @file triangle.hpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 */

#include "circle.hpp"
#include "line.hpp"
#include "point.hpp"

namespace ns_geo {
#pragma region Triangle2

  /**
   * @brief a sample template class to describe the 2-dime triangles
   */
  template <typename Ty = float>
  class Triangle2 : protected Geometry {
  public:
    using value_type = Ty;
    using point_type = ns_geo::Point2<value_type>;
    using ary_type = std::array<point_type, 3>;
    using self_type = Triangle2<value_type>;

  public:
    point_type p1;
    point_type p2;
    point_type p3;

  public:
    /**
     * @brief constructors
     */
    Triangle2() = default;
    Triangle2(const point_type &p1, const point_type &p2, const point_type &p3)
        : p1(p1), p2(p2), p3(p3) {}
    explicit Triangle2(const point_type points[3])
        : p1(points[0]), p2(points[1]), p3(points[2]) {}
    explicit Triangle2(const ary_type &points)
        : p1(points[0]), p2(points[1]), p3(points[2]) {}
    Triangle2(value_type p1x, value_type p1y, value_type p2x, value_type p2y,
              value_type p3x, value_type p3y)
        : p1(p1x, p1y), p2(p2x, p2y), p3(p3x, p3y) {}

    inline Line2<value_type> side12() const {
      return Line2<value_type>(p1, p2);
    }

    inline Line2<value_type> side13() const {
      return Line2<value_type>(p1, p3);
    }

    inline Line2<value_type> side23() const {
      return Line2<value_type>(p2, p3);
    }

    inline ary_type points() const {
      return ary_type{this->p1, this->p2, this->p3};
    }

    [[nodiscard]] inline float area() const {
      float v12_x = p2.x - p1.x;
      float v12_y = p2.y - p1.y;
      float v13_x = p3.x - p1.x;
      float v13_y = p3.y - p1.y;
      return std::abs(v12_x * v13_y - v12_y * v13_x) * 0.5f;
    }

    [[nodiscard]] inline float perimeter() const {
      return ns_geo::distance(p1, p2) + ns_geo::distance(p1, p3) +
             ns_geo::distance(p2, p3);
    }

    /**
     * @brief calculate the circumscribed circle of the triangle
     *
     * @return std::pair<Point2f, float> the center and the radius
     */
    [[nodiscard]] ns_geo::Circle circumCircle() const {
      auto x1 = p1.x, y1 = p1.y;
      auto x2 = p2.x, y2 = p2.y;
      auto x3 = p3.x, y3 = p3.y;
      float a = ((y2 - y1) * (y3 * y3 - y1 * y1 + x3 * x3 - x1 * x1) -
                 (y3 - y1) * (y2 * y2 - y1 * y1 + x2 * x2 - x1 * x1)) /
                (2.0 * ((x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1)));
      float b = ((x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) -
                 (x3 - x1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)) /
                (2.0 * ((y3 - y1) * (x2 - x1) - (y2 - y1) * (x3 - x1)));
      float r = std::sqrt((x1 - a) * (x1 - a) + (y1 - b) * (y1 - b));
      // return std::make_pair(Point2f(a, b), r);
      return ns_geo::Circle({a, b}, r);
    }

    /**
     * @brief calculate the inscribed circle of the triangle
     *
     * @return std::pair<Point2f, float> the center and the radius
     */
    [[nodiscard]] ns_geo::Circle inscribedCircle() const {
      float a = distance(p3, p2), b = distance(p1, p3),
            c = distance(p1, p2);
      float temp = 1.0f / (a + b + c);
      float x = (a * p1.x + b * p2.x + c * p3.x) * temp;
      float y = (a * p1.y + b * p2.y + c * p3.y) * temp;
      return ns_geo::Circle(Point2d(x, y), distance(Point2d(x, y), Line2d({p1.x, p1.y}, {p2.x, p2.y})));
    }

    [[nodiscard]] inline ns_geo::GeoType type() const override {
      return GeoType::TRIANGLE2;
    }
  };
  /**
   * @brief overload operator "<<" for Triangle2<_Ty>
   */
  template <typename Ty = float>
  std::ostream &operator<<(std::ostream &os, const Triangle2<Ty> &tri) {
    os << '{';
    os << tri.p1 << ", ";
    os << tri.p2 << ", ";
    os << tri.p3 << '}';
    return os;
  }
#pragma endregion

#pragma region Triangle3

  /**
   * @brief a sample template class to describe the 3-dime triangles
   */
  template <typename Ty = float>
  class Triangle3 : protected Geometry {
  public:
    using value_type = Ty;
    using point_type = ns_geo::Point3<value_type>;
    using ary_type = std::array<point_type, 3>;
    using self_type = Triangle3<value_type>;

  public:
    point_type p1;
    point_type p2;
    point_type p3;

  public:
    /**
     * @brief constructors
     */
    Triangle3() = default;
    Triangle3(const point_type &p1, const point_type &p2, const point_type &p3)
        : p1(p1), p2(p2), p3(p3) {}
    explicit Triangle3(const point_type points[3])
        : p1(points[0]), p2(points[1]), p3(points[2]) {}
    explicit Triangle3(const ary_type &points)
        : p1(points[0]), p2(points[1]), p3(points[2]) {}
    Triangle3(value_type p1x, value_type p1y, value_type p1z, value_type p2x,
              value_type p2y, value_type p2z, value_type p3x, value_type p3y,
              value_type p3z)
        : p1(p1x, p1y, p1z), p2(p2x, p2y, p2z), p3(p3x, p3y, p3z) {}

    inline Line3<value_type> side12() const {
      return Line3<value_type>(p1, p2);
    }

    inline Line3<value_type> side13() const {
      return Line3<value_type>(p1, p3);
    }

    inline Line3<value_type> side23() const {
      return Line3<value_type>(p2, p3);
    }

    inline ary_type points() const {
      return ary_type{this->p1, this->p2, this->p3};
    }

    [[nodiscard]] float area() const {
      float v12_x = p2.x - p1.x;
      float v12_y = p2.y - p1.y;
      float v12_z = p2.z - p1.z;
      float v13_x = p3.x - p1.x;
      float v13_y = p3.y - p1.y;
      float v13_z = p3.z - p1.z;
      auto val1 = std::pow(v12_y * v13_z - v12_z * v13_y, 2);
      auto val2 = std::pow(v13_x * v12_z - v12_x * v13_z, 2);
      auto val3 = std::pow(v12_x * v13_y - v12_y * v13_x, 2);
      return std::sqrt(val1 + val2 + val3) * 0.5f;
    }

    [[nodiscard]] inline float perimeter() const {
      return ns_geo::distance(p1, p2) + ns_geo::distance(p1, p3) +
             ns_geo::distance(p2, p3);
    }

    [[nodiscard]] inline ns_geo::GeoType type() const override {
      return GeoType::TRIANGLE3;
    }
  };
  /**
   * @brief overload operator "<<" for Triangle3<_Ty>
   */
  template <typename Ty = float>
  std::ostream &operator<<(std::ostream &os, const Triangle3<Ty> &tri) {
    os << '{';
    os << tri.p1 << ", ";
    os << tri.p2 << ", ";
    os << tri.p3 << '}';
    return os;
  }
#pragma endregion

#pragma region RefTriangle2

  /**
   * @brief a sample template class to describe the 2-dime triangles
   */
  template <typename Ty = float>
  class RefTriangle2 : protected Geometry {
  public:
    using value_type = Ty;
    using id_type = uint;
    using refpoint_type = ns_geo::RefPoint2<value_type>;
    using refpointset_type = RefPointSet2<value_type>;
    using ary_type = std::array<refpoint_type, 3>;
    using self_type = RefTriangle2<value_type>;

  public:
    friend class RefPointSet2<value_type>;

  public:
    id_type pid1;
    id_type pid2;
    id_type pid3;
    // thr reference point set's pointer
    const refpointset_type *const _rps;

  protected:
    /**
     * @brief constructors
     */
    RefTriangle2(const id_type &pid1, const id_type &pid2, const id_type &pid3,
                 const refpointset_type *const refpointset)
        : pid1(pid1), pid2(pid2), pid3(pid3), _rps(refpointset) {}

  public:
    inline const refpointset_type *refPointSet() const {
      return this->_rps;
    };

    explicit operator Triangle2<value_type>() {
      return Triangle2<value_type>(this->p1(), this->p2(), this->p3());
    }

    inline const refpoint_type &p1() const { return this->_rps->at(pid1); }

    inline const refpoint_type &p2() const { return this->_rps->at(pid2); }

    inline const refpoint_type &p3() const { return this->_rps->at(pid3); }

    inline RefLine2<value_type> side12() const {
      return this->_rps->createRefLine2(pid1, pid2);
    }

    inline RefLine2<value_type> side13() const {
      return this->_rps->createRefLine2(pid1, pid3);
    }

    inline RefLine2<value_type> side23() const {
      return this->_rps->createRefLine2(pid2, pid3);
    }

    inline ary_type refPoints() const {
      return ary_type{this->p1(), this->p2(), this->p3()};
    }

    [[nodiscard]] inline float area() const {
      auto p1 = this->p1();
      auto p2 = this->p2();
      auto p3 = this->p3();
      float v12_x = p2.x - p1.x;
      float v12_y = p2.y - p1.y;
      float v13_x = p3.x - p1.x;
      float v13_y = p3.y - p1.y;
      return std::abs(v12_x * v13_y - v12_y * v13_x) * 0.5f;
    }

    [[nodiscard]] inline float perimeter() const {
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
    [[nodiscard]] ns_geo::Circle circumCircle() const {
      auto &p1 = this->p1(), p2 = this->p2(), p3 = this->p3();
      auto x1 = p1.x, y1 = p1.y;
      auto x2 = p2.x, y2 = p2.y;
      auto x3 = p3.x, y3 = p3.y;
      float a = ((y2 - y1) * (y3 * y3 - y1 * y1 + x3 * x3 - x1 * x1) -
                 (y3 - y1) * (y2 * y2 - y1 * y1 + x2 * x2 - x1 * x1)) /
                (2.0 * ((x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1)));
      float b = ((x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) -
                 (x3 - x1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)) /
                (2.0 * ((y3 - y1) * (x2 - x1) - (y2 - y1) * (x3 - x1)));
      float r = std::sqrt((x1 - a) * (x1 - a) + (y1 - b) * (y1 - b));
      return ns_geo::Circle(Point2d(a, b), r);
    }

    /**
     * @brief calculate the inscribed circle of the triangle
     *
     * @return std::pair<Point2f, float> the center and the radius
     */
    [[nodiscard]] ns_geo::Circle inscribedCircle() const {
      auto &p1 = this->p1(), p2 = this->p2(), p3 = this->p3();
      float a = distance(p3, p2), b = distance(p1, p3), c = distance(p1, p2);
      float temp = 1.0f / (a + b + c);
      float x = (a * p1.x + b * p2.x + c * p3.x) * temp;
      float y = (a * p1.y + b * p2.y + c * p3.y) * temp;
      return ns_geo::Circle(Point2d(x, y), distance(Point2d(x, y), Line2d({p1.x, p1.y}, {p2.x, p2.y})));
    }

    [[nodiscard]] inline ns_geo::GeoType type() const override {
      return GeoType::REF_TRIANGLE2;
    }
  };
  /**
   * @brief overload operator "<<" for RefTriangle2<_Ty>
   */
  template <typename Ty = float>
  std::ostream &operator<<(std::ostream &os, const RefTriangle2<Ty> &tri) {
    auto p1 = tri.p1();
    auto p2 = tri.p2();
    auto p3 = tri.p3();
    os << '{';
    os << p1.id << ": [" << p1.x << ", " << p1.y << ']' << ", ";
    os << p2.id << ": [" << p2.x << ", " << p2.y << ']' << ", ";
    os << p3.id << ": [" << p3.x << ", " << p3.y << "]}";
    return os;
  }
#pragma endregion

#pragma region RefTriangle3

  /**
   * @brief a sample template class to describe the 3-dime triangles
   */
  template <typename Ty = float>
  class RefTriangle3 : protected Geometry {
  public:
    using value_type = Ty;
    using id_type = uint;
    using refpoint_type = ns_geo::RefPoint3<value_type>;
    using refpointset_type = RefPointSet3<value_type>;
    using ary_type = std::array<refpoint_type, 3>;
    using self_type = RefTriangle3<value_type>;

  public:
    friend class RefPointSet3<value_type>;

  public:
    id_type pid1;
    id_type pid2;
    id_type pid3;
    // the reference point set's pointer
    const refpointset_type *const _rps;

  protected:
    /**
     * @brief constructors
     */
    RefTriangle3(const id_type &pid1, const id_type &pid2, const id_type &pid3,
                 const refpointset_type *const refpointset)
        : pid1(pid1), pid2(pid2), pid3(pid3), _rps(refpointset) {}

  public:
    inline const refpointset_type *refPointSet() const {
      return this->_rps;
    };

    explicit operator Triangle3<value_type>() {
      return Triangle3<value_type>(this->p1(), this->p2(), this->p3());
    }

    inline const refpoint_type &p1() const { return this->_rps->at(pid1); }

    inline const refpoint_type &p2() const { return this->_rps->at(pid2); }

    inline const refpoint_type &p3() const { return this->_rps->at(pid3); }

    inline RefLine3<value_type> side12() const {
      return this->_rps->createRefLine3(pid1, pid2);
    }

    inline RefLine3<value_type> side13() const {
      return this->_rps->createRefLine3(pid1, pid3);
    }

    inline RefLine3<value_type> side23() const {
      return this->_rps->createRefLine3(pid2, pid3);
    }

    inline ary_type refPoints() const {
      return ary_type{this->p1(), this->p2(), this->p3()};
    }

    [[nodiscard]] float area() const {
      auto p1 = this->p1();
      auto p2 = this->p2();
      auto p3 = this->p3();
      float v12_x = p2.x - p1.x;
      float v12_y = p2.y - p1.y;
      float v12_z = p2.z - p1.z;
      float v13_x = p3.x - p1.x;
      float v13_y = p3.y - p1.y;
      float v13_z = p3.z - p1.z;
      auto val1 = std::pow(v12_y * v13_z - v12_z * v13_y, 2);
      auto val2 = std::pow(v13_x * v12_z - v12_x * v13_z, 2);
      auto val3 = std::pow(v12_x * v13_y - v12_y * v13_x, 2);
      return (float)(std::sqrt(val1 + val2 + val3) * 0.5);
    }

    [[nodiscard]] inline float perimeter() const {
      auto p1 = this->p1();
      auto p2 = this->p2();
      auto p3 = this->p3();
      return ns_geo::distance(p1, p2) + ns_geo::distance(p1, p3) +
             ns_geo::distance(p2, p3);
    }

    [[nodiscard]] inline ns_geo::GeoType type() const override {
      return GeoType::REF_TRIANGLE3;
    }
  };
  /**
   * @brief overload operator "<<" for RefTriangle3<_Ty>
   */
  template <typename Ty = float>
  std::ostream &operator<<(std::ostream &os, const RefTriangle3<Ty> &tri) {
    auto p1 = tri.p1();
    auto p2 = tri.p2();
    auto p3 = tri.p3();
    os << '{';
    os << p1.id << ": [" << p1.x << ", " << p1.y << ", " << p1.z << ']'
       << ", ";
    os << p2.id << ": [" << p2.x << ", " << p2.y << ", " << p2.z << ']'
       << ", ";
    os << p3.id << ": [" << p3.x << ", " << p3.y << ", " << p3.z << "]}";
    return os;
  }
#pragma endregion
} // namespace ns_geo

#endif