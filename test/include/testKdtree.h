#pragma once

/**
 * @file testKdtree.h
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "helper.h"
#include "../../include/kdtree.hpp"

class TestKdTree2f : public testing::Test
{
protected:
    virtual void SetUp() override
    {
        ns_geo::PointSet2f ps{
            {0.0f, 2.0f},
            {1.0f, 1.0f},
            {2.0f, -1.0f},
            {-1.0f, 0.0f},
            {3.0f, -2.0f},
            {0.0f, -1.0f}};
        _kdtree = new ns_geo::KdTree2f(ps);
    }

    void TearDown() override
    {
        delete _kdtree;
    }

    ns_geo::KdTree2f *_kdtree;
};

TEST_F(TestKdTree2f, nearestKSearch)
{
    EXPECT_EQ(6, _kdtree->size());

    std::vector<ns_geo::Point2f> vec;
    std::vector<float> dis;

    _kdtree->nearestKSearch(ns_geo::Point2f(2.0f, 1.0f), 1, vec, dis);
    test_point2f_eq(ns_geo::Point2f(1.0f, 1.0f), vec[0]);
    EXPECT_EQ(1.0f, dis[0]);

    vec.clear(), dis.clear();

    _kdtree->nearestKSearch(ns_geo::Point2f(2.0f, 1.0f), 2, vec, dis);

    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::Point2f &p)
                                           { return p.x() == 1.0f && p.y() == 1.0f; }));
    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::Point2f &p)
                                           { return p.x() == 2.0f && p.y() == -1.0f; }));

    vec.clear(), dis.clear();

    _kdtree->nearestKSearch(ns_geo::Point2f(2.0f, 1.0f), 3, vec, dis);

    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::Point2f &p)
                                           { return p.x() == 1.0f && p.y() == 1.0f; }));
    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::Point2f &p)
                                           { return p.x() == 2.0f && p.y() == -1.0f; }));
    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::Point2f &p)
                                           { return p.x() == 0.0f && p.y() == 2.0f; }));
}

TEST_F(TestKdTree2f, radiusSearch)
{
    EXPECT_EQ(6, _kdtree->size());

    std::vector<ns_geo::Point2f> vec;
    std::vector<float> dis;

    _kdtree->radiusSearch(ns_geo::Point2f(2.0f, 1.0f), 0.5, vec, dis);
    EXPECT_TRUE(vec.empty());

    vec.clear(), dis.clear();

    _kdtree->radiusSearch(ns_geo::Point2f(2.0f, 1.0f), 2.1, vec, dis);
    EXPECT_EQ(2, vec.size());

    vec.clear(), dis.clear();

    _kdtree->radiusSearch(ns_geo::Point2f(2.0f, 1.0f), 2.5, vec, dis);
    EXPECT_EQ(3, vec.size());
}

class TestKdTree3f : public testing::Test
{
protected:
    virtual void SetUp() override
    {
        ns_geo::PointSet3f ps{
            {0.0f, 2.0f, 0.0f},
            {1.0f, 1.0f, 0.0f},
            {2.0f, -1.0f, 0.0f},
            {-1.0f, 0.0f, 0.0f},
            {3.0f, -2.0f, 0.0f},
            {0.0f, -1.0f, 0.0f}};
        _kdtree = new ns_geo::KdTree3f(ps);
    }

    void TearDown() override
    {
        delete _kdtree;
    }

    ns_geo::KdTree3f *_kdtree;
};

TEST_F(TestKdTree3f, nearestKSearch)
{
    EXPECT_EQ(6, _kdtree->size());

    std::vector<ns_geo::Point3f> vec;
    std::vector<float> dis;

    _kdtree->nearestKSearch(ns_geo::Point3f(2.0f, 1.0f, 0.0f), 1, vec, dis);
    test_point3f_eq(ns_geo::Point3f(1.0f, 1.0f, 0.0f), vec[0]);
    EXPECT_EQ(1.0f, dis[0]);

    vec.clear(), dis.clear();

    _kdtree->nearestKSearch(ns_geo::Point3f(2.0f, 1.0f, 0.0f), 2, vec, dis);

    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::Point3f &p)
                                           { return p.x() == 1.0f && p.y() == 1.0f && p.z() == 0.0f; }));
    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::Point3f &p)
                                           { return p.x() == 2.0f && p.y() == -1.0f && p.z() == 0.0f; }));

    vec.clear(), dis.clear();

    _kdtree->nearestKSearch(ns_geo::Point3f(2.0f, 1.0f, 0.0f), 3, vec, dis);

    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::Point3f &p)
                                           { return p.x() == 1.0f && p.y() == 1.0f && p.z() == 0.0f; }));
    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::Point3f &p)
                                           { return p.x() == 2.0f && p.y() == -1.0f && p.z() == 0.0f; }));
    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::Point3f &p)
                                           { return p.x() == 0.0f && p.y() == 2.0f && p.z() == 0.0f; }));
}

TEST_F(TestKdTree3f, radiusSearch)
{
    EXPECT_EQ(6, _kdtree->size());

    std::vector<ns_geo::Point3f> vec;
    std::vector<float> dis;

    _kdtree->radiusSearch(ns_geo::Point3f(2.0f, 1.0f, 0.0f), 0.5, vec, dis);
    EXPECT_TRUE(vec.empty());

    vec.clear(), dis.clear();

    _kdtree->radiusSearch(ns_geo::Point3f(2.0f, 1.0f, 0.0f), 2.1, vec, dis);
    EXPECT_EQ(2, vec.size());

    vec.clear(), dis.clear();

    _kdtree->radiusSearch(ns_geo::Point3f(2.0f, 1.0f, 0.0f), 2.5, vec, dis);
    EXPECT_EQ(3, vec.size());
}

class TestRefKdTree2f : public testing::Test
{
protected:
    virtual void SetUp() override
    {
        ns_geo::RefPointSet2f ps;
        ps.insert({0, 0.0f, 2.0f});
        ps.insert({1, 1.0f, 1.0f});
        ps.insert({2, 2.0f, -1.0f});
        ps.insert({3, -1.0f, 0.0f});
        ps.insert({4, 3.0f, -2.0f});
        ps.insert({5, 0.0f, -1.0f});
        _kdtree = new ns_geo::RefKdTree2f(ps);
    }

    void TearDown() override
    {
        delete _kdtree;
    }

    ns_geo::RefKdTree2f *_kdtree;
};

TEST_F(TestRefKdTree2f, nearestKSearch)
{
    EXPECT_EQ(6, _kdtree->size());

    std::vector<ns_geo::RefPoint2f> vec;
    std::vector<float> dis;

    _kdtree->nearestKSearch(ns_geo::Point2f(2.0f, 1.0f), 1, vec, dis);
    test_point2f_eq(ns_geo::Point2f(1.0f, 1.0f), vec[0]);
    EXPECT_EQ(1.0f, dis[0]);

    vec.clear(), dis.clear();

    _kdtree->nearestKSearch(ns_geo::Point2f(2.0f, 1.0f), 2, vec, dis);

    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::RefPoint2f &p)
                                           { return p.id() == 1 && p.x() == 1.0f && p.y() == 1.0f; }));
    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::RefPoint2f &p)
                                           { return p.id() == 2 && p.x() == 2.0f && p.y() == -1.0f; }));

    vec.clear(), dis.clear();

    _kdtree->nearestKSearch(ns_geo::Point2f(2.0f, 1.0f), 3, vec, dis);

    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::RefPoint2f &p)
                                           { return p.id() == 1 && p.x() == 1.0f && p.y() == 1.0f; }));
    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::RefPoint2f &p)
                                           { return p.id() == 2 && p.x() == 2.0f && p.y() == -1.0f; }));
    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::RefPoint2f &p)
                                           { return p.id() == 0 && p.x() == 0.0f && p.y() == 2.0f; }));
}

TEST_F(TestRefKdTree2f, radiusSearch)
{
    EXPECT_EQ(6, _kdtree->size());

    std::vector<ns_geo::RefPoint2f> vec;
    std::vector<float> dis;

    _kdtree->radiusSearch(ns_geo::Point2f(2.0f, 1.0f), 0.5, vec, dis);
    EXPECT_TRUE(vec.empty());

    vec.clear(), dis.clear();

    _kdtree->radiusSearch(ns_geo::Point2f(2.0f, 1.0f), 2.1, vec, dis);
    EXPECT_EQ(2, vec.size());

    vec.clear(), dis.clear();

    _kdtree->radiusSearch(ns_geo::Point2f(2.0f, 1.0f), 2.5, vec, dis);
    EXPECT_EQ(3, vec.size());
}

class TestRefKdTree3f : public testing::Test
{
protected:
    virtual void SetUp() override
    {
        ns_geo::RefPointSet3f ps;
        ps.insert({0, 0.0f, 2.0f, 0.0f});
        ps.insert({1, 1.0f, 1.0f, 0.0f});
        ps.insert({2, 2.0f, -1.0f, 0.0f});
        ps.insert({3, -1.0f, 0.0f, 0.0f});
        ps.insert({4, 3.0f, -2.0f, 0.0f});
        ps.insert({5, 0.0f, -1.0f, 0.0f});
        _kdtree = new ns_geo::RefKdTree3f(ps);
    }

    void TearDown() override
    {
        delete _kdtree;
    }

    ns_geo::RefKdTree3f *_kdtree;
};

TEST_F(TestRefKdTree3f, nearestKSearch)
{
    EXPECT_EQ(6, _kdtree->size());

    std::vector<ns_geo::RefPoint3f> vec;
    std::vector<float> dis;

    _kdtree->nearestKSearch(ns_geo::Point3f(2.0f, 1.0f, 0.0f), 1, vec, dis);
    test_refpoint3f_eq(ns_geo::RefPoint3f(1, 1.0f, 1.0f, 0.0f), vec[0]);
    EXPECT_EQ(1.0f, dis[0]);

    vec.clear(), dis.clear();

    _kdtree->nearestKSearch(ns_geo::Point3f(2.0f, 1.0f, 0.0f), 2, vec, dis);

    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::RefPoint3f &p)
                                           { return p.id() == 1 && p.x() == 1.0f && p.y() == 1.0f && p.z() == 0.0f; }));
    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::RefPoint3f &p)
                                           { return p.id() == 2 && p.x() == 2.0f && p.y() == -1.0f && p.z() == 0.0f; }));

    vec.clear(), dis.clear();

    _kdtree->nearestKSearch(ns_geo::Point3f(2.0f, 1.0f, 0.0f), 3, vec, dis);

    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::RefPoint3f &p)
                                           { return p.id() == 1 && p.x() == 1.0f && p.y() == 1.0f && p.z() == 0.0f; }));
    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::RefPoint3f &p)
                                           { return p.id() == 2 && p.x() == 2.0f && p.y() == -1.0f && p.z() == 0.0f; }));
    EXPECT_TRUE(vec.cend() != std::find_if(vec.cbegin(), vec.cend(), [](const ns_geo::RefPoint3f &p)
                                           { return p.id() == 0 && p.x() == 0.0f && p.y() == 2.0f && p.z() == 0.0f; }));
}

TEST_F(TestRefKdTree3f, radiusSearch)
{
    EXPECT_EQ(6, _kdtree->size());

    std::vector<ns_geo::RefPoint3f> vec;
    std::vector<float> dis;

    _kdtree->radiusSearch(ns_geo::Point3f(2.0f, 1.0f, 0.0f), 0.5, vec, dis);
    EXPECT_TRUE(vec.empty());

    vec.clear(), dis.clear();

    _kdtree->radiusSearch(ns_geo::Point3f(2.0f, 1.0f, 0.0f), 2.1, vec, dis);
    EXPECT_EQ(2, vec.size());

    vec.clear(), dis.clear();

    _kdtree->radiusSearch(ns_geo::Point3f(2.0f, 1.0f, 0.0f), 2.5, vec, dis);
    EXPECT_EQ(3, vec.size());
}
