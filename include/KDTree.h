#pragma once
// ---------------------------------------------------------------------------
// KDTree.h  --  INTERFACE CONTRACT (Day 1)
// Owner: Member 1.  Implementation: src/KDTree.cpp (Days 11-12).
//
// 2-D tree over all intersections, used to snap any GPS point to the
// nearest road node.
// ---------------------------------------------------------------------------

#include "Graph.h"

class KDTree {
public:
    KDTree();
    ~KDTree();

    // Builds the tree (recursively) from every node of the graph.
    void build(const Graph& graph);

    // Returns the index of the node closest to (lat, lon), or -1 if the tree
    // is empty. If outDistanceKm is not null it receives the distance.
    int nearest(double lat, double lon, double* outDistanceKm = nullptr) const;

    bool empty() const;
};
