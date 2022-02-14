#pragma once

/**
 * @file polygon.hpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 */

#include "point.hpp"

namespace ns_geo {
#pragma region Polygon

template <typename _Ty = float>
class Polygon : public PointSet2<_Ty>, protected Geometry {
 public:
  using value_type = _Ty;
  using pointset_type = PointSet2<value_type>;
  /**
   * @brief using pointset_type's constructors
   */
  using pointset_type::pointset_type;
  using self_type = Polygon<value_type>;

  inline float perimeter() const {
    float len = 0.0;
    for (auto iter = this->cbegin(); iter != --this->cend();)
      len += distance(*iter, *(iter++));
    len += distance(this->front(), this->back());
    return len;
  }

  inline float area() const {
    float S = 0.0;
    auto size = this->size();
    for (int i = 0; i != size; ++i) {
      auto &pi = this->at(i % size);
      auto &pii = this->at((i + 1) % size);
      S += (pi.x() * pii.y() - pii.x() * pi.y());
    }
    S = 0.5 * std::abs(S);
    return S;
  }

  inline virtual ns_geo::GeoType type() const override {
    return GeoType::POLYGON;
  }
};
/**
 * @brief overload operator "<<" for Polygon<_Ty>
 */
template <typename _Ty>
std::ostream &operator<<(std::ostream &os, const Polygon<_Ty> &polygon) {
  os << '{';
  for (auto iter = polygon.cbegin(); iter != --polygon.cend(); ++iter)
    os << *iter << ", ";
  os << polygon.back() << '}';
  return os;
}
#pragma endregion

#pragma region RefPolygon

template <typename _Ty = float>
class RefPolygon : public std::vector<uint>, protected Geometry {
 public:
  using value_type = _Ty;
  using id_type = uint;
  using refpoint_type = RefPoint2<value_type>;
  using pointidset_type = std::vector<id_type>;
  using refpointset_type = RefPointSet2<value_type>;
  using self_type = RefPolygon<value_type>;

 public:
  friend class RefPointSet2<value_type>;

 private:
  const refpointset_type *const _rps;

 protected:
  /**
   * @brief constructors
   */
  RefPolygon(const std::initializer_list<id_type> &pidls,
             const refpointset_type *const rps)
      : pointidset_type(pidls), _rps(rps) {}

  RefPolygon() = delete;

 public:
  inline const refpointset_type *const refPointSet() const {
    return this->_rps;
  };

  operator Polygon<value_type>() {
    Polygon<value_type> polygon;
    for (int i = 0; i != this->size(); ++i) polygon.push_back(this->indexAt(i));
    return polygon;
  }

  /**
   * @brief get the 'index'st reference point in the polygon
   *
   * @param index the index of the reference point's id in the polygon
   * @return const refpoint_type&
   */
  inline const refpoint_type &indexAt(std::size_t index) {
    return this->_rps->at(this->at(index));
  }

  /**
   * @brief get the 'id' reference point in the polygon's referenced refpointset
   *
   * @param id the id of the reference point
   * @return const refpoint_type&
   */
  inline const refpoint_type &idAt(std::size_t id) {
    return this->_rps->at(id);
  }

  inline const std::vector<uint> &pids() const { return *this; }

  inline float perimeter() const {
    float len = 0.0;
    int i = 0;
    for (auto iter = this->cbegin(); iter != --this->cend();) {
      auto curPoint = _rps->at(*iter);
      auto nextPoint = _rps->at(*(++iter));
      len += distance(curPoint, nextPoint);
    }
    len += distance(_rps->at(this->front()), _rps->at(this->back()));
    return len;
  }

  inline float area() const {
    float S = 0.0;
    auto size = this->size();
    for (int i = 0; i != size; ++i) {
      auto &pi = _rps->at(this->at(i % size));
      auto &pii = _rps->at(this->at((i + 1) % size));
      S += (pi.x() * pii.y() - pii.x() * pi.y());
    }
    S = 0.5 * std::abs(S);
    return S;
  }
  
  inline virtual ns_geo::GeoType type() const override {
    return GeoType::REFPOLYGON;
  }
};
/**
 * @brief overload operator "<<" for RefPolygon<_Ty>
 */
template <typename _Ty>
std::ostream &operator<<(std::ostream &os, const RefPolygon<_Ty> &polygon) {
  auto rps = polygon.refPointSet();
  os << '{';
  for (auto iter = polygon.cbegin(); iter != --polygon.cend(); ++iter) {
    auto &p = rps->at(*iter);
    os << p.id() << ": [" << p.x() << ", " << p.y() << ']' << ", ";
  }
  auto &p = rps->at(polygon.back());
  os << p.id() << ": [" << p.x() << ", " << p.y() << "]}";
  return os;
}
#pragma endregion
}  // namespace ns_geo
