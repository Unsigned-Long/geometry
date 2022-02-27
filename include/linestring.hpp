#pragma once

/**
 * @file linestring.hpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 */

#include "point.hpp"

namespace ns_geo {
#pragma region LineString2

  template <typename _Ty = float>
  class LineString2 : public PointSet2<_Ty>, protected Geometry {
  public:
    using value_type = _Ty;
    using pointset_type = PointSet2<value_type>;
    /**
     * @brief using pointset_type's constructors
     */
    using pointset_type::pointset_type;
    using self_type = LineString2<value_type>;

    inline float length() const {
      float len = 0.0;
      for (auto iter = this->cbegin(); iter != --this->cend();)
        len += distance(*iter, *(iter++));
      return len;
    }

    inline virtual ns_geo::GeoType type() const override {
      return GeoType::LINESTRING2D;
    }
  };
  /**
   * @brief overload operator "<<" for LineString2
   */
  template <typename _Ty>
  std::ostream &operator<<(std::ostream &os, const LineString2<_Ty> &ls) {
    os << '{';
    for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter)
      os << *iter << ", ";
    os << ls.back() << '}';
    return os;
  }
#pragma endregion

#pragma region LineString3

  template <typename _Ty = float>
  class LineString3 : public PointSet3<_Ty>, protected Geometry {
  public:
    using value_type = _Ty;
    using pointset_type = PointSet3<value_type>;
    /**
     * @brief using pointset_type's constructors
     */
    using pointset_type::pointset_type;
    using self_type = LineString3<value_type>;

    inline float length() const {
      float len = 0.0;
      for (auto iter = this->cbegin(); iter != --this->cend();)
        len += distance(*iter, *(iter++));
      return len;
    }

    inline virtual ns_geo::GeoType type() const override {
      return GeoType::LINESTRING3D;
    }
  };
  /**
   * @brief overload operator "<<" for LineString3
   */
  template <typename _Ty>
  std::ostream &operator<<(std::ostream &os, const LineString3<_Ty> &ls) {
    os << '{';
    for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter)
      os << *iter << ", ";
    os << ls.back() << '}';
    return os;
  }
#pragma endregion

#pragma region RefLineString2

  template <typename _Ty = float>
  class RefLineString2 : public std::vector<uint>, protected Geometry {
  public:
    using value_type = _Ty;
    using id_type = uint;
    using refpoint_type = RefPoint2<value_type>;
    using pointidset_type = std::vector<id_type>;
    using refpointset_type = RefPointSet2<value_type>;
    using self_type = RefLineString2<value_type>;

  public:
    friend class RefPointSet2<value_type>;

  private:
    const refpointset_type *const _rps;

  protected:
    /**
     * @brief constructors
     */
    RefLineString2(const std::initializer_list<id_type> &pidls,
                   const refpointset_type *const rps)
        : pointidset_type(pidls), _rps(rps) {}

    RefLineString2() = delete;

  public:
    inline const refpointset_type *const refPointSet() const {
      return this->_rps;
    };

    /**
     * @brief cast from 'RefLineString2<value_type>' to 'LineString2<value_type>'
     *
     * @return LineString2<value_type>
     */
    operator LineString2<value_type>() {
      LineString2<value_type> linestring;
      for (int i = 0; i != this->size(); ++i)
        linestring.push_back(this->indexAt(i));
      return linestring;
    }
    /**
     * @brief get the 'index'st reference point in the line string
     *
     * @param index the index of the reference point's id in the line string
     * @return const refpoint_type&
     */
    inline const refpoint_type &indexAt(std::size_t index) {
      return this->_rps->at(this->at(index));
    }

    /**
     * @brief get the 'id' reference point in the line string's referenced
     * refpointset
     *
     * @param id the id of the reference point
     * @return const refpoint_type&
     */
    inline const refpoint_type &idAt(std::size_t id) {
      return this->_rps->at(id);
    }

    inline const std::vector<uint> &pids() const { return *this; }

    inline float length() const {
      float len = 0.0;
      for (auto iter = this->cbegin(); iter != --this->cend();)
        len += distance(_rps->at(*iter), _rps->at(*(iter++)));
      return len;
    }

    inline virtual ns_geo::GeoType type() const override {
      return GeoType::REFLINESTRING2D;
    }
  };
  /**
   * @brief overload operator "<<" for RefLineString2<_Ty>
   */
  template <typename _Ty>
  std::ostream &operator<<(std::ostream &os, const RefLineString2<_Ty> &ls) {
    auto rps = ls.refPointSet();
    os << '{';
    for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter) {
      auto &p = rps->at(*iter);
      os << p.id() << ": [" << p.x() << ", " << p.y() << ']' << ", ";
    }
    auto &p = rps->at(ls.back());
    os << p.id() << ": [" << p.x() << ", " << p.y() << "]}";
    return os;
  }
#pragma endregion

#pragma region RefLineString3

  template <typename _Ty = float>
  class RefLineString3 : public std::vector<uint>, protected Geometry {
  public:
    using value_type = _Ty;
    using id_type = uint;
    using refpoint_type = RefPoint3<value_type>;
    using pointidset_type = std::vector<id_type>;
    using refpointset_type = RefPointSet3<value_type>;
    using self_type = RefLineString3<value_type>;

  public:
    friend class RefPointSet3<value_type>;

  private:
    const refpointset_type *const _rps;

  protected:
    /**
     * @brief constructors
     */
    RefLineString3(const std::initializer_list<id_type> &pidls,
                   const refpointset_type *const rps)
        : pointidset_type(pidls), _rps(rps) {}

    RefLineString3() = delete;

  public:
    inline const refpointset_type *const refPointSet() const {
      return this->_rps;
    };

    /**
     * @brief cast from 'RefLineString3<value_type>' to 'LineString3<value_type>'
     *
     * @return LineString3<value_type>
     */
    operator LineString3<value_type>() {
      LineString3<value_type> linestring;
      for (int i = 0; i != this->size(); ++i)
        linestring.push_back(this->indexAt(i));
      return linestring;
    }

    /**
     * @brief get the 'index'st reference point in the line string
     *
     * @param index the index of the reference point's id in the line string
     * @return const refpoint_type&
     */
    inline const refpoint_type &indexAt(std::size_t index) {
      return this->_rps->at(this->at(index));
    }

    /**
     * @brief get the 'id' reference point in the line string's referenced
     * refpointset
     *
     * @param id the id of the reference point
     * @return const refpoint_type&
     */
    inline const refpoint_type &idAt(std::size_t id) {
      return this->_rps->at(id);
    }

    inline const std::vector<uint> &pids() const { return *this; }

    inline float length() const {
      float len = 0.0;
      for (auto iter = this->cbegin(); iter != --this->cend();)
        len += distance(_rps->at(*iter), _rps->at(*(iter++)));
      return len;
    }

    inline virtual ns_geo::GeoType type() const override {
      return GeoType::REFLINESTRING3D;
    }
  };
  /**
   * @brief overload operator "<<" for RefLineString3<_Ty>
   */
  template <typename _Ty>
  std::ostream &operator<<(std::ostream &os, const RefLineString3<_Ty> &ls) {
    auto rps = ls.refPointSet();
    os << '{';
    for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter) {
      auto &p = rps->at(*iter);
      os << p.id() << ": [" << p.x() << ", " << p.y() << ", " << p.z() << ']'
         << ", ";
    }
    auto &p = rps->at(ls.back());
    os << p.id() << ": [" << p.x() << ", " << p.y() << ", " << p.z() << "]}";
    return os;
  }
#pragma endregion
} // namespace ns_geo
