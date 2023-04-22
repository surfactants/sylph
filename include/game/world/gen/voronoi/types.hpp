#pragma once

#include <SFML/System/Vector2.hpp>

#include <memory>

#include "../point.hpp"

namespace Voronoi
{
    struct Vertex;
    struct Half_Edge;

    using Vertex_ptr = std::shared_ptr<Vertex>;
    using Half_Edge_ptr = std::shared_ptr<Half_Edge>;

    struct Vertex {
        Point point;
        Half_Edge_ptr edge;

        Vertex(const Point& point, Half_Edge_ptr edge = nullptr);

        int x() { return point.x; }
        int y() { return point.y; }
    };

    struct Half_Edge {
        bool added { false };
        int left_index;
        int right_index;

        Vertex_ptr vertex;

        Half_Edge_ptr twin;
        Half_Edge_ptr prev;
        Half_Edge_ptr next;

        Half_Edge(int left, int right, Vertex_ptr vertex = nullptr);

        Vertex_ptr vertex0() { return vertex; }
        Vertex_ptr vertex1() { return twin->vertex; }
        bool finite();

        // iterators around vertex
        Half_Edge_ptr vertexNextCCW();

        Half_Edge_ptr vertexNextCW();
    };

    std::pair<Half_Edge_ptr, Half_Edge_ptr> makeTwins(int left, int right);

    std::pair<Half_Edge_ptr, Half_Edge_ptr> makeTwins(const std::pair<int, int>& indices);

    void connectHalfEdges(Half_Edge_ptr he1, Half_Edge_ptr he2);
}
