#pragma once

#include <vector>

#include "beachline.hpp"
#include "types.hpp"

namespace Voronoi
{
    struct Event;
    using Event_ptr = std::shared_ptr<Event>;

    struct BL_Node;
    using BL_Node_ptr = std::shared_ptr<BL_Node>;

    struct BL_Node {

        BL_Node(const std::pair<int, int>& indices
              , double* sweep_line = nullptr
              , const std::vector<Point>* points = nullptr
              , BL_Node_ptr left = nullptr
              , BL_Node_ptr right = nullptr
              , BL_Node_ptr parent = nullptr
              , int height = 1);

        std::pair<int, int> indices;
        double* sweep_line;
        const std::vector<Point>* points;
        BL_Node_ptr left, right, parent;
        int height;
        Event_ptr circle_event;
        Half_Edge_ptr edge;

        bool isLeaf();

        int getID();

        bool hasIndices(int a, int b);

        bool hasIndices(const std::pair<int, int>& p);

        double value();

        BL_Node_ptr prev { nullptr };
        BL_Node_ptr next { nullptr };
    };

    void connect(BL_Node_ptr prev, BL_Node_ptr next);

    int getHeight(BL_Node_ptr node);

    void updateHeight(BL_Node_ptr node);

    int getBalance(BL_Node_ptr node);

    BL_Node_ptr rotateLeft(BL_Node_ptr node);

    BL_Node_ptr rotateRight(BL_Node_ptr node);

    BL_Node_ptr find(BL_Node_ptr root, double x);

    BL_Node_ptr replace(BL_Node_ptr node, BL_Node_ptr new_node);

    BL_Node_ptr remove(BL_Node_ptr leaf);

    std::pair<BL_Node_ptr, BL_Node_ptr> calculateBreakpoints(BL_Node_ptr leaf);

    bool isRoot(BL_Node_ptr node);

    BL_Node_ptr makeSubtree(int index
                          , int index_behind
                          , double* sweep_line
                          , const std::vector<Point>* points
                          , std::vector<Half_Edge_ptr> edges);

    BL_Node_ptr makeSimpleSubtree(int index
                            , int index_behind
                            , double *sweep_line
                            , const std::vector<Point> *points
                            , std::vector<Half_Edge_ptr> &edges);

    bool validate(BL_Node_ptr node);

    bool checkBalance(BL_Node_ptr node);
}
