#include <game/world/gen/voronoi/beachline.hpp>

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

#include <game/world/gen/voronoi/parabola.hpp>

using namespace Voronoi;

namespace Voronoi
{

BL_Node::BL_Node(const std::pair<int, int>& indices
      , double* sweep_line
      , const std::vector<Point>* points
      , BL_Node_ptr left
      , BL_Node_ptr right
      , BL_Node_ptr parent
      , int height)
    : indices { indices }
    , sweep_line { sweep_line }
    , points { points }
    , left { left }
    , right { right }
    , parent { parent }
    , height { height }
{}

bool BL_Node::isLeaf()
{
    return (indices.first == indices.second);
}

int BL_Node::getID()
{
    return indices.first;
}

bool BL_Node::hasIndices(int a, int b)
{
    return (indices.first == a && indices.second == b);
}

bool BL_Node::hasIndices(const std::pair<int, int>& p)
{
    return (indices.first == p.first && indices.second == p.second);
}

double BL_Node::value()
{
    if (points == nullptr) {
        return std::numeric_limits<double>::infinity();
    }
    if (isLeaf()) {
        return (*points)[indices.first].x;
    }
    else {
        Point p1 = (*points)[indices.first];
        Point p2 = (*points)[indices.second];

        std::vector<Point> intersects = findIntersections(p1, p2, *sweep_line);
        if (intersects.size() == 2) {
            if (p1.y < p2.y) {
                return intersects[0].x;
            }
            else {
                return intersects[1].x;
            }
        }
        else {
            return intersects[0].x;
        }
    }
}


/**
 Connect as a list
 */
void connect(BL_Node_ptr prev, BL_Node_ptr next)
{
    prev->next = next;
    next->prev = prev;
}


/**
 Check if the node is a root node
 */
bool isRoot(BL_Node_ptr node)
{
    return node->parent == nullptr;
}


/**
 Get height of the node
 */
int getHeight(BL_Node_ptr node)
{
    if (node == nullptr) return 0;
    return node->height;
}


/**
 Update height of the node
 */
void updateHeight(BL_Node_ptr node)
{
    if (node == nullptr)
        return;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
}


/**
 Get balance of the node (difference between the height of left and right subtrees)
 */
int getBalance(BL_Node_ptr node)
{
    return getHeight(node->left) - getHeight(node->right);
}


/**
 Performs rotation of a tree around `node` such that it goes to the left subtree
 */
BL_Node_ptr rotateLeft(BL_Node_ptr node)
{
    if (node == nullptr)
        return nullptr;

    if (node->right == nullptr)
        return node;

    // get right node, which becomes a new root node
    BL_Node_ptr rnode = node->right;

    // establish connections with a root node if threre is one
    if (!isRoot(node)) {
        if (node->parent->left == node) {
            node->parent->left = rnode;
        }
        else {
            node->parent->right = rnode;
        }
    }
    rnode->parent = node->parent;

    // connect right subtree of the left child as a left subtree of `node`
    node->right = rnode->left;
    if (rnode->left != nullptr) {
        rnode->left->parent = node;
    }

    // connect `node` as a right child of it's child
    rnode->left = node;
    node->parent = rnode;

    // update height attribute
    updateHeight(node);
    updateHeight(rnode);
    updateHeight(rnode->parent);

    return rnode;
}


/**
 Performs rotation of a tree around `node` such that it goes to the right subtree
 */
BL_Node_ptr rotateRight(BL_Node_ptr node)
{
    if (node == nullptr)
        return nullptr;

    if (node->left == nullptr)
        return node;

    // left node becomes root node of subtree
    BL_Node_ptr lnode = node->left;

    // establish connections with a root node if threre is one
    if (!isRoot(node)) {
        if (node->parent->left == node) {
            node->parent->left = lnode;
        }
        else {
            node->parent->right = lnode;
        }
    }
    lnode->parent = node->parent;

    // connect right subtree of the left child as a left subtree of `node`
    node->left = lnode->right;
    if (lnode->right != nullptr) {
        lnode->right->parent = node;
    }

    // connect `node` as a right child of it's child
    lnode->right = node;
    node->parent = lnode;

    // update height attribute
    updateHeight(node);
    updateHeight(lnode);
    updateHeight(lnode->parent);

    return lnode;
}


/**
 Find a leaf in a tree such that x is under the parabolic arc,
 which corresponds to this leaf.
 */
BL_Node_ptr find(BL_Node_ptr root, double x)
{
    if (root == nullptr) {
        return nullptr;
    }
    BL_Node_ptr node = root;
    while (!node->isLeaf()) {
        if (node->value() < x) {
            node = node->right;
        }
        else {
            node = node->left;
        }
    }
    return node;
}


/**
 Replace a leaf `node` with a new subtree, which has root `new_node`.
 The function rebalances the tree and returns the pointer to a new root node.
 */
BL_Node_ptr replace(BL_Node_ptr node, BL_Node_ptr new_node)
{
    if (node == nullptr) {
        return new_node;
    }

    // Find x-coordinate
    double x = new_node->value();

    // Get a parent node
    BL_Node_ptr parent_node = node->parent;

    // Remove leaf, because it's replaced by a new subtree
    //        delete node;

    // Insert the node
    new_node->parent = parent_node;
    if (parent_node != nullptr) {
        if (parent_node->value() < x) {
            parent_node->right = new_node;
        }
        else {
            parent_node->left = new_node;
        }
    }

    // Rebalance the tree
    node = new_node;
    while (parent_node != nullptr) {
        updateHeight(parent_node);
        int balance = getBalance(parent_node);
        if (balance > 1) { // left subtree is higher than right subtree by more than 1
            if (parent_node->left != nullptr && !parent_node->left->isLeaf() && getBalance(parent_node->left) < 0) { // @TODO ensure that
                parent_node->left = rotateLeft(parent_node->left);
            }
            parent_node = rotateRight(parent_node);
        }
        else if (balance < -1) { // right subtree is lower than left subtree by more than 1
            if (parent_node->right != nullptr && !parent_node->right->isLeaf() && getBalance(parent_node->right) > 0) {
                parent_node->right = rotateRight(parent_node->right);
            }
            parent_node = rotateLeft(parent_node);
        }

        //_validate(parent_node);

        node = parent_node;
        parent_node = parent_node->parent;
    }

    //_check_balance(node);

    return node;
}

/**
 Remove a disappearing arc related to a circle event.
 The function rebalances the tree and returns the pointer to a new root node.
 */
BL_Node_ptr remove(BL_Node_ptr leaf)
{
    // General idea behind this code:
    // This function removes the leaf and it's parent corresponding to one breakpoint.
    // It moves up in a tree and rebalaces it. If function encounters second breakpoint,
    // it replaces this breakpoint with a new one. This is possible because when the circle
    // event appears, two breakpoints coincide and thus they should be represented by one.

    if (leaf == nullptr)
        return nullptr;

    BL_Node_ptr parent = leaf->parent, grandparent = parent->parent;
    std::pair<int,int> bp1(leaf->prev->getID(), leaf->getID());
    std::pair<int,int> bp2(leaf->getID(), leaf->next->getID());
    std::pair<int,int> other_bp;

    assert(leaf->next != nullptr);
    assert(leaf->prev != nullptr);
    assert(parent != nullptr);
    assert(grandparent != nullptr);

    assert(parent->hasIndices(bp1) || parent->hasIndices(bp2));

    if (parent->hasIndices(bp1)) {
        other_bp = bp2;
    }
    else if (parent->hasIndices(bp2)) {
        other_bp = bp1;
    }

    BL_Node_ptr other_subtree;
    if (parent->left == leaf)
        other_subtree = parent->right;
    else
        other_subtree = parent->left;

    other_subtree->parent = grandparent;
    if (grandparent->left == parent) {
        grandparent->left = other_subtree;
    }
    else {
        grandparent->right = other_subtree;
    }

    BL_Node_ptr new_root = grandparent;
    // Go up and rebalance the whole tree
    while (grandparent != nullptr) {
        if (grandparent->hasIndices(other_bp))
            grandparent->indices = std::make_pair(leaf->prev->getID(), leaf->next->getID());
        // update height of a node
        updateHeight(grandparent);
        // calculate balance factor of a node
        int balance = getBalance(grandparent);
        if (balance > 1) { // left subtree is higher than right subtree by more than 1
            if (grandparent->left != nullptr && !grandparent->left->isLeaf() && getBalance(grandparent->left) < 0) {
                grandparent->left = rotateLeft(grandparent->left);
            }
            grandparent = rotateRight(grandparent);
        }
        else if (balance < -1) { // right subtree is lower than left subtree by more than 1
            if (grandparent->right != nullptr && !grandparent->right->isLeaf() && getBalance(grandparent->right) > 0) {
                grandparent->right = rotateRight(grandparent->right);
            }
            grandparent = rotateLeft(grandparent);
        }

        //_validate(grandparent);

        new_root = grandparent;
        grandparent = grandparent->parent;
    }

    // Connect previous with next leaf
    connect(leaf->prev, leaf->next);

    //_check_balance(new_root);

    return new_root;
}


/**
 Returns breakpoints for a given arc
 */
std::pair<BL_Node_ptr, BL_Node_ptr> calculateBreakpoints(BL_Node_ptr leaf)
{
    if (leaf == nullptr || leaf->next == nullptr || leaf->prev == nullptr)
        return std::make_pair<BL_Node_ptr>(nullptr, nullptr);

    BL_Node_ptr parent = leaf->parent, gparent = leaf->parent;
    std::pair<int,int> bp1(leaf->prev->getID(), leaf->getID()); // left breakpoint
    std::pair<int,int> bp2(leaf->getID(), leaf->next->getID()); // right breakpoint
    std::pair<int,int> other_bp;

    bool left_is_missing = true;

    if (parent->hasIndices(bp1)) {
        other_bp = bp2;
        left_is_missing = false;
    }
    else if (parent->hasIndices(bp2)) {
        other_bp = bp1;
        left_is_missing = true;
    }

    // Go up and rebalance the whole tree
    while (gparent != nullptr) {
        if (gparent->hasIndices(other_bp)) {
            break;
        }
        gparent = gparent->parent;
    }

    if (left_is_missing) {
        return std::make_pair(gparent, parent);
    }
    else {
        return std::make_pair(parent, gparent);
    }
}


BL_Node_ptr makeSubtree(int index
                      , int index_behind
                      , double* sweep_line
                      , const std::vector<Point>* points
                      , std::vector<Half_Edge_ptr> edges)
{
    // create nodes corresponding to branching points
    BL_Node_ptr node1 = std::make_shared<BL_Node>(std::make_pair(index_behind, index), sweep_line, points);
    BL_Node_ptr node2 = std::make_shared<BL_Node>(std::make_pair(index, index_behind), sweep_line, points);

    // create leaf nodes
    BL_Node_ptr leaf1 = std::make_shared<BL_Node>(std::make_pair(index_behind, index_behind), sweep_line, points);
    BL_Node_ptr leaf2 = std::make_shared<BL_Node>(std::make_pair(index, index), sweep_line, points);
    BL_Node_ptr leaf3 = std::make_shared<BL_Node>(std::make_pair(index_behind, index_behind), sweep_line, points);

    // adjust tree connections
    node1->right = node2;
    node2->parent = node1;

    node1->left = leaf1;
    leaf1->parent = node1;

    node2->left = leaf2;
    leaf2->parent = node2;

    node2->right = leaf3;
    leaf3->parent = node2;

    // add halfedges
    std::pair<Half_Edge_ptr, Half_Edge_ptr> twin_edges = makeTwins(index_behind, index);
    node1->edge = twin_edges.first;//second;//first;
    node2->edge = twin_edges.second;//first;//second;

    edges.push_back(twin_edges.first);
    edges.push_back(twin_edges.second);

    // connect leaf nodes
    connect(leaf1, leaf2);
    connect(leaf2, leaf3);

    // reset height of a node
    updateHeight(node2);
    updateHeight(node1);

    // return the result
    return node1;
}


BL_Node_ptr makeSimpleSubtree(int index
                            , int index_behind
                            , double *sweep_line
                            , const std::vector<Point> *points
                            , std::vector<Half_Edge_ptr> &edges)
{
    BL_Node_ptr node, leaf_l, leaf_r;

    std::pair<Half_Edge_ptr, Half_Edge_ptr> twin_edges = makeTwins(index_behind, index);

    edges.push_back(twin_edges.first);
    edges.push_back(twin_edges.second);

    if ((*points)[index].x < (*points)[index_behind].x) {
        // Depends on the point order
        node = std::make_shared<BL_Node>(std::make_pair(index, index_behind), sweep_line, points);
        leaf_l = std::make_shared<BL_Node>(std::make_pair(index, index), sweep_line, points);
        leaf_r = std::make_shared<BL_Node>(std::make_pair(index_behind, index_behind), sweep_line, points);
        node->edge = twin_edges.second;//twin_edges.first;
    }
    else {
        node = std::make_shared<BL_Node>(std::make_pair(index_behind, index), sweep_line, points);
        leaf_l = std::make_shared<BL_Node>(std::make_pair(index_behind, index_behind), sweep_line, points);
        leaf_r = std::make_shared<BL_Node>(std::make_pair(index, index), sweep_line, points);
        node->edge = twin_edges.first;//twin_edges.second;
    }

    node->left = leaf_l;
    node->right = leaf_r;

    leaf_l->parent = node;
    leaf_r->parent = node;

    connect(leaf_l, leaf_r);
    updateHeight(node);

    return node;
}


bool _validate(BL_Node_ptr node)
{
    if (node == nullptr) {
        return true;
    }

    if (node->isLeaf()) {
        if (node->left != nullptr || node->right != nullptr) {
            std::cout << "LEAF NOT A LEAF: " << node->indices.first << ", " << node->indices.second << std::endl;
            return false;
        }
    }
    else {
        if (node->left == nullptr || node->right == nullptr) {
            std::cout << " BP WITHOUT LEAF: " << node->indices.first << ", " << node->indices.second << std::endl;
            return false;
        }
    }
    return true;
}

bool _check_balance(BL_Node_ptr node)
{
    if (node == nullptr) return true;
    if (_check_balance(node->left) && _check_balance(node->right)) {
        if (fabs(getBalance(node)) > 1) {

            std::cout << "+unbalanced (" << node->indices.first << ", " << node->indices.second << ")" << std::endl;

            return false;
        }
    }
    return true;
}

} // namespace Voronoi
