#pragma once
#include <string>
#include <unordered_map>
#include "SinglyLinkedList.h"
using namespace std;

struct Node {
    int index;
    long long osmId;
    double lat;
    double lon;

    Node() {
        index = -1;
        osmId = 0;
        lat = 0;
        lon = 0;
    }
};

struct Edge {
    int to;
    double distanceKm;
    double timeMin;
    bool blocked;
    string roadName;

    Edge() {
        to = -1;
        distanceKm = 0;
        timeMin = 0;
        blocked = false;
    }
};

typedef SinglyLinkedList<Edge>::ListNode EdgeNode;

class Graph {
private:
    Node* nodes;
    SinglyLinkedList<Edge>** adjacency;
    int nodeCount;
    int edgeCount;
    int capacity;
    unordered_map<long long, int> osmToIndex;

    void grow();
    bool validIndex(int index) const;

public:
    Graph(int startCapacity = 1000);
    ~Graph();

    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    int addNode(long long osmId, double lat, double lon);

    bool addEdge(int from, int to, double distanceKm, double timeMin,
                 const string& roadName, bool oneWay);

    int getNodeCount() const;
    int getEdgeCount() const;

    const Node* getNode(int index) const;
    const SinglyLinkedList<Edge>* getNeighbors(int index) const;

    int indexOfOsmId(long long osmId) const;

    bool setEdgeBlocked(int from, int to, bool blocked);
};
