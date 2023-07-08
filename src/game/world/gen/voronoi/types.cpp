#include <game/world/gen/voronoi/types.hpp>

#include <cmath>

namespace Voronoi
{
    Voronoi::Vertex::Vertex(const Point& point, Half_Edge_ptr edge)
        : point { point }
        , edge { edge }
    {
    }

    Voronoi::Half_Edge::Half_Edge(int left_index, int right_index, Vertex_ptr vertex)
        : left_index { left_index }
        , right_index { right_index }
        , vertex { vertex }
    {
    }

    bool Voronoi::Half_Edge::finite()
    {
        return (vertex && twin->vertex);
    }

    Half_Edge_ptr Voronoi::Half_Edge::vertexNextCCW()
    {
        return twin->prev;
    }

    Half_Edge_ptr Voronoi::Half_Edge::vertexNextCW()
    {
        return next->twin;
    }

    std::pair<Half_Edge_ptr, Half_Edge_ptr> makeTwins(int left, int right)
    {
        Half_Edge_ptr h = std::make_shared<Half_Edge>(left, right);
        Half_Edge_ptr h_twin = std::make_shared<Half_Edge>(right, left);

        h->twin = h_twin;
        h_twin->twin = h;

        return std::make_pair(h, h_twin);
    }

    std::pair<Half_Edge_ptr, Half_Edge_ptr> makeTwins(const std::pair<int, int>& indices)
    {
        return makeTwins(indices.first, indices.second);
        Half_Edge_ptr h = std::make_shared<Half_Edge>(indices.first, indices.second);
        Half_Edge_ptr h_twin = std::make_shared<Half_Edge>(indices.second, indices.first);

        h->twin = h_twin;
        h_twin->twin = h;

        return std::make_pair(h, h_twin);
    }

    void connectHalfEdges(Half_Edge_ptr he1, Half_Edge_ptr he2)
    {
        he1->next = he2;
        he2->prev = he1;
    }
}
