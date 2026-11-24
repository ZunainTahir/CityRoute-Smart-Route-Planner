#pragma once
#include "Graph.h"

class KDTree {
public:
    KDTree();
    ~KDTree();

    void build(const Graph& graph);
    int nearest(double lat, double lon, double* outDistanceKm = nullptr) const;
    bool isEmpty() const;
};
