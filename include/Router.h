#pragma once
// ---------------------------------------------------------------------------
// Router.h  --  INTERFACE CONTRACT (Day 1)
// Owner: Member 1.  Implementation: src/Router.cpp (Days 8-13).
//
// Member 3's TripPlanner uses shortestDistanceKm() and dijkstra().
// Until the real code lands (Day 8) use a stub with the same signature.
// ---------------------------------------------------------------------------

#include <vector>

#include "Graph.h"

enum class Metric { Distance, Time };

struct PathResult {
    bool found = false;
    double totalDistanceKm = 0.0;
    double totalTimeMin = 0.0;
    int nodesVisited = 0;        // how many nodes the algorithm settled (benchmarking)
    std::vector<int> nodes;      // node indices from source to destination
};

class Router {
public:
    explicit Router(const Graph& graph);

    // Shortest path with a binary min-heap (Dijkstra).
    PathResult dijkstra(int source, int destination, Metric metric = Metric::Distance) const;

    // A* with a Haversine heuristic.
    PathResult aStar(int source, int destination, Metric metric = Metric::Distance) const;

    // Fewest road segments (BFS). Ignores weights.
    PathResult bfs(int source, int destination) const;

    // Connectivity check (DFS).
    bool isConnected(int a, int b) const;

    // Convenience for the trip planner: distance of the shortest route in km,
    // or -1.0 if the destination cannot be reached.
    double shortestDistanceKm(int source, int destination) const;
};
