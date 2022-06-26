#ifndef HELPER_H
#define HELPER_H

/**
 * @file helper.h
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "include/point.hpp"
#include "gtest/gtest.h"

#pragma region help mathods

void test_point2f_eq(const ns_geo::Point2f &p1, const ns_geo::Point2f &p2) {
  EXPECT_FLOAT_EQ(p1.x, p2.x);
  EXPECT_FLOAT_EQ(p1.y, p2.y);
}

void test_point3f_eq(const ns_geo::Point3f &p1, const ns_geo::Point3f &p2) {
  EXPECT_FLOAT_EQ(p1.x, p2.x);
  EXPECT_FLOAT_EQ(p1.y, p2.y);
  EXPECT_FLOAT_EQ(p1.z, p2.z);
}

void test_refpoint2f_eq(const ns_geo::RefPoint2f &p1,
                        const ns_geo::RefPoint2f &p2) {
  EXPECT_EQ(p1.id, p2.id);
  EXPECT_FLOAT_EQ(p1.x, p2.x);
  EXPECT_FLOAT_EQ(p1.y, p2.y);
  return;
}

void test_refpoint3f_eq(const ns_geo::RefPoint3f &p1,
                        const ns_geo::RefPoint3f &p2) {
  EXPECT_EQ(p1.id, p2.id);
  EXPECT_FLOAT_EQ(p1.x, p2.x);
  EXPECT_FLOAT_EQ(p1.y, p2.y);
  EXPECT_FLOAT_EQ(p1.z, p2.z);
  return;
}

void test_point2d_eq(const ns_geo::Point2d &p1, const ns_geo::Point2d &p2) {
  EXPECT_DOUBLE_EQ(p1.x, p2.x);
  EXPECT_DOUBLE_EQ(p1.y, p2.y);
}

void test_point3d_eq(const ns_geo::Point3d &p1, const ns_geo::Point3d &p2) {
  EXPECT_DOUBLE_EQ(p1.x, p2.x);
  EXPECT_DOUBLE_EQ(p1.y, p2.y);
  EXPECT_DOUBLE_EQ(p1.z, p2.z);
}

void test_refpoint2d_eq(const ns_geo::RefPoint2d &p1,
                        const ns_geo::RefPoint2d &p2) {
  EXPECT_EQ(p1.id, p2.id);
  EXPECT_DOUBLE_EQ(p1.x, p2.x);
  EXPECT_DOUBLE_EQ(p1.y, p2.y);
  return;
}

void test_refpoint3d_eq(const ns_geo::RefPoint3d &p1,
                        const ns_geo::RefPoint3d &p2) {
  EXPECT_EQ(p1.id, p2.id);
  EXPECT_DOUBLE_EQ(p1.x, p2.x);
  EXPECT_DOUBLE_EQ(p1.y, p2.y);
  EXPECT_DOUBLE_EQ(p1.z, p2.z);
  return;
}

#pragma endregion

#pragma region help classes

class TestRefPointSet2f : public testing::Test {
protected:
  virtual void SetUp() override {
    ns_geo::PointSet2f ps{{0.0f, 2.0f}, {1.0f, 1.0f}, {2.0f, -1.0f}, {-1.0f, 0.0f}, {3.0f, -2.0f}, {0.0f, -1.0f}};
    _rps = new ns_geo::RefPointSet2f();
    _rps->insert(ns_geo::RefPoint2f(0, 0.0f, 2.0f));
    _rps->insert(ns_geo::RefPoint2f(1, 1.0f, 1.0f));
    _rps->insert(ns_geo::RefPoint2f(2, 2.0f, -1.0f));
    _rps->insert(ns_geo::RefPoint2f(3, -1.0f, 0.0f));
    _rps->insert(ns_geo::RefPoint2f(4, 3.0f, -2.0f));
    _rps->insert(ns_geo::RefPoint2f(5, 0.0f, -1.0f));
  }

  void TearDown() override { delete _rps; }

  ns_geo::RefPointSet2f *_rps;
};

class TestRefPointSet3f : public testing::Test {
protected:
  virtual void SetUp() override {
    ns_geo::PointSet3f ps{{0.0f, 2.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {2.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 1.0f}, {3.0f, -2.0f, 1.0f}, {0.0f, -1.0f, 1.0f}};
    _rps = new ns_geo::RefPointSet3f();
    _rps->insert(ns_geo::RefPoint3f(0, 0.0f, 2.0f, 1.0f));
    _rps->insert(ns_geo::RefPoint3f(1, 1.0f, 1.0f, 1.0f));
    _rps->insert(ns_geo::RefPoint3f(2, 2.0f, -1.0f, 1.0f));
    _rps->insert(ns_geo::RefPoint3f(3, -1.0f, 0.0f, 1.0f));
    _rps->insert(ns_geo::RefPoint3f(4, 3.0f, -2.0f, 1.0f));
    _rps->insert(ns_geo::RefPoint3f(5, 0.0f, -1.0f, 1.0f));
  }

  void TearDown() override { delete _rps; }

  ns_geo::RefPointSet3f *_rps;
};

class TestPointSet : public testing::Test {
protected:
  virtual void SetUp() override {
    _ps2f = new ns_geo::PointSet2f();
    _ps2f->push_back({0.0f, 2.0f});
    _ps2f->push_back({1.0f, 1.0f});
    _ps2f->push_back({2.0f, -1.0f});
    _ps2f->push_back({-1.0f, 0.0f});
    _ps2f->push_back({3.0f, -2.0f});
    _ps2f->push_back({0.0f, -1.0f});

    _ps3f = new ns_geo::PointSet3f();
    _ps3f->push_back({0.0f, 2.0f, 1.0f});
    _ps3f->push_back({1.0f, 1.0f, 1.0f});
    _ps3f->push_back({2.0f, -1.0f, 1.0f});
    _ps3f->push_back({-1.0f, 0.0f, 1.0f});
    _ps3f->push_back({3.0f, -2.0f, 1.0f});
    _ps3f->push_back({0.0f, -1.0f, 1.0f});
  }

  void TearDown() override {
    delete _ps2f;
    delete _ps3f;
  }

  ns_geo::PointSet2f *_ps2f;
  ns_geo::PointSet3f *_ps3f;
};

#pragma endregion

#endif