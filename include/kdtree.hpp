#pragma once

/**
 * @file kdtree.hpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2021-12-11
 * 
 * @copyright Copyright (c) 2021
 */

#include "point.hpp"
#include <memory>

namespace ns_geo
{
#pragma region global
    enum class SplitFeature
    {
        X,
        Y,
        Z
    };

    /**
     * @brief Orderly exchange and partition dimensions in the composition of kdtree construction for kdtree2
     * 
     * @param sf the split feature
     * @return SplitFeature 
     */
    SplitFeature exfDime2(SplitFeature sf)
    {
        return (sf == SplitFeature::X ? SplitFeature::Y : SplitFeature::X);
    }

    /**
     * @brief Orderly exchange and partition dimensions in the composition of kdtree construction for kdtree3
     * 
     * @param sf the split feature
     * @return SplitFeature 
     */
    SplitFeature exfDime3(SplitFeature sf)
    {
        return (sf == SplitFeature::X ? SplitFeature::Y : (sf == SplitFeature::Y ? SplitFeature::Z : SplitFeature::X));
    }

    std::ostream &operator<<(std::ostream &os, SplitFeature sf)
    {
        os << (sf == SplitFeature::X ? "[X]" : (sf == SplitFeature::Y ? "[Y]" : "[Z]"));
        return os;
    }

    /**
     * @brief the node used in the kdtree
     * 
     * @tparam _PointType 
     */
    template <typename _PointType>
    struct Node
    {
    public:
        using point_type = _PointType;
        using value_type = typename point_type::value_type;
        using node_ptr = std::shared_ptr<Node>;

    public:
        // father node pointer
        node_ptr _fn;
        // left node pointer
        node_ptr _ln;
        // right node pointer
        node_ptr _rn;
        // the point
        point_type _p;
        // the splited feature
        SplitFeature _sf;

        Node(const node_ptr &fn, const node_ptr &ln, const node_ptr &rn, const point_type &p, SplitFeature sf)
            : _fn(fn), _ln(ln), _rn(rn), _p(p), _sf(sf) {}
    };

#pragma endregion

#pragma region kdtree

    /**
     * @brief the virtual base class int the kdtree system
     * 
     * @tparam _PointType 
     */
    template <typename _PointType>
    class KdTree
    {
    public:
        using point_type = _PointType;
        using value_type = typename point_type::value_type;
        using node_type = Node<point_type>;
        using node_ptr = std::shared_ptr<node_type>;
        using pointset_type = std::vector<point_type>;
        using exchange_sf = SplitFeature (*)(SplitFeature sf);

    protected:
        // the root of the kdtree
        node_ptr _root;
        // the exchange feature function
        exchange_sf _ef;

    public:
        KdTree() = delete;

        KdTree(exchange_sf ef) : _ef(ef) {}

        /**
         * @brief print the kdtree by some order
         * 
         * @param mode [1]:Pre order;[2]:middle order;[3]post order
         */
        void printKdTree(int mode = 1, std::ostream &os = std::cout, bool el = true) const
        {
            switch (mode)
            {
            case 1:
                this->printKdTree1(this->_root, os);
                break;
            case 2:
                this->printKdTree2(this->_root, os);
                break;
            case 3:
                this->printKdTree3(this->_root, os);
                break;
            default:
                this->printKdTree1(this->_root, os);
                break;
            }
            if (el)
                os << '\n';
            return;
        }

    protected:
        /**
         * @brief initialize the root of the kdtree
         * 
         * @param ps the point set
         */
        virtual void buildKdTree(pointset_type ps) = 0;

        /**
         * @brief Sort the point set with a dimension as a reference
         * 
         * @param sf the reference feature
         * @param lps the point set on the left tree
         * @param rps the point set on the right tree
         */
        virtual void sortPointSet(SplitFeature sf, pointset_type &lps, pointset_type &rps) = 0;

        void buildKdTree(node_ptr &np, SplitFeature sf, pointset_type lps, pointset_type rps)
        {
            this->sortPointSet(sf, lps, rps);

            if (!lps.empty())
            {
                // find the media point in the point set on the left tree
                auto lmp = lps.at(lps.size() / 2);
                // construct the left node
                auto ln = std::make_shared<node_type>(np, nullptr, nullptr, lmp, sf);
                np->_ln = ln;

                // split the point set
                auto llps = pointset_type(lps.cbegin(), lps.cbegin() + lps.size() / 2);
                auto lrps = pointset_type(lps.cbegin() + lps.size() / 2 + 1, lps.cend());
                // build the left tree
                this->buildKdTree(ln, this->_ef(sf), llps, lrps);
            }

            if (!rps.empty())
            {
                auto rmp = rps.at(rps.size() / 2);
                auto rn = std::make_shared<node_type>(np, nullptr, nullptr, rmp, sf);
                np->_rn = rn;

                auto rlps = pointset_type(rps.cbegin(), rps.cbegin() + rps.size() / 2);
                auto rrps = pointset_type(rps.cbegin() + rps.size() / 2 + 1, rps.cend());
                this->buildKdTree(rn, this->_ef(sf), rlps, rrps);
            }
        }

        void printKdTree1(const node_ptr &n, std::ostream &os) const
        {
            if (n == nullptr)
                return;
            os << n->_p << ':' << n->_sf << ' ';
            this->printKdTree1(n->_ln, os);
            this->printKdTree1(n->_rn, os);
            return;
        }

        void printKdTree2(const node_ptr &n, std::ostream &os) const
        {
            if (n == nullptr)
                return;
            this->printKdTree2(n->_ln, os);
            os << n->_p << ':' << n->_sf << ' ';
            this->printKdTree2(n->_rn, os);
            return;
        }

        void printKdTree3(const node_ptr &n, std::ostream &os) const
        {
            if (n == nullptr)
                return;
            this->printKdTree3(n->_ln, os);
            this->printKdTree3(n->_rn, os);
            os << n->_p << ':' << n->_sf << ' ';
            return;
        }
    };

    template <typename _PointType>
    std::ostream &operator<<(std::ostream &os, const KdTree<_PointType> &kdtree)
    {
        kdtree.printKdTree(1, os, false);
        return os;
    }

#pragma endregion

#pragma region kdtree2

    template <typename _PointType>
    class KdTree2 : public KdTree<_PointType>
    {
    public:
        using point_type = _PointType;
        using value_type = typename point_type::value_type;
        using node_type = Node<point_type>;
        using node_ptr = std::shared_ptr<node_type>;
        using pointset_type = std::vector<point_type>;
        using exchange_sf = SplitFeature (*)(SplitFeature sf);
        using partent_type = KdTree<point_type>;

    public:
        KdTree2() = delete;
        KdTree2(const pointset_type &ps) : partent_type(exfDime2) { this->buildKdTree(ps); }

    private:
        virtual void buildKdTree(pointset_type ps) override
        {
            // find the feature that the stdevp is the largest
            float mean_x = 0.0f, mean_y = 0.0f;
            for (const auto &elem : ps)
                mean_x += elem.x(), mean_y += elem.y();
            mean_x /= ps.size(), mean_y /= ps.size();
            float stdevp_x = 0.0f, stdevp_y = 0.0f;
            for (const auto &elem : ps)
                stdevp_x += std::pow(elem.x() - mean_x, 2), stdevp_y += std::pow(elem.y() - mean_y, 2);

            SplitFeature sf;
            // decide the split feature and sort the point set
            if (stdevp_x < stdevp_y)
            {
                // split feature : Y
                std::sort(ps.begin(), ps.end(), [](const auto &p1, const auto &p2)
                          { return p1.y() < p2.y(); });
                sf = SplitFeature::Y;
            }
            else
            {
                // split feature : X
                std::sort(ps.begin(), ps.end(), [](const auto &p1, const auto &p2)
                          { return p1.x() < p2.x(); });
                sf = SplitFeature::X;
            }

            auto mp = ps.at(ps.size() / 2);
            auto lps = pointset_type(ps.cbegin(), ps.cbegin() + ps.size() / 2);
            auto rps = pointset_type(ps.cbegin() + ps.size() / 2 + 1, ps.cend());

            // fn, ln, rn, p, sp
            this->_root = std::make_shared<node_type>(nullptr, nullptr, nullptr, mp, sf);

            partent_type::buildKdTree(this->_root, partent_type::_ef(sf), lps, rps);
            return;
        }

        virtual void sortPointSet(SplitFeature sf, pointset_type &lps, pointset_type &rps) override
        {
            if (sf == SplitFeature::X)
            {
                std::sort(lps.begin(), lps.end(), [](const auto &p1, const auto &p2)
                          { return p1.x() < p2.x(); });
                std::sort(rps.begin(), rps.end(), [](const auto &p1, const auto &p2)
                          { return p1.x() < p2.x(); });
            }
            else
            {
                std::sort(lps.begin(), lps.end(), [](const auto &p1, const auto &p2)
                          { return p1.y() < p2.y(); });
                std::sort(rps.begin(), rps.end(), [](const auto &p1, const auto &p2)
                          { return p1.y() < p2.y(); });
            }
            return;
        }
    };

#pragma endregion

#pragma region kdtree3

    template <typename _PointType>
    class KdTree3 : public KdTree<_PointType>
    {
    public:
        using point_type = _PointType;
        using value_type = typename point_type::value_type;
        using node_type = Node<point_type>;
        using node_ptr = std::shared_ptr<node_type>;
        using pointset_type = std::vector<point_type>;
        using exchange_sf = SplitFeature (*)(SplitFeature sf);
        using partent_type = KdTree<point_type>;

    public:
        KdTree3() = delete;

        KdTree3(const pointset_type &ps) : partent_type(exfDime3) { this->buildKdTree(ps); }

    private:
        virtual void buildKdTree(pointset_type ps) override
        {
            // find the feature that the stdevp is the greatest
            float mean_x = 0.0f, mean_y = 0.0f, mean_z = 0.0f;
            for (const auto &elem : ps)
                mean_x += elem.x(), mean_y += elem.y(), mean_z += elem.z();
            mean_x /= ps.size(), mean_y /= ps.size(), mean_z /= ps.size();
            float stdevp_x = 0.0f, stdevp_y = 0.0f, stdevp_z = 0.0f;
            for (const auto &elem : ps)
                stdevp_x += std::pow(elem.x() - mean_x, 2), stdevp_y += std::pow(elem.y() - mean_y, 2), stdevp_z += std::pow(elem.z() - mean_z, 2);

            SplitFeature sf;
            // decide the split feature and sort the point set
            if (stdevp_x <= stdevp_y && stdevp_z <= stdevp_y)
            {
                // split feature : Y
                std::sort(ps.begin(), ps.end(), [](const auto &p1, const auto &p2)
                          { return p1.y() < p2.y(); });
                sf = SplitFeature::Y;
            }
            else if (stdevp_x <= stdevp_z && stdevp_y <= stdevp_z)
            {
                // split feature : Z
                std::sort(ps.begin(), ps.end(), [](const auto &p1, const auto &p2)
                          { return p1.z() < p2.z(); });
                sf = SplitFeature::Z;
            }
            else
            {
                // split feature : X
                std::sort(ps.begin(), ps.end(), [](const auto &p1, const auto &p2)
                          { return p1.x() < p2.x(); });
                sf = SplitFeature::X;
            }

            auto mp = ps.at(ps.size() / 2);
            auto lps = pointset_type(ps.cbegin(), ps.cbegin() + ps.size() / 2);
            auto rps = pointset_type(ps.cbegin() + ps.size() / 2 + 1, ps.cend());

            // fn, ln, rn, p, sp
            this->_root = std::make_shared<node_type>(nullptr, nullptr, nullptr, mp, sf);
            partent_type::buildKdTree(this->_root, partent_type::_ef(sf), lps, rps);
            return;
        }

        virtual void sortPointSet(SplitFeature sf, pointset_type &lps, pointset_type &rps) override
        {
            if (sf == SplitFeature::X)
            {
                std::sort(lps.begin(), lps.end(), [](const auto &p1, const auto &p2)
                          { return p1.x() < p2.x(); });
                std::sort(rps.begin(), rps.end(), [](const auto &p1, const auto &p2)
                          { return p1.x() < p2.x(); });
            }
            else if (sf == SplitFeature::Y)
            {
                std::sort(lps.begin(), lps.end(), [](const auto &p1, const auto &p2)
                          { return p1.y() < p2.y(); });
                std::sort(rps.begin(), rps.end(), [](const auto &p1, const auto &p2)
                          { return p1.y() < p2.y(); });
            }
            else
            {
                std::sort(lps.begin(), lps.end(), [](const auto &p1, const auto &p2)
                          { return p1.z() < p2.z(); });
                std::sort(rps.begin(), rps.end(), [](const auto &p1, const auto &p2)
                          { return p1.z() < p2.z(); });
            }
            return;
        }
    };

#pragma endregion
} // namespace ns_geo
