#ifndef LINESTRING_HPP
#define LINESTRING_HPP

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

  template <typename Ty = float>
  class LineString2 : public PointSet2<Ty>, protected Geometry {
  public:
    using value_type = Ty;
    using pointset_type = PointSet2<value_type>;
    /**
     * @brief using point-set_type's constructors
     */
    using pointset_type::pointset_type;
    using self_type = LineString2<value_type>;

    [[nodiscard]] inline float length() const {
      float len = 0.0;
      for (auto iter = this->cbegin(); iter != --this->cend();)
        len += distance(*iter, *(iter++));
      return len;
    }

    [[nodiscard]] inline ns_geo::GeoType type() const override {
      return GeoType::LINESTRING2;
    }
  };
  /**
   * @brief overload operator "<<" for LineString2
   */
  template <typename Ty>
  std::ostream &operator<<(std::ostream &os, const LineString2<Ty> &ls) {
    os << '{';
    for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter)
      os << *iter << ", ";
    os << ls.back() << '}';
    return os;
  }
#pragma endregion

#pragma region LineString3

  template <typename Ty = float>
  class LineString3 : public PointSet3<Ty>, protected Geometry {
  public:
    using value_type = Ty;
    using pointset_type = PointSet3<value_type>;
    /**
     * @brief using point-set_type's constructors
     */
    using pointset_type::pointset_type;
    using self_type = LineString3<value_type>;

    [[nodiscard]] inline float length() const {
      float len = 0.0;
      for (auto iter = this->cbegin(); iter != --this->cend();)
        len += distance(*iter, *(iter++));
      return len;
    }

    [[nodiscard]] inline ns_geo::GeoType type() const override {
      return GeoType::LINESTRING3;
    }
  };
  /**
   * @brief overload operator "<<" for LineString3
   */
  template <typename Ty>
  std::ostream &operator<<(std::ostream &os, const LineString3<Ty> &ls) {
    os << '{';
    for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter)
      os << *iter << ", ";
    os << ls.back() << '}';
    return os;
  }
#pragma endregion

#pragma region RefLineString2

  template <typename Ty = float>
  class RefLineString2 : public std::vector<uint>, protected Geometry {
  public:
    using value_type = Ty;
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

  public:
    inline const refpointset_type *refPointSet() const {
      return this->_rps;
    };

    /**
     * @brief cast from 'RefLineString2<value_type>' to 'LineString2<value_type>'
     *
     * @return LineString2<value_type>
     */
    explicit operator LineString2<value_type>() {
      LineString2<value_type> linestring;
      for (int i = 0; i != this->size(); ++i)
        linestring.push_back(this->indexAt(i));
      return linestring;
    }
    /**
     * @brief get the 'index's reference point in the line string
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

    [[nodiscard]] inline const std::vector<uint> &pids() const { return *this; }

    [[nodiscard]] inline float length() const {
      float len = 0.0;
      for (auto iter = this->cbegin(); iter != --this->cend();)
        len += distance(_rps->at(*iter), _rps->at(*(iter++)));
      return len;
    }

    [[nodiscard]] inline ns_geo::GeoType type() const override {
      return GeoType::REF_LINESTRING2;
    }
  };
  /**
   * @brief overload operator "<<" for RefLineString2<_Ty>
   */
  template <typename Ty>
  std::ostream &operator<<(std::ostream &os, const RefLineString2<Ty> &ls) {
    auto rps = ls.refPointSet();
    os << '{';
    for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter) {
      auto &p = rps->at(*iter);
      os << p.id << ": [" << p.x << ", " << p.y << ']' << ", ";
    }
    auto &p = rps->at(ls.back());
    os << p.id << ": [" << p.x << ", " << p.y << "]}";
    return os;
  }
#pragma endregion

#pragma region RefLineString3

  template <typename Ty = float>
  class RefLineString3 : public std::vector<uint>, protected Geometry {
  public:
    using value_type = Ty;
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

  public:
    inline const refpointset_type *refPointSet() const {
      return this->_rps;
    };

    /**
     * @brief cast from 'RefLineString3<value_type>' to 'LineString3<value_type>'
     *
     * @return LineString3<value_type>
     */
    explicit operator LineString3<value_type>() {
      LineString3<value_type> linestring;
      for (int i = 0; i != this->size(); ++i)
        linestring.push_back(this->indexAt(i));
      return linestring;
    }

    /**
     * @brief get the 'index's reference point in the line string
     *
     * @param index the index of the reference point's id in the line string
     * @return const refpoint_type&
     */
    inline const refpoint_type &indexAt(std::size_t index) {
      return this->_rps->at(this->at(index));
    }

    /**
     * @brief get the 'id' reference point in the line string's referenced refPointSet
     *
     * @param id the id of the reference point
     * @return const refpoint_type&
     */
    inline const refpoint_type &idAt(std::size_t id) {
      return this->_rps->at(id);
    }

    [[nodiscard]] inline const std::vector<uint> &pids() const { return *this; }

    [[nodiscard]] inline float length() const {
      float len = 0.0;
      for (auto iter = this->cbegin(); iter != --this->cend();)
        len += distance(_rps->at(*iter), _rps->at(*(iter++)));
      return len;
    }

    [[nodiscard]] inline ns_geo::GeoType type() const override {
      return GeoType::REF_LINESTRING3;
    }
  };
  /**
   * @brief overload operator "<<" for RefLineString3<_Ty>
   */
  template <typename Ty>
  std::ostream &operator<<(std::ostream &os, const RefLineString3<Ty> &ls) {
    auto rps = ls.refPointSet();
    os << '{';
    for (auto iter = ls.cbegin(); iter != --ls.cend(); ++iter) {
      auto &p = rps->at(*iter);
      os << p.id << ": [" << p.x << ", " << p.y << ", " << p.z << ']'
         << ", ";
    }
    auto &p = rps->at(ls.back());
    os << p.id << ": [" << p.x << ", " << p.y << ", " << p.z << "]}";
    return os;
  }
#pragma endregion
} // namespace ns_geo

#endif