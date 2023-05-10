#include <game/world/gen/voronoi/diagram.hpp>

#include <cassert>
#include <cmath>
#include <queue>

#include <engine/math/collide.hpp>
#include <engine/math/primordial.hpp>
#include <engine/resources/palette.hpp>
#include <engine/util/prng.hpp>

#include <game/world/gen/voronoi/circle.hpp>
#include <game/world/gen/voronoi/parabola.hpp>
#include <game/world/gen/voronoi/types.hpp>

#define BREAKPOINTS_EPSILON 1.0e-5

namespace Voronoi {

Diagram::Diagram(size_t point_count, sf::Vector2<double> min, sf::Vector2<double> max)
    : frame { sf::Vector2f(min), sf::Vector2f(max) }
{
    sf::Vector2f size(max - min);
    sf::Vector2f A(min);
    sf::Vector2f B(max.x, min.x);
    sf::Vector2f C(max);
    sf::Vector2f D(min.x, max.y);

    frame_face.push_back(std::make_pair(A, B));
    frame_face.push_back(std::make_pair(B, C));
    frame_face.push_back(std::make_pair(C, D));
    frame_face.push_back(std::make_pair(D, A));

    generatePoints(point_count, min, max);
    point_count = points.size();

    std::sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
        return (fabs(p1.y - p2.y) < POINT_EPSILON && p1.x < p2.x) || (fabs(p1.y - p2.y) >= POINT_EPSILON && p1.y < p2.y);
    });

    for (size_t i = 1; i < point_count; ++i) {
        if ((points[i - 1] - points[i]).norm() < 100) {
            points[i - 1].x = prng::number(max.x);
        }
    }
    for (int i = point_count - 1; i >= 0; --i) {
        int j = prng::number(i + 1);
        std::swap(points[i], points[j]);
    }

    // left points
    points.push_back(Point(min.x - (size.x / 2.f), min.y - (size.y / 2.f)));
    points.push_back(Point(min.x - (size.x / 2.f), min.y + (size.y / 2.f)));
    points.push_back(Point(min.x - (size.x / 2.f), max.y + (size.y / 2.f)));

    // middle points
    points.push_back(Point(min.x + (size.x / 2.f), min.y - (size.y / 2.f)));
    points.push_back(Point(min.x + (size.x / 2.f), max.y + (size.y / 2.f)));

    // right points
    points.push_back(Point(max.x + (size.x / 2.f), min.y - (size.y / 2.f)));
    points.push_back(Point(max.x + (size.x / 2.f), min.y + (size.y / 2.f)));
    points.push_back(Point(max.x + (size.x / 2.f), max.y + (size.y / 2.f)));

    extra_point_count = 8;

    build();

    size_t n = half_edges.size();
    for (size_t i = 0; i < n; i++) {
        Half_Edge_ptr h = half_edges[i];
        std::vector<double> x = { 2.d, 0.d };
        std::vector<double> y = { 2.d, 0.d };
        initEdgePointsVis(h, x, y, points);
    }

    // construct cells
    for (size_t i = 0; i < n; i++) {
        Half_Edge_ptr h = half_edges[i];
        std::vector<sf::Vector2f> p;
        if (h && h->vertex) {
            if (h->added) {
                continue;
            }
            //reordered_points.push_back(h->vertex->point);
            do {
                if (h) {
                    if (h->vertex0()) {
                        p.push_back(h->vertex0()->point.sfv());
                    }
                    h->added = true;
                }
                assert(half_edges[i]->left_index == h->left_index);
                h = h->next;
            } while (h && h != half_edges[i]);
            size_t s = p.size();
            sf::ConvexShape shape(s);
            for (size_t j = 0; j < s; j++) {
                shape.setPoint(j, p[j]);
            }
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineColor(Palette::white);
            m_cells.push_back(shape);
        }
    }

    for (auto it = points.begin(); it != points.end();) {
        if (!frame.contains(it->sfv())) {
            points.erase(it);
        }
        else {
            it++;
        }
    }

    const static sf::Vector2f r_size { 32.f, 32.f };
    const static sf::Vector2f r_orig { r_size / 2.f };

    // reorder points to match the indices of the cells that contain them
    // if no point is found, delete the cell
    std::vector<Point> r_points;
    std::vector<sf::ConvexShape> r_cells;
    for (auto& c : m_cells) {
        for (auto& p : points) {
            if (collide::convexShape_Point(c, p.sfv())) {
                r_cells.push_back(c);
                r_points.push_back(p);
                m_sites.push_back(p.sfv());
                break;
            }
        }
    }
    points = r_points;
    m_cells = r_cells;
}

void Diagram::generatePoints(size_t point_count, const sf::Vector2<double> min, const sf::Vector2<double> max)
{
    const static sf::Vector2f size(4.f, 4.f);
    const static sf::Vector2f origin(size / 2.f);

    constexpr static unsigned int max_find_iterations { 1000 };
    for (unsigned int i = 0; i < point_count; i++) {
        double x;
        double y;
        unsigned int iter { 0 };
        do {
            if (++iter >= max_find_iterations) {
                // log this with number of systems
                /*
                std::cout << "\n\nWARNING: FAILED TO FIND ENOUGH SPACE FOR "
                          << point_count << "POINTS IN VORONOI GENERATION!"
                          << "\n\tFAILED ON POINT " << i + 1
                          << "\n\t\tMIN " << min
                          << "\n\t\tMAX " << max << "\n\n";
                */
                return;
            }
            x = prng::number(min.x, max.x);
            y = prng::number(min.y, max.y);
        } while (nearbyPoints(x, y));
        points.push_back(Point(x, y));
    }
}

bool Diagram::nearbyPoints(double x, double y)
{
    constexpr static double min_dist { 128.d };
    for (const auto& p : points) {
        double dist = scalarDistance(sf::Vector2<double>(p.x, p.y), sf::Vector2<double>(x, y));
        if (std::abs(dist) < min_dist) {
            return true;
        }
    }
    return false;
}

std::vector<sf::ConvexShape> Diagram::get()
{
    return m_cells;
}

std::vector<sf::Vector2f> Diagram::sites()
{
    return m_sites;
}

struct Event {
    Event(int index = -1, int type = Event::SKIP, const Point& point = Point(0.0, 0.0))
        : index { index }
        , type { type }
        , point { point }
    {
    }

    enum {
        SITE = 0,
        CIRCLE = 1,
        SKIP = 2,
    };

    /*
     Site event attributes:
     */
    int index;

    int type;
    Point point;

    /*
     Circle event attributes:
     */
    Point center;
    BL_Node_ptr arc { nullptr };
};

using Event_ptr = std::shared_ptr<Event>;

struct PointComparator {
    bool operator()(const Point& p1, const Point& p2)
    {
        return (p1.y == p2.y && p1.x > p2.x) || p1.y > p2.y;
    }
};

struct PointComparator2 {
    bool operator()(const Point& p1, const Point& p2)
    {
        return (p1.y == p2.y && p1.x < p2.x) || p1.y < p2.y;
    }
};

struct Event_ptrComparator {
    PointComparator point_cmp;
    bool operator()(const Event_ptr& e1, const Event_ptr& e2)
    {
        return point_cmp(e1->point, e2->point);
    }
};

Event_ptr checkCircleEvent(BL_Node_ptr n1, BL_Node_ptr n2, BL_Node_ptr n3, const std::vector<Point>& points, double sweep_line)
{

    if (!n1 || !n2 || !n3) {
        return nullptr;
    }

    Point p1 = points[n1->getID()];
    Point p2 = points[n2->getID()];
    Point p3 = points[n3->getID()];
    Point center;

    if (p2.y > p1.y && p2.y > p3.y) {
        return nullptr;
    }

    if (!findCircleCenter(p1, p2, p3, center)) {
        return nullptr;
    }

    Point bottom(center);
    bottom.y += (center - p2).norm();

    // check circle event
    if (fabs(bottom.y - sweep_line) < POINT_EPSILON || sweep_line < bottom.y) {
        // create a circle event structure
        Event_ptr e = std::make_shared<Event>(-1, Event::CIRCLE, bottom);
        // initialize attributes
        e->center = center;
        e->arc = n2;
        // add reference in the corresponding node
        n2->circle_event = e;
        return e;
    }

    return nullptr;
}

void Diagram::build()
{
    // create a priority queue
    std::priority_queue<Event_ptr, std::vector<Event_ptr>, Event_ptrComparator> pq;

    // initialize it with all site events
    for (size_t i = 0; i < points.size(); ++i) {
        pq.push(std::make_shared<Event>(static_cast<int>(i), Event::SITE, points[i]));
    }

    // initialize vector of half_edges for faces
    faces.resize(points.size(), nullptr);

    // create a beachline tree
    BL_Node_ptr root;
    double sweep_line = 0L; // current position of the sweep_line

    // process events
    while (!pq.empty()) {
        // extract new event from the queue
        Event_ptr e = pq.top();
        pq.pop();

        // set position of a sweep_line
        sweep_line = e->point.y;

        if (e->type == Event::SITE) { // handle site event
            int point_i = e->index;
            if (root == nullptr) { // init empty beachline tree
                root = std::make_shared<BL_Node>(std::make_pair(point_i, point_i), &sweep_line, &points);
                continue;
            }
            else { // if it's not empty
                BL_Node_ptr arc = find(root, e->point.x);
                BL_Node_ptr subtree, left_leaf, right_leaf;

                if (arc->circle_event != nullptr) {
                    arc->circle_event->type = Event::SKIP; // ignore corresponding event
                }

                // check number of intersection points
                int isp_num = intersectionPointsNum(points[arc->getID()], e->point);

                // different subtrees depending on the number of intersection points
                if (isp_num == 1) {
                    subtree = makeSimpleSubtree(point_i, arc->getID(), &sweep_line, &points, half_edges);
                    left_leaf = subtree->left;
                    right_leaf = subtree->right;
                }
                else if (isp_num == 2) {
                    subtree = makeSubtree(point_i, arc->getID(), &sweep_line, &points, half_edges);
                    left_leaf = subtree->left;
                    right_leaf = subtree->right->right;
                }
                else {
                    continue;
                }

                if (arc->prev != nullptr) {
                    connect(arc->prev, left_leaf);
                }

                if (arc->next != nullptr) {
                    connect(right_leaf, arc->next);
                }

                // Replace old leaf with a subtree and rebalance it
                root = replace(arc, subtree);

                // Check circle events
                Event_ptr circle_event = checkCircleEvent(left_leaf->prev, left_leaf, left_leaf->next, points, sweep_line);
                if (circle_event != nullptr) {
                    pq.push(circle_event);
                }
                circle_event = checkCircleEvent(right_leaf->prev, right_leaf, right_leaf->next, points, sweep_line);
                if (circle_event != nullptr) {
                    pq.push(circle_event);
                }
            }
        }
        else if (e->type == Event::CIRCLE) { // handle circle event

            BL_Node_ptr arc = e->arc, prev_leaf, next_leaf;

            // get breakpoint nodes
            std::pair<BL_Node_ptr, BL_Node_ptr> breakpoints = calculateBreakpoints(arc);

            // recheck if it's a false alarm 1
            if (breakpoints.first == nullptr || breakpoints.second == nullptr) {
                continue;
            }

            // recheck if it's a false alarm 2
            double v1 = breakpoints.first->value(), v2 = breakpoints.second->value();

            if (fabs(v1 - v2) > BREAKPOINTS_EPSILON) {
                continue;
            }

            // create a new vertex and insert into doubly-connected edge list
            Vertex_ptr vertex = std::make_shared<Vertex>(e->center);
            Half_Edge_ptr h_first = breakpoints.first->edge;
            Half_Edge_ptr h_second = breakpoints.second->edge;

            // store vertex of Voronoi diagram
            m_vertices.push_back(vertex);

            // remove circle event corresponding to next leaf
            if (arc->prev != nullptr && arc->prev->circle_event != nullptr) {
                Event_ptr circle_e = arc->prev->circle_event;
                circle_e->type = Event::SKIP; // ignore corresponding event
            }

            // remove circle event corresponding to prev leaf
            if (arc->next != nullptr && arc->next->circle_event != nullptr) {
                Event_ptr circle_e = arc->next->circle_event;
                circle_e->type = Event::SKIP; // ignore corresponding event
            }

            // store pointers to the next and previous leaves
            prev_leaf = arc->prev;
            next_leaf = arc->next;

            // They should not be null
            assert(prev_leaf != nullptr);
            assert(next_leaf != nullptr);

            // get node associated with a new edge
            BL_Node_ptr new_edge_node;
            if (arc->parent == breakpoints.first)
                new_edge_node = breakpoints.second;
            else
                new_edge_node = breakpoints.first;

            // remove arc from the beachline
            root = remove(arc);

            // make a new pair of half_edges
            std::pair<Half_Edge_ptr, Half_Edge_ptr> twin_nodes = makeTwins(prev_leaf->getID(), next_leaf->getID());
            new_edge_node->edge = twin_nodes.first;
            //1/ new_edge_node->edge = twin_nodes.first;

            // connect half_edges
            connectHalfEdges(h_second, h_first->twin);
            connectHalfEdges(h_first, twin_nodes.first);
            connectHalfEdges(twin_nodes.second, h_second->twin);

            // half_edges are pointing into a vertex  -----> O <-----
            // not like this <---- O ----->
            // counterclockwise
            h_first->vertex = vertex;
            h_second->vertex = vertex;
            twin_nodes.second->vertex = vertex;
            vertex->edge = h_second;

            half_edges.push_back(twin_nodes.first);
            half_edges.push_back(twin_nodes.second);

            // check new circle events
            if (prev_leaf != nullptr && next_leaf != nullptr) {
                Event_ptr circle_event = checkCircleEvent(prev_leaf->prev, prev_leaf, next_leaf, points, sweep_line);
                if (circle_event != nullptr) {
                    pq.push(circle_event);
                }
                circle_event = checkCircleEvent(prev_leaf, next_leaf, next_leaf->next, points, sweep_line);
                if (circle_event != nullptr) {
                    pq.push(circle_event);
                }
            }
        }
    }

    // Fill edges corresponding to faces
    for (size_t i = 0; i < half_edges.size(); ++i) {
        Half_Edge_ptr he = half_edges[i];
        if (he->prev == nullptr || faces[he->left_index] == nullptr) {
            faces[he->left_index] = he;
        }
    }
}

void Diagram::initEdgePointsVis(Half_Edge_ptr h, std::vector<double>& x, std::vector<double>& y, const std::vector<Point>& points)
{

    if (h->vertex != nullptr && h->twin->vertex != nullptr) {
        x[0] = h->vertex->point.x;
        x[1] = h->twin->vertex->point.x;

        y[0] = h->vertex->point.y;
        y[1] = h->twin->vertex->point.y;
    }
    else if (h->vertex != nullptr) {
        x[0] = h->vertex->point.x;
        y[0] = h->vertex->point.y;

        Point norm = (points[h->left_index] - points[h->right_index]).normalized().getRotated90CCW();
        x[1] = x[0] + norm.x * 1000;
        y[1] = y[0] + norm.y * 1000;
    }
    else if (h->twin->vertex != nullptr) {
        x[0] = h->twin->vertex->point.x;
        y[0] = h->twin->vertex->point.y;

        Point norm = (points[h->twin->left_index] - points[h->twin->right_index]).normalized().getRotated90CCW();
        x[1] = x[0] + norm.x * 1000;
        y[1] = y[0] + norm.y * 1000;
    }
    else {
        Point p1 = points[h->left_index], p2 = points[h->right_index];

        Point norm = (p1 - p2).normalized().getRotated90CCW();
        Point c = 0.5 * (p1 + p2);

        x[0] = c.x + norm.x * 1000;
        x[1] = c.x - norm.x * 1000;

        y[0] = c.y + norm.y * 1000;
        y[1] = c.y - norm.y * 1000;
    }
}

} // namespace voronoi
