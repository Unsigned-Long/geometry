#pragma once

#include "artwork/geometry/line.hpp"
#include "artwork/geometry/linestring.hpp"
#include "artwork/geometry/point.hpp"
#include "artwork/geometry/polygon.hpp"
#include "artwork/geometry/rectangle.hpp"
#include "artwork/geometry/triangle.hpp"

#include "artwork/logger/logger.h"

TEST(ostream, geo_ostream) {
  ns_geo::Point2f p2f(1, 2);
  LOG_VAR(p2f);
  ns_geo::Point3f p3f(1, 3, 4);
  LOG_VAR(p3f);
  ns_geo::Line2f line2f(p2f, p2f);
  LOG_VAR(line2f);
  ns_geo::Line3f line3f(p3f, p3f);
  LOG_VAR(line3f);
  ns_geo::LineString2f ls2f{p2f, p2f};
  LOG_VAR(ls2f);
  ns_geo::LineString3f ls3f{p3f, p3f};
  LOG_VAR(ls3f);
  ns_geo::Polygonf ply{p2f, p2f, p2f};
  LOG_VAR(ply);
  ns_geo::Rectanglef rect(p2f, p2f);
  LOG_VAR(rect);
  ns_geo::Triangle2f tri2f(p2f, p2f, p2f);
  LOG_VAR(tri2f);
  ns_geo::Triangle3f tri3f(p3f, p3f, p3f);
  LOG_VAR(tri3f);

  ns_geo::RefPoint2f rp2f(0, 1, 2);
  LOG_VAR(rp2f);
  ns_geo::RefPoint3f rp3f(0, 1, 2, 3);
  LOG_VAR(rp3f);

  ns_geo::RefPointSet2f rps2f;
  rps2f.insert(rp2f);
  LOG_VAR(rps2f.createRefLine2(0, 0));
  LOG_VAR(rps2f.createRefLineString2({0, 0, 0}));
  LOG_VAR(rps2f.createRefPolygon({0, 0, 0}));
  LOG_VAR(rps2f.createRefRectangle(0, 0));
  LOG_VAR(rps2f.createRefTriangle2(0, 0, 0));

  ns_geo::RefPointSet3f rps3f;
  rps3f.insert(rp3f);
  LOG_VAR(rps3f.createRefLine3(0, 0));
  LOG_VAR(rps3f.createRefLineString3({0, 0, 0}));
  LOG_VAR(rps3f.createRefTriangle3(0, 0, 0));
  ASSERT_TRUE(std::cout.good());
}
