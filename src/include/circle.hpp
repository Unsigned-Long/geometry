#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "eigen3/Eigen/Dense"
#include "point.hpp"
#include "sample.hpp"

namespace ns_geo {
  template <typename Ty = float>
  class Circle : protected Geometry {
  public:
    using value_type = Ty;
    using point_type = ns_geo::Point2<value_type>;
    using self_type = Circle<value_type>;
    using pointset_type = PointSet2<value_type>;

  public:
    /**
     * @brief the members
     */
    point_type cen;
    value_type rad;

  public:
    /**
     * @brief construct a new Circle object
     */
    Circle(const point_type &cen, const value_type &rad) : cen(cen), rad(rad) {}
    /**
     * @brief Construct a new Circle object from three points
     */
    Circle(const point_type &p1, const point_type &p2, const point_type &p3) {
      double x2 = p2.x - p1.x, y2 = p2.y - p1.y;
      double x3 = p3.x - p1.x, y3 = p3.y - p1.y;
      double r2 = x2 * x2 + y2 * y2, r3 = x3 * x3 + y3 * y3;
      cen.x = (y3 * r2 - y2 * r3) / (2.0 * (x2 * y3 - y2 * x3)) + p1.x;
      cen.y = (x2 * r3 - x3 * r2) / (2.0 * (x2 * y3 - y2 * x3)) + p1.y;
      rad = ns_geo::distance(cen, p1);
    }

    // Calculate the distance from a point to the nearest point on the circle
    float distance(const point_type &p) const {
      return ns_geo::distance(nearest(p), p);
    }

    // find the nearest point on the circle
    point_type nearest(const point_type &p) const {
      double deltaX = p.x - cen.x, deltaY = p.y - cen.y;
      double theta = std::atan2(deltaY, deltaX);
      if (deltaY < 0.0) {
        theta += 2.0 * M_PI;
      }
      point_type target;
      target.x = rad * std::cos(theta) + cen.x;
      target.y = rad * std::sin(theta) + cen.y;
      return target;
    }

    // using gauss-newton method to fit a circle
    static self_type fit(const pointset_type &points, const ushort iter = 10) {
      auto cir = Circle::ransac(points);
      for (int i = 0; i != iter; ++i) {
        Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
        Eigen::Vector3d g = Eigen::Vector3d::Zero();
        for (const auto &p : points) {
          double dis = ns_geo::distance(p, cir.cen);
          double error = dis - cir.rad;
          Eigen::Vector3d j(-(p.x - cir.cen.x) / dis, -(p.y - cir.cen.y) / dis, -1.0);
          H += j * j.transpose();
          g -= j * error;
        }
        Eigen::Vector3d delta = H.ldlt().solve(g);
        cir.cen.x += delta(0);
        cir.cen.y += delta(1);
        cir.rad += delta(2);
      }
      return cir;
    }

    // using ransac method to find a circle
    static self_type ransac(const pointset_type &points, const ushort num = 10) {
      std::vector<std::pair<Circle, double>> samples;
      std::default_random_engine engine;
      for (int i = 0; i != num; ++i) {
        auto vec = ns_geo::samplingWoutReplace2(engine, points, 3);
        // construct the circle and compute the error
        Circle curCir(vec[0], vec[1], vec[2]);
        double error = 0.0;
        for (const auto &p : points) {
          error += curCir.distance(p);
        }
        samples.push_back({curCir, error});
      }
      // find the circle whose error is min
      auto iter = std::min_element(samples.cbegin(), samples.cend(),
                                   [](const std::pair<Circle, double> &p1, const std::pair<Circle, double> &p2) {
                                     return p1.second < p2.second;
                                   });
      return iter->first;
    }

    [[nodiscard]] inline ns_geo::GeoType type() const override {
      return GeoType::CIRCLE;
    }
  };
  /**
   * @brief override operator '<<' for type 'Circle'
   */
  template <typename Ty = float>
  std::ostream &operator<<(std::ostream &os, const Circle<Ty> &cir) {
    os << "[[" << cir.cen.x << ", " << cir.cen.y << "], " << cir.rad << ']';
    return os;
  }

} // namespace ns_geo

#endif