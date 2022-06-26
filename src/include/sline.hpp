#ifndef SLINE_HPP
#define SLINE_HPP

#include "eigen3/Eigen/Dense"
#include "point.hpp"
#include "sample.hpp"

namespace ns_geo {
  class SLine2 : protected Geometry {
  public:
    using value_type = double;
    using point_type = Point2<value_type>;
    using self_type = SLine2;
    using pointset_type = PointSet2<value_type>;

  public:
    /**
     * @brief the members
     */
    value_type a;
    value_type b;
    value_type c;

  public:
    /**
     * @brief construct a new self_type object
     */
    SLine2(const value_type &a, const value_type &b, const value_type &c) {
      // normalize
      value_type norm = std::sqrt(a * a + b * b + c * c);
      this->a = a / norm;
      this->b = b / norm;
      this->c = c / norm;
    }

    SLine2(const point_type &p1, const point_type &p2) {
      Eigen::MatrixXd A(2, 3);
      A(0, 0) = p1.x, A(0, 1) = p1.y, A(0, 2) = 1;
      A(1, 0) = p2.x, A(1, 1) = p2.y, A(1, 2) = 1;
      Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeFullV);
      Eigen::Matrix3d vMatrix = svd.matrixV();
      Eigen::Vector3d param = vMatrix.col(vMatrix.cols() - 1);
      a = param(0), b = param(1), c = param(2);
    }

    // Fit lines from points
    static self_type fit(const pointset_type &pts, const ushort iter = 10) {
      // ransac
      self_type l = self_type::ransac(pts, iter);
      // gauss newton [assign init value]
      value_type k = -l.a / l.b, b = -l.c / l.b;
      for (int i = 0; i != iter; ++i) {
        Eigen::Matrix2d H = Eigen::Matrix2d::Zero();
        Eigen::Vector2d g = Eigen::Vector2d::Zero();
        for (const auto &p : pts) {
          value_type x = p.x, y = p.y;
          value_type d = (k * x - y + b) / std::sqrt(k * k + 1.0);
          value_type jk = (x * (k * k + 1.0) - k * (k * x - y + b)) / std::pow(k * k + 1, 1.5);
          value_type jb = 1.0 / std::sqrt(k * k + 1.0);
          Eigen::Vector2d j(jk, jb);
          H += j * j.transpose();
          g -= j * d;
        }
        auto delta = H.ldlt().solve(g);
        k += delta(0);
        b += delta(1);
      }
      return self_type(k, -1.0, b);
    }

    static self_type ransac(const pointset_type &pts, const ushort iter = 10) {
      std::vector<std::pair<self_type, value_type>> lines;
      std::default_random_engine e;
      for (int i = 0; i != iter; ++i) {
        auto tp = samplingWoutReplace(e, pts, 2);
        self_type l(pts[tp[0]], pts[tp[1]]);
        value_type error = 0.0;
        for (const auto &p : pts) {
          error += l.distance(p);
        }
        lines.push_back({l, error});
      }
      auto tar = std::min_element(lines.cbegin(), lines.cend(),
                                  [](const std::pair<self_type, value_type> &p1, const std::pair<self_type, value_type> &p2) {
                                    return p1.second < p2.second;
                                  });
      return tar->first;
    }

    // Solve the nearest point from the target point to the line
    point_type nearest(const point_type &p) const {
      Eigen::Matrix2d A;
      A(0, 0) = b, A(0, 1) = -a;
      A(1, 0) = a, A(1, 1) = b;

      Eigen::Vector2d l;
      l(0) = b * p.x - a * p.y;
      l(1) = -c;

      Eigen::Vector2d np = A.inverse() * l;
      return point_type(np(0), np(1));
    }

    // Solve the distance from the point to the line
    value_type distance(const point_type &p) const {
      value_type v1 = std::abs(a * p.x + b * p.y + c);
      value_type v2 = std::sqrt(a * a + b * b);
      return v1 / v2;
    }

    [[nodiscard]] inline ns_geo::GeoType type() const override {
      return GeoType::SLINE2;
    }
  };
  /**
   * @brief override operator '<<' for type 'self_type'
   */
  std::ostream &operator<<(std::ostream &os, const SLine2 &sl) {
    os << '[' << sl.a << ", " << sl.b << ", " << sl.c << ']';
    return os;
  }

} // namespace ns_section

#endif