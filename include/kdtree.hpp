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
#include <stack>
#include <unordered_set>
#include <iterator>

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

    template <typename _Ty>
    bool atLeftTree(const Point2<_Ty> &p1, const Point2<_Ty> &p2, SplitFeature sf)
    {
        bool bl;
        switch (sf)
        {
        case SplitFeature::X:
            bl = p1.x() < p2.x() ? true : false;
            break;
        case SplitFeature::Y:
            bl = p1.y() < p2.y() ? true : false;
            break;
        default:
            bl = p1.x() < p2.x() ? true : false;
            break;
        }
        return bl;
    }

    template <typename _Ty>
    bool atLeftTree(const Point3<_Ty> &p1, const Point3<_Ty> &p2, SplitFeature sf)
    {
        bool bl;
        switch (sf)
        {
        case SplitFeature::X:
            bl = p1.x() < p2.x() ? true : false;
            break;
        case SplitFeature::Y:
            bl = p1.y() < p2.y() ? true : false;
            break;
        case SplitFeature::Z:
            bl = p1.z() < p2.z() ? true : false;
            break;
        default:
            bl = p1.x() < p2.x() ? true : false;
            break;
        }
        return bl;
    }

    template <typename _Ty>
    bool isIntersect(const Point2<_Ty> &searchPoint, const Point2<_Ty> &nodePoint, float radius, SplitFeature sf)
    {
        bool bl;
        switch (sf)
        {
        case SplitFeature::X:
            bl = std::abs(searchPoint.x() - nodePoint.x()) > radius ? false : true;
            break;
        case SplitFeature::Y:
            bl = std::abs(searchPoint.y() - nodePoint.y()) > radius ? false : true;
            break;
        default:
            bl = std::abs(searchPoint.x() - nodePoint.x()) > radius ? false : true;
            break;
        }
        return bl;
    }

    template <typename _Ty>
    bool isIntersect(const Point3<_Ty> &searchPoint, const Point3<_Ty> &nodePoint, float radius, SplitFeature sf)
    {
        bool bl;
        switch (sf)
        {
        case SplitFeature::X:
            bl = std::abs(searchPoint.x() - nodePoint.x()) > radius ? false : true;
            break;
        case SplitFeature::Y:
            bl = std::abs(searchPoint.y() - nodePoint.y()) > radius ? false : true;
            break;
        case SplitFeature::Z:
            bl = std::abs(searchPoint.z() - nodePoint.z()) > radius ? false : true;
            break;
        default:
            bl = std::abs(searchPoint.x() - nodePoint.x()) < radius ? false : true;
            break;
        }
        return bl;
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
        // the nodes's number on the kdtree
        std::size_t _size;

    public:
        KdTree() = delete;

        KdTree(exchange_sf ef, std::size_t size) : _root(nullptr), _ef(ef), _size(size) {}

        /**
         * @brief print the kdtree by some order
         *
         * @param mode [1]:Pre order;[2]:middle order;[3]post order
         */
        void printKdTree(int mode = 1, std::ostream &os = std::cout, bool el = true) const
        {
            printKdTree(_root, os, mode);
            if (el)
                os << '\n';
            return;
        }

        /**
         * @brief get the root of the kdtree
         *
         * @return const node_ptr&
         */
        inline const node_ptr &root() const { return this->_root; }

        /**
         * @brief get the nodes' number on the kdtree
         *
         * @return std::size_t
         */
        inline std::size_t size() const { return this->_size; }

        /**
         * @brief Search nearest K points from the search on the kdtree
         *
         * @param searchPoint the target search point
         * @param K the number of the nearest points
         * @param ps the point vector to save the search result
         * @param dis the distance
         */
        void nearestKSearch(const point_type &searchPoint, std::size_t K, std::vector<point_type> &ps, std::vector<float> &dis) const
        {
            if (K == 0 || this->_size == 0)
                return;
            else if (K >= _size)
            {
                /**
                 * @brief if the K is greater than the size of the kdtree, than add all points to the 'ps'
                 */
                K = _size;
                std::vector<node_ptr> nodes;
                nodesOnRootNode(_root, nodes);

                ps.resize(K), dis.resize(K);

                for (int i = 0; i != K; ++i)
                    ps.at(i) = nodes.at(i)->_p, dis.at(i) = distance(nodes.at(i)->_p, searchPoint);

                return;
            }

            // according binary search rule, get the initial seatch path
            std::stack<node_ptr> searchPath;
            std::unordered_set<node_ptr> mainPath;
            node_ptr tempNode = this->_root;

            // get the nodes on the search path
            while (tempNode != nullptr)
            {
                searchPath.push(tempNode);
                mainPath.insert(tempNode);

                if (atLeftTree(searchPoint, tempNode->_p, tempNode->_sf))
                    tempNode = tempNode->_ln;
                else
                    tempNode = tempNode->_rn;
            }

            // keep the point and the distance from the search point
            // [point, distance]
            std::vector<std::pair<point_type, float>> record;
            // the max distance in the 'record' vector
            float furthestDis = 0.0f;

            while (!searchPath.empty())
            {
                auto curNode = searchPath.top();
                searchPath.pop();

                auto curDis = distance(curNode->_p, searchPoint);
                if (record.size() < K)
                {
                    // if the size of the 'record' is less than 'K', than add the point to the 'record'
                    record.push_back(std::make_pair(curNode->_p, curDis));
                    // update the max distance
                    if (furthestDis < curDis)
                        furthestDis = curDis;
                }
                else
                {
                    // if the size of the 'record' is equals to the 'K'

                    // if the current distance if less than the max distance in the 'record'
                    if (curDis < furthestDis)
                    {
                        // find the point whose distance is [max|sedmax] from the search point

                        auto maxIter = record.begin();
                        auto sedMaxIter = record.begin();
                        for (auto iter = record.begin(); iter != record.end(); ++iter)
                        {
                            if (maxIter->second < iter->second)
                                maxIter = iter;
                            else if (sedMaxIter->second < iter->second)
                                sedMaxIter = iter;
                            else
                                continue;
                        }

                        // update the point
                        maxIter->first = curNode->_p;
                        maxIter->second = curDis;

                        // update the max distance
                        furthestDis = std::max(sedMaxIter->second, curDis);
                    }
                }

                // if current node is the main path node and it is intersect with the [search point] judged by the max distance
                if (mainPath.find(curNode) != mainPath.cend() &&
                    isIntersect(searchPoint, curNode->_p, furthestDis, curNode->_sf))
                {
                    // add nodes on the other side of the tree
                    std::vector<node_ptr> nodes;
                    if (atLeftTree(searchPoint, curNode->_p, curNode->_sf))
                        nodesOnRootNode(curNode->_rn, nodes);
                    else
                        nodesOnRootNode(curNode->_ln, nodes);
                    for (const auto &elem : nodes)
                        searchPath.push(elem);
                }
            }

            // fill the 'ps' and 'dis' vectors
            ps.resize(K), dis.resize(K);
            for (int i = 0; i != K; ++i)
                ps.at(i) = record.at(i).first, dis.at(i) = record.at(i).second;

            return;
        }

        /**
         * @brief Search  points whose distance from
         *        the search point is less than a specified distance on the kdtree
         *
         * @param searchPoint the target search point
         * @param radius the search radius
         * @param ps the point vector to save the search result
         * @param dis the distance
         */
        void radiusSearch(const point_type &searchPoint, float radius, std::vector<point_type> &ps, std::vector<float> &dis) const
        {
            if (radius <= 0.0 || this->_size == 0)
                return;
            // according binary search rule, get the initial seatch path
            std::stack<node_ptr> searchPath;
            std::unordered_set<node_ptr> mainPath;
            node_ptr tempNode = this->_root;

            while (tempNode != nullptr)
            {
                searchPath.push(tempNode);
                mainPath.insert(tempNode);

                if (atLeftTree(searchPoint, tempNode->_p, tempNode->_sf))
                    tempNode = tempNode->_ln;
                else
                    tempNode = tempNode->_rn;
            }

            // search points
            while (!searchPath.empty())
            {
                auto curNode = searchPath.top();
                searchPath.pop();

                auto d = distance(curNode->_p, searchPoint);
                if (d <= radius)
                    ps.push_back(curNode->_p), dis.push_back(d);

                /**
                 * @brief if the current node is the main node and
                 *        is intersect with the search point,
                 *        than add it's sub nodes to the search path
                 *
                 */
                if (mainPath.find(curNode) != mainPath.cend() &&
                    isIntersect(searchPoint, curNode->_p, radius, curNode->_sf))
                {
                    std::vector<node_ptr> nodes;
                    if (atLeftTree(searchPoint, curNode->_p, curNode->_sf))
                        nodesOnRootNode(curNode->_rn, nodes);
                    else
                        nodesOnRootNode(curNode->_ln, nodes);
                    for (const auto &elem : nodes)
                        searchPath.push(elem);
                }
            }
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

        void printKdTree(const node_ptr &n, std::ostream &os, int mode) const
        {
            if (n == nullptr)
                return;
            switch (mode)
            {
            case 1:
            {
                os << n->_p << ':' << n->_sf << ' ';
                this->printKdTree(n->_ln, os, mode);
                this->printKdTree(n->_rn, os, mode);
            }
            break;
            case 2:
            {
                this->printKdTree(n->_ln, os, mode);
                os << n->_p << ':' << n->_sf << ' ';
                this->printKdTree(n->_rn, os, mode);
            }
            break;
            case 3:
            {
                this->printKdTree(n->_ln, os, mode);
                this->printKdTree(n->_rn, os, mode);
                os << n->_p << ':' << n->_sf << ' ';
            }
            break;
            default:
            {
                os << n->_p << ':' << n->_sf << ' ';
                this->printKdTree(n->_ln, os, mode);
                this->printKdTree(n->_rn, os, mode);
            }
            break;
            }
            return;
        }

        bool isLeafNode(const node_ptr &n) const
        {
            if (n->_ln == nullptr && n->_rn == nullptr)
                return true;
            else
                return false;
        }

        void nodesOnRootNode(const node_ptr &node, std::vector<node_ptr> &nodes) const
        {
            if (node == nullptr)
                return;
            nodesOnRootNode(node->_ln, nodes);
            nodesOnRootNode(node->_rn, nodes);
            nodes.push_back(node);
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

        KdTree2(const pointset_type &ps) : partent_type(exfDime2, ps.size()) { this->buildKdTree(ps); }

    private:
        virtual void buildKdTree(pointset_type ps) override
        {
            if (ps.empty())
                return;
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

        KdTree3(const pointset_type &ps) : partent_type(exfDime3, ps.size()) { this->buildKdTree(ps); }

    private:
        virtual void buildKdTree(pointset_type ps) override
        {
            if (ps.empty())
                return;
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

#pragma region refkdtree2
    template <typename _PointType>
    class RefKdTree2 : public KdTree2<_PointType>
    {
    public:
        using refpoint_type = _PointType;
        using value_type = typename refpoint_type::value_type;
        using point_type = Point2<value_type>;
        using refpointset_type = RefPointSet2<value_type>;
        using partent_type = KdTree2<refpoint_type>;

    public:
        RefKdTree2() = delete;
        RefKdTree2(const refpointset_type &ps)
            : partent_type(trans(ps)) {}

        /**
         * @brief Search nearest K points from the search on the kdtree
         *
         * @param searchPoint the target search point
         * @param K the number of the nearest points
         * @param ps the point vector to save the search result
         * @param dis the distance
         */
        void nearestKSearch(const point_type &searchPoint, std::size_t K, std::vector<refpoint_type> &ps, std::vector<float> &dis) const
        {
            return partent_type::nearestKSearch({0, searchPoint.x(), searchPoint.y()}, K, ps, dis);
        }

        /**
         * @brief Search  points whose distance from
         *        the search point is less than a specified distance on the kdtree
         *
         * @param searchPoint the target search point
         * @param radius the search radius
         * @param ps the point vector to save the search result
         * @param dis the distance
         */
        void radiusSearch(const point_type &searchPoint, float radius, std::vector<refpoint_type> &ps, std::vector<float> &dis) const
        {
            return partent_type::radiusSearch({0, searchPoint.x(), searchPoint.y()}, radius, ps, dis);
        }

    protected:
        static std::vector<refpoint_type> trans(const refpointset_type &ps)
        {
            std::vector<refpoint_type> rps(ps.size());
            int index = 0;
            for (const auto &elem : ps)
                rps[index++] = elem.second;
            return rps;
        }
    };

#pragma endregion

#pragma region refkdtree3
    template <typename _PointType>
    class RefKdTree3 : public KdTree3<_PointType>
    {
    public:
        using refpoint_type = _PointType;
        using value_type = typename refpoint_type::value_type;
        using point_type = Point3<value_type>;
        using refpointset_type = RefPointSet3<value_type>;
        using partent_type = KdTree3<refpoint_type>;

    public:
        RefKdTree3() = delete;

        RefKdTree3(const refpointset_type &ps)
            : partent_type(trans(ps)) {}

        /**
         * @brief Search nearest K points from the search on the kdtree
         *
         * @param searchPoint the target search point
         * @param K the number of the nearest points
         * @param ps the point vector to save the search result
         * @param dis the distance
         */
        void nearestKSearch(const point_type &searchPoint, std::size_t K, std::vector<refpoint_type> &ps, std::vector<float> &dis) const
        {
            return partent_type::nearestKSearch({0, searchPoint.x(), searchPoint.y(), searchPoint.z()}, K, ps, dis);
        }

        /**
         * @brief Search  points whose distance from
         *        the search point is less than a specified distance on the kdtree
         *
         * @param searchPoint the target search point
         * @param radius the search radius
         * @param ps the point vector to save the search result
         * @param dis the distance
         */
        void radiusSearch(const point_type &searchPoint, float radius, std::vector<refpoint_type> &ps, std::vector<float> &dis) const
        {
            return partent_type::radiusSearch({0, searchPoint.x(), searchPoint.y(), searchPoint.z()}, radius, ps, dis);
        }

    protected:
        static std::vector<refpoint_type> trans(const refpointset_type &ps)
        {
            std::vector<refpoint_type> rps(ps.size());
            int index = 0;
            for (const auto &elem : ps)
                rps[index++] = elem.second;
            return rps;
        }
    };

#pragma endregion
} // namespace ns_geo
