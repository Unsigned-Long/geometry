#include "kdtree.h"

namespace GIS
{
    kdTree::~kdTree()
    {
        this->deconstruct_KdTree(this->_root);
    }

    kdTree::Node *kdTree::selectRoot()
    {
        return this->_root;
    }

    list<string> kdTree::selectRefPointID()
    {
        list<string> ls;
        this->selectRefPointID_KdTree(ls, this->_root);
        return ls;
    }

    void kdTree::insertRefPoint(const RefPoint3d &refPoint)
    {
        this->RefPoint3dDB::insertRefPoint(refPoint);
        this->insertRefPoint_KdTree(refPoint, &this->_root, nullptr);
    }

    void kdTree::insertRefPoint(const initializer_list<RefPoint3d> &refPoints)
    {
        this->RefPoint3dDB::insertRefPoint(refPoints);
        for(const auto&elem : refPoints) {
            this->insertRefPoint_KdTree(elem, &this->_root, nullptr);
        }
    }

    bool kdTree::deleteRefPoint(const string &pointID)
    {
        auto point = this->selectRefPoint(pointID);
        if(this->RefPoint3dDB::deleteRefPoint(pointID) == false) {
            return false;
        }
        this->deleteRefPoint_KdTree(point, &this->_root);
        return true;
    }

    list<string> kdTree::nearestKSearch(const point2d &target, size_t k)
    {
        auto nearest = this->_nearestKSearch(target, k);
        list<string> ids;
        for(const auto&elem : nearest) {
            ids.push_back(elem.first._id);
        }
        return ids;
    }

    list<string> kdTree::neighborSearch(const point2d &target, double maxDis)
    {
        auto nearest = this->_neighborSearch(target, maxDis);
        list<string> ids;
        for(const auto&elem : nearest) {
            ids.push_back(elem.first._id);
        }
        return ids;
    }

    list<pair<RefPoint3d, double>> kdTree::_nearestKSearch(const point2d &target, size_t k)
    {
        if(this->_root == nullptr || k == 0) {
            return {};
        }
        list<pair<RefPoint3d, double>> nearPoints;
        list<kdTree::Node*> nodeList;
        this->searchPath_KdTree(nodeList, target, this->_root);
        auto curNode = nodeList.back();
        auto curPoint = this->selectRefPoint(curNode->_id);
        double maxDis = GIS::distance(target, point2d(curPoint._pos._x, curPoint._pos._y));
        nodeList.pop_back();
        nearPoints.push_back({curPoint, maxDis});
        while (!nodeList.empty()) {
            //
            curNode = nodeList.back();
            curPoint = this->selectRefPoint(curNode->_id);
            nodeList.pop_back();
            double curDis = GIS::distance(target, point2d(curPoint._pos._x, curPoint._pos._y));
            if(nearPoints.size() < k) {
                nearPoints.push_back({curPoint, curDis});
            } else {
                nearPoints.sort(
                    [](const list<pair<RefPoint3d, double>>::value_type & p1,
                const list<pair<RefPoint3d, double>>::value_type & p2) {
                    return p1.second < p2.second;
                });
                maxDis = nearPoints.back().second;
                if(curDis < maxDis) {
                    nearPoints.pop_back();
                    nearPoints.push_back({curPoint, curDis});
                }
            }
            //
            if(curNode->_left != nullptr || curNode->_right != nullptr) {
                //sort the near points
                nearPoints.sort(
                    [](const list<pair<RefPoint3d, double>>::value_type & p1,
                const list<pair<RefPoint3d, double>>::value_type & p2) {
                    return p1.second < p2.second;
                });
                maxDis = nearPoints.back().second;
                if(curNode->_pivot == PIVOT::X_AXIS) {
                    if(abs(target._x - curPoint._pos._x) < maxDis) {
                        if(target._x < curPoint._pos._x) {
                            this->selectNode_KdTree(nodeList, curNode->_right);
                        } else {
                            this->selectNode_KdTree(nodeList, curNode->_left);
                        }
                    }
                } else {
                    if(abs(target._y - curPoint._pos._y) < maxDis) {
                        if(target._y < curPoint._pos._y) {
                            this->selectNode_KdTree(nodeList, curNode->_right);
                        } else {
                            this->selectNode_KdTree(nodeList, curNode->_left);
                        }
                    }
                }
            }
        }
        return nearPoints;
    }

    list<pair<RefPoint3d, double> > kdTree::_neighborSearch(const point2d& target, double maxDis)
    {
        if(this->_root == nullptr) {
            return {};
        }
        list<pair<RefPoint3d, double> > neighborPoints;
        list<kdTree::Node*> nodeList;
        this->searchPath_KdTree(nodeList, target, this->_root);
        while (!nodeList.empty()) {
            auto curNode = nodeList.back();
            auto curPoint = this->selectRefPoint(curNode->_id);
            nodeList.pop_back();
            double dis = GIS::distance(target, point2d(curPoint._pos._x, curPoint._pos._y));
            if(dis <= maxDis) {
                neighborPoints.push_back({curPoint, dis});
            }
            //
            if(curNode->_left != nullptr || curNode->_right != nullptr) {
                if(curNode->_pivot == PIVOT::X_AXIS) {
                    if(abs(target._x - curPoint._pos._x) < maxDis) {
                        if(target._x < curPoint._pos._x) {
                            this->selectNode_KdTree(nodeList, curNode->_right);
                        } else {
                            this->selectNode_KdTree(nodeList, curNode->_left);
                        }
                    }
                } else {
                    if(abs(target._y - curPoint._pos._y) < maxDis) {
                        if(target._y < curPoint._pos._y) {
                            this->selectNode_KdTree(nodeList, curNode->_right);
                        } else {
                            this->selectNode_KdTree(nodeList, curNode->_left);
                        }
                    }
                }
            }
        }
        return neighborPoints;
    }

    void kdTree::selectRefPointID_KdTree(list<string> &ls, Node *curRoot)
    {
        if(curRoot == nullptr) {
            return;
        }
        ls.push_back(curRoot->_id);
        this->selectRefPointID_KdTree(ls, curRoot->_left);
        this->selectRefPointID_KdTree(ls, curRoot->_right);
    }

    void kdTree::selectNode_KdTree(list<kdTree::Node *> &ls, kdTree::Node *curRoot)
    {
        if(curRoot == nullptr) {
            return;
        }
        ls.push_back(curRoot);
        this->selectNode_KdTree(ls, curRoot->_left);
        this->selectNode_KdTree(ls, curRoot->_right);
    }

    void kdTree::construct_KdTree(list<string> &pointsLS, Node **curRoot, Node *parent)
    {
        if(pointsLS.empty()) {
            return;
        }
        if(pointsLS.size() == 1) {
            if(parent == nullptr) {
                *curRoot = new Node(pointsLS.front(), PIVOT::Y_AXIS, parent, nullptr, nullptr);
            } else {
                auto pivot = parent->_pivot == PIVOT::X_AXIS ? PIVOT::Y_AXIS : PIVOT::X_AXIS;
                *curRoot = new Node(pointsLS.front(), pivot, parent, nullptr, nullptr);
            }
            return;
        }
        auto infoPair = this->maxVariance(pointsLS);
        auto& pivot = infoPair.first;
        auto& maxVarSortedList = infoPair.second;
        auto middleIter = this->listMiddleIter(maxVarSortedList);
        auto middleID = *middleIter;
        list<string> smallList(maxVarSortedList.begin(), middleIter);
        list<string> largeList(++middleIter, maxVarSortedList.end());
        *curRoot = new Node(middleID, pivot, parent, nullptr, nullptr);
        this->construct_KdTree(smallList, &((*curRoot)->_left), *curRoot);
        this->construct_KdTree(largeList, &((*curRoot)->_right), *curRoot);
    }

    pair<kdTree::PIVOT, list<string> > kdTree::maxVariance(list<string> &pointsLS)
    {
        //x
        pointsLS.sort([this](const string & id1, const string & id2) {
            auto& p1 = this->selectRefPoint(id1)._pos;
            auto& p2 = this->selectRefPoint(id2)._pos;
            return p1._x < p2._x;
        });
        list<string> xVarList(pointsLS.begin(), pointsLS.end());
        auto xMiddlePointID = this->listMiddleIter(pointsLS);
        auto& xMiddleValue = this->selectRefPoint(*xMiddlePointID)._pos._x;
        double xVar = 0.0;
        for(const auto&elem : pointsLS) {
            auto& curPos = this->selectRefPoint(elem)._pos;
            xVar += pow(xMiddleValue - curPos._x, 2);
        }
        //y
        pointsLS.sort([this](const string & id1, const string & id2) {
            auto& p1 = this->selectRefPoint(id1)._pos;
            auto& p2 = this->selectRefPoint(id2)._pos;
            return p1._y < p2._y;
        });
        list<string> yVarList(pointsLS.begin(), pointsLS.end());
        auto yMiddlePointID = this->listMiddleIter(pointsLS);
        auto& yMiddleValue = this->selectRefPoint(*yMiddlePointID)._pos._y;
        double yVar = 0.0;
        for(const auto&elem : pointsLS) {
            auto& curPos = this->selectRefPoint(elem)._pos;
            yVar += pow(yMiddleValue - curPos._y, 2);
        }
        if(xVar > yVar) {
            return {PIVOT::X_AXIS, xVarList};
        } else {
            return {PIVOT::Y_AXIS, yVarList};
        }
    }

    list<string>::iterator kdTree::listMiddleIter(list<string> &pointsLS)
    {
        auto middlePos = static_cast<int>(pointsLS.size() / 2);
        auto beginIter = pointsLS.begin();
        std::advance(beginIter, middlePos);
        return beginIter;
    }

    void kdTree::insertRefPoint_KdTree(const RefPoint3d &refPoint, Node **curRoot, Node *parent)
    {
        if(*curRoot == nullptr) {
            if(parent == nullptr) {
                *curRoot = new Node(refPoint._id, PIVOT::Y_AXIS, parent, nullptr, nullptr);
            } else {
                auto pivot = parent->_pivot == PIVOT::X_AXIS ? PIVOT::Y_AXIS : PIVOT::X_AXIS;
                *curRoot = new Node(refPoint._id, pivot, parent, nullptr, nullptr);
            }
        } else {
            auto& pivot = (*curRoot)->_pivot;
            auto& pos = this->selectRefPoint((*curRoot)->_id)._pos;
            if(pivot == PIVOT::X_AXIS) {
                if(refPoint._pos._x < pos._x) {
                    this->insertRefPoint_KdTree(refPoint, &((*curRoot)->_left), *curRoot);
                } else {
                    this->insertRefPoint_KdTree(refPoint, &((*curRoot)->_right), *curRoot);
                }
            } else {
                if(refPoint._pos._y < pos._y) {
                    this->insertRefPoint_KdTree(refPoint, &((*curRoot)->_left), *curRoot);
                } else {
                    this->insertRefPoint_KdTree(refPoint, &((*curRoot)->_right), *curRoot);
                }
            }
        }
    }

    void kdTree::deconstruct_KdTree(Node *curRoot)
    {
        if(curRoot == nullptr) {
            return;
        }
        this->deconstruct_KdTree(curRoot->_left);
        this->deconstruct_KdTree(curRoot->_right);
        delete curRoot;
        curRoot = nullptr;
    }

    void kdTree::deleteRefPoint_KdTree(const RefPoint3d &point, Node **curRoot)
    {
        if((*curRoot)->_id == point._id) {
            list<string> ls;
            this->selectRefPointID_KdTree(ls, (*curRoot));
            ls.pop_front();
            auto parent = (*curRoot)->_parent;
            this->deconstruct_KdTree(*curRoot);
            this->construct_KdTree(ls, curRoot, parent);
        } else {
            auto& curRootPos = this->selectRefPoint((*curRoot)->_id)._pos;
            if((*curRoot)->_pivot == PIVOT::X_AXIS) {
                if(point._pos._x < curRootPos._x) {
                    this->deleteRefPoint_KdTree(point, &(*curRoot)->_left);
                } else {
                    this->deleteRefPoint_KdTree(point, &(*curRoot)->_right);
                }
            } else {
                if(point._pos._y < curRootPos._y) {
                    this->deleteRefPoint_KdTree(point, &(*curRoot)->_left);
                } else {
                    this->deleteRefPoint_KdTree(point, &(*curRoot)->_right);
                }
            }
        }
    }

    void kdTree::searchPath_KdTree(list<kdTree::Node *> &serchPath, const point2d &point, kdTree::Node *curRoot)
    {
        if(curRoot == nullptr) {
            return;
        }
        serchPath.push_back(curRoot);
        auto& curRootPos = this->selectRefPoint(curRoot->_id)._pos;
        if(curRoot->_pivot == PIVOT::X_AXIS) {
            if(point._x < curRootPos._x) {
                this->searchPath_KdTree(serchPath, point, curRoot->_left);
            } else {
                this->searchPath_KdTree(serchPath, point, curRoot->_right);
            }
        } else {
            if(point._y < curRootPos._y) {
                this->searchPath_KdTree(serchPath, point, curRoot->_left);
            } else {
                this->searchPath_KdTree(serchPath, point, curRoot->_right);
            }
        }
    }

}
