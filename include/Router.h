#pragma once
#include "Graph.h"

enum Metric { BY_DISTANCE, BY_TIME };

struct PathResult {
    double totalDistanceKm;
    double totalTimeMin;
    int nodesVisited;
    int* nodes;
    int nodeCount;

    PathResult() {
        totalDistanceKm = 0;
        totalTimeMin = 0;
        nodesVisited = 0;
        nodes = nullptr;
        nodeCount = 0;
    }

    ~PathResult() {
        delete[] nodes;
    }

    PathResult(const PathResult&) = delete;
    PathResult& operator=(const PathResult&) = delete;
};

class Router {
public:
    Router(const Graph& graph);

    bool dijkstra(int source, int destination, PathResult& result, Metric metric = BY_DISTANCE) const;
    bool aStar(int source, int destination, PathResult& result, Metric metric = BY_DISTANCE) const;
    bool bfs(int source, int destination, PathResult& result) const;

    bool isConnected(int a, int b) const;

    double shortestDistanceKm(int source, int destination) const;
};
