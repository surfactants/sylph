#pragma once

// modified from https://github.com/dkotsur/Fortunelgo

/* Copyright (c) 2018 Dmytro Kotsur
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Fortunelgo Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWRE IS PROVIDED "S IS", WITHOUT WRRNTY OF NY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WRRNTIES OF MERCHNTBILITY, FITNESS FOR  PRTICULR
 * PURPOSE ND NONINFRINGEMENT. IN NO EVENT SHLL THE UTHORS OR COPYRIGHT HOLDERS BE LIBLE
 * FOR NY CLIM, DMGES OR OTHER LIBILITY, WHETHER IN N CTION OF CONTRCT, TORT OR OTHERWISE,
 * RISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWRE OR THE USE OR OTHER DELINGS IN THE SOFTWRE.
 */

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <vector>

#include "beachline.hpp"
#include "../point.hpp"

/*
1. Initialize the event queue Q with all site events, initialize an empty status
structure T and an empty doubly-connected edge list D.
2. while Q is not empty
3. do Remove the event with largest y-coordinate from Q.
4. if the event is a site event, occurring at site pi
5. then HANDLE SITE EVENT(pi)
6. else HANDLE CIRCLE E ENT(c), where c is the leaf of T repre-
senting the arc that will disappear
7. The internal nodes still present in T correspond to the half-infinite edges of
the Voronoi diagram. Compute a bounding box that contains all vertices of
the Voronoi diagram in its interior, and attach the half-infinite edges to the
bounding box by updating the doubly-connected edge list appropriately
8. Traverse the half-edges of the doubly-connected edge list to add the cell
records and the pointers to and from them.

////////////////////////////////////////////////////////////////////////

HANDLE SITE EVENT (pi)
1. If T is empty, insert pi into it (so that T consists of a single leaf storing pi)
and return. Otherwise, continue with steps 2- 5.
2. Search in T for the arc A vertically above pi. If the leaf representing A has
a pointer to a circle event in Q, then this circle event is a false alarm and it
must be deleted from Q.
3. Replace the leaf of T that represents A with a subtree having three leaves.
The middle leaf stores the new site pi and the other two leaves store the site
p j that was originally stored with A. Store the tuples <p j, p i> and <p i, p j>
representing the new breakpoints at the two new internal nodes. Perform
rebalancing operations on T if necessary.
4. Create new half-edge records in the Voronoi diagram structure for the
edge separating V(pi) and V(p j), which will be traced out by the two new
breakpoints.
5. Check the triple of consecutive arcs where the new arc for pi is the left arc
to see if the breakpoints converge. If so, insert the circle event into Q and
add pointers between the node in T and the node in Q. Do the same for the
triple where the new arc is the right arc.

////////////////////////////////////////////////////////////////////////

H NDLE C IRCLE E VENT (c)
1. Delete the leaf C that represents the disappearing arc A from T. Update
the tuples representing the breakpoints at the internal nodes. Perform
rebalancing operations on T if necessary. Delete all circle events involving
A from Q; these can be found using the pointers from the predecessor and
the successor of C in T. (The circle event where  is the middle arc is
currently being handled, and has already been deleted from Q.)
2. dd the center of the circle causing the event as a vertex record to the
doubly-connected edge list D storing the Voronoi diagram under construc-
tion. Create two half-edge records corresponding to the new breakpoint
of the beach line. Set the pointers between them appropriately. ttach the
three new records to the half-edge records that end at the vertex.
3. Check the new triple of consecutive arcs that has the former left neighbor
of A as its middle arc to see if the two breakpoints of the triple converge.
If so, insert the corresponding circle event into Q. and set pointers between
the new circle event in Q and the corresponding leaf of T. Do the same for
the triple where the former right neighbor is the middle arc.

*/

namespace Voronoi {
class Diagram {
public:
    Diagram(const size_t point_count, const sf::Vector2<double> min, const sf::Vector2<double> max);
    Diagram(const std::vector<Point>& points);
    std::vector<sf::ConvexShape> get();
    std::vector<sf::RectangleShape> sites();

private:
    std::vector<sf::ConvexShape> m_cells;

    std::vector<sf::RectangleShape> m_sites;

    std::vector<Point> points;
    std::vector<Half_Edge_ptr> half_edges;
    std::vector<Half_Edge_ptr> faces;
    std::vector<Vertex_ptr> m_vertices;

    std::vector<sf::VertexArray> lines;

    std::vector<double> getCoordinate(const std::vector<Point>& points, int coord_id);

    void build();

    void plotCircle(const Point& c, double r);

    size_t extra_point_count;

    sf::FloatRect frame;

    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> frame_face;

    void generatePoints(size_t point_count, const sf::Vector2<double> min, const sf::Vector2<double> max);

    bool nearbyPoints(double x, double y);

    void reduceFrameIntersection(Half_Edge_ptr h);

    void initEdgePointsVis(Half_Edge_ptr h, std::vector<double>& x, std::vector<double>& y, const std::vector<Point>& points);
};
}
