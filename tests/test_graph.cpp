#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;

int failures = 0;

void check(bool ok, string name) {
    if (!ok) {
        cout << "FAILED: " << name << endl;
        failures++;
    }
}

int countNeighbors(const Graph& g, int index) {
    int total = 0;
    EdgeNode* p = g.getNeighbors(index)->getHead();
    while (p != nullptr) {
        total++;
        p = p->next;
    }
    return total;
}

bool hasNeighbor(const Graph& g, int from, int to) {
    EdgeNode* p = g.getNeighbors(from)->getHead();
    while (p != nullptr) {
        if (p->data.to == to) {
            return true;
        }
        p = p->next;
    }
    return false;
}

bool isBlocked(const Graph& g, int from, int to) {
    EdgeNode* p = g.getNeighbors(from)->getHead();
    while (p != nullptr) {
        if (p->data.to == to) {
            return p->data.blocked;
        }
        p = p->next;
    }
    return false;
}

void testAddNode() {
    Graph g;
    check(g.getNodeCount() == 0, "starts empty");

    int a = g.addNode(1001, 33.6844, 73.0479);
    int b = g.addNode(1002, 33.7000, 73.0600);
    check(a == 0 && b == 1, "indexes go 0, 1");
    check(g.getNodeCount() == 2, "two nodes");
    check(g.indexOfOsmId(1001) == 0, "lookup 1001");
    check(g.indexOfOsmId(1002) == 1, "lookup 1002");
    check(g.indexOfOsmId(9999) == -1, "unknown osm id");
    check(g.getNode(1)->osmId == 1002, "node 1 osm id");
    check(g.getNode(1)->index == 1, "node 1 index");
    check(g.getNode(1)->lat > 33.69 && g.getNode(1)->lat < 33.71, "node 1 latitude");
}

void testDuplicateNode() {
    Graph g;
    int first = g.addNode(500, 1.0, 2.0);
    int again = g.addNode(500, 9.0, 9.0);
    check(first == again, "same osm id gives same index");
    check(g.getNodeCount() == 1, "no second node added");
    check(g.getNode(0)->lat == 1.0, "old data is kept");
}

void testTwoWayEdge() {
    Graph g;
    int a = g.addNode(1, 0, 0);
    int b = g.addNode(2, 0, 1);
    check(g.addEdge(a, b, 2.5, 4.0, "Murree Road", false), "add two way road");

    check(g.getEdgeCount() == 2, "counted in both directions");
    check(hasNeighbor(g, a, b), "a -> b");
    check(hasNeighbor(g, b, a), "b -> a");
    check(g.getNeighbors(a)->front()->roadName == "Murree Road", "road name");
    check(g.getNeighbors(b)->front()->distanceKm == 2.5, "distance on reverse edge");
    check(g.getNeighbors(b)->front()->timeMin == 4.0, "time on reverse edge");
    check(!g.getNeighbors(a)->front()->blocked, "not blocked at start");
}

void testOneWayEdge() {
    Graph g;
    int a = g.addNode(1, 0, 0);
    int b = g.addNode(2, 0, 1);
    g.addEdge(a, b, 1.0, 1.0, "Jinnah Avenue", true);

    check(g.getEdgeCount() == 1, "one edge only");
    check(hasNeighbor(g, a, b), "a -> b exists");
    check(!hasNeighbor(g, b, a), "b -> a does not exist");
}

void testSmallNetwork() {
    Graph g;
    for (int i = 0; i < 5; i++) {
        g.addNode(1000 + i, 0, i);
    }
    g.addEdge(0, 1, 1, 1, "A", false);
    g.addEdge(1, 2, 1, 1, "B", false);
    g.addEdge(0, 3, 1, 1, "C", false);
    g.addEdge(2, 4, 1, 1, "D", false);
    g.addEdge(3, 4, 1, 1, "E", true);

    check(g.getNodeCount() == 5, "five nodes");
    check(g.getEdgeCount() == 9, "8 edges from the two way roads + 1 one way");
    check(countNeighbors(g, 0) == 2, "node 0 has 2 neighbors");
    check(countNeighbors(g, 3) == 2, "node 3 has 2 neighbors");
    check(countNeighbors(g, 4) == 1, "node 4 has 1 neighbor");
    check(hasNeighbor(g, 3, 4) && !hasNeighbor(g, 4, 3), "3 -> 4 is one way");
}

void testBlock() {
    Graph g;
    int a = g.addNode(1, 0, 0);
    int b = g.addNode(2, 0, 1);
    int c = g.addNode(3, 0, 2);
    g.addEdge(a, b, 1, 1, "X", false);
    g.addEdge(b, c, 1, 1, "Y", false);

    check(g.setEdgeBlocked(a, b, true), "block a-b");
    check(isBlocked(g, a, b), "a -> b is blocked");
    check(isBlocked(g, b, a), "b -> a is blocked too");
    check(!isBlocked(g, b, c), "b -> c is still open");

    check(g.setEdgeBlocked(b, a, false), "open it again with swapped order");
    check(!isBlocked(g, a, b), "a -> b is open");
    check(!isBlocked(g, b, a), "b -> a is open");

    check(!g.setEdgeBlocked(a, c, true), "no road between a and c");
    check(!g.setEdgeBlocked(a, 7, true), "bad index");
}

void testBadInput() {
    Graph g;
    g.addNode(1, 0, 0);
    g.addNode(2, 0, 1);

    check(!g.addEdge(0, 5, 1, 1, "bad", false), "bad to index");
    check(!g.addEdge(-1, 1, 1, 1, "bad", false), "bad from index");
    check(!g.addEdge(0, 1, -1.0, 1.0, "bad", false), "negative distance");
    check(!g.addEdge(0, 1, 1.0, -1.0, "bad", false), "negative time");
    check(!g.addEdge(0, 0, 1.0, 1.0, "loop", false), "road from a node to itself");
    check(g.getEdgeCount() == 0, "nothing was added");

    check(g.getNode(2) == nullptr, "getNode too big");
    check(g.getNode(-1) == nullptr, "getNode negative");
    check(g.getNeighbors(2) == nullptr, "getNeighbors too big");
}

void testGrow() {
    Graph g(2);
    int n = 50000;
    for (int i = 0; i < n; i++) {
        g.addNode(1000000000LL + i * 7LL, 33.0 + i * 0.00001, 73.0 + i * 0.00001);
    }
    for (int i = 0; i + 1 < n; i++) {
        g.addEdge(i, i + 1, 0.01, 0.02, "chain", false);
    }

    check(g.getNodeCount() == n, "50000 nodes");
    check(g.getEdgeCount() == 2 * (n - 1), "chain edges");
    check(g.indexOfOsmId(1000000000LL + 49999 * 7LL) == 49999, "lookup of the last node");
    check(countNeighbors(g, 25000) == 2, "middle node has 2 neighbors");
}

int main() {
    testAddNode();
    testDuplicateNode();
    testTwoWayEdge();
    testOneWayEdge();
    testSmallNetwork();
    testBlock();
    testBadInput();
    testGrow();

    if (failures == 0) {
        cout << "test_graph: all passed" << endl;
        return 0;
    }
    cout << "test_graph: " << failures << " failed" << endl;
    return 1;
}
