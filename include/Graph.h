#pragma once
// ---------------------------------------------------------------------------
// Graph.h  --  INTERFACE CONTRACT (Day 1)
// Owner: Member 1.  Implementation: src/Graph.cpp (Day 2 onwards).
//
// The road network: intersections are Nodes, road segments are Edges.
// Adjacency lists use Member 2's SinglyLinkedList<T> (include/SinglyLinkedList.h,
// due Day 3). Until then it is only forward-declared here.
// ---------------------------------------------------------------------------

#include <cstddef>
#include <string>

template <typename T>
class SinglyLinkedList;  // provided by Member 2

struct Node {
    int index = -1;         // internal index 0..nodeCount-1
    long long osmId = 0;    // original (huge, sparse) OpenStreetMap id
    double lat = 0.0;       // degrees
    double lon = 0.0;       // degrees
};

struct Edge {
    int to = -1;            // index of the destination node
    double distanceKm = 0.0;
    double timeMin = 0.0;   // estimated from an average speed per road type
    bool blocked = false;   // true = road closed by an Admin
    std::string roadName;
};

class Graph {
public:
    Graph();
    ~Graph();

    // Adds an intersection and returns its internal index.
    int addNode(long long osmId, double lat, double lon);

    // Adds a road segment from -> to. If oneWay is false the reverse edge
    // (to -> from) is added automatically with the same weights.
    void addEdge(int from, int to, double distanceKm, double timeMin,
                 const std::string& roadName, bool oneWay);

    std::size_t nodeCount() const;
    std::size_t edgeCount() const;

    // Node by internal index (0 <= index < nodeCount()).
    const Node& node(int index) const;

    // Hash-map lookup: OSM id -> internal index, or -1 if unknown.
    int indexOfOsmId(long long osmId) const;

    // Outgoing edges of a node.
    const SinglyLinkedList<Edge>& neighbors(int index) const;

    // Admin feature: close/open the edge from -> to (both directions are
    // updated for two-way roads). Returns false if no such edge exists.
    bool setEdgeBlocked(int from, int to, bool blocked);

    // Private data members are added together with the implementation.
};
