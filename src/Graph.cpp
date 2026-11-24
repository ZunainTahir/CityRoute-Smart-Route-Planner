#include "Graph.h"

Graph::Graph(int startCapacity) {
    if (startCapacity < 1) {
        startCapacity = 1;
    }
    capacity = startCapacity;
    nodeCount = 0;
    edgeCount = 0;
    nodes = new Node[capacity];
    adjacency = new SinglyLinkedList<Edge>*[capacity];
}

Graph::~Graph() {
    for (int i = 0; i < nodeCount; i++) {
        delete adjacency[i];
    }
    delete[] adjacency;
    delete[] nodes;
}

void Graph::grow() {
    int newCapacity = capacity * 2;
    Node* newNodes = new Node[newCapacity];
    SinglyLinkedList<Edge>** newAdj = new SinglyLinkedList<Edge>*[newCapacity];

    for (int i = 0; i < nodeCount; i++) {
        newNodes[i] = nodes[i];
        newAdj[i] = adjacency[i];
    }

    delete[] nodes;
    delete[] adjacency;
    nodes = newNodes;
    adjacency = newAdj;
    capacity = newCapacity;
}

bool Graph::validIndex(int index) const {
    return index >= 0 && index < nodeCount;
}

int Graph::addNode(long long osmId, double lat, double lon) {
    unordered_map<long long, int>::iterator found = osmToIndex.find(osmId);
    if (found != osmToIndex.end()) {
        return found->second;
    }

    if (nodeCount == capacity) {
        grow();
    }

    nodes[nodeCount].index = nodeCount;
    nodes[nodeCount].osmId = osmId;
    nodes[nodeCount].lat = lat;
    nodes[nodeCount].lon = lon;
    adjacency[nodeCount] = new SinglyLinkedList<Edge>();
    osmToIndex[osmId] = nodeCount;

    nodeCount++;
    return nodeCount - 1;
}

bool Graph::addEdge(int from, int to, double distanceKm, double timeMin,
                    const string& roadName, bool oneWay) {
    if (!validIndex(from) || !validIndex(to)) {
        return false;
    }
    if (distanceKm < 0 || timeMin < 0) {
        return false;
    }
    if (from == to) {
        return false;
    }

    Edge e;
    e.to = to;
    e.distanceKm = distanceKm;
    e.timeMin = timeMin;
    e.roadName = roadName;
    adjacency[from]->pushBack(e);
    edgeCount++;

    if (!oneWay) {
        Edge back = e;
        back.to = from;
        adjacency[to]->pushBack(back);
        edgeCount++;
    }
    return true;
}

int Graph::getNodeCount() const {
    return nodeCount;
}

int Graph::getEdgeCount() const {
    return edgeCount;
}

const Node* Graph::getNode(int index) const {
    if (!validIndex(index)) {
        return nullptr;
    }
    return &nodes[index];
}

const SinglyLinkedList<Edge>* Graph::getNeighbors(int index) const {
    if (!validIndex(index)) {
        return nullptr;
    }
    return adjacency[index];
}

int Graph::indexOfOsmId(long long osmId) const {
    unordered_map<long long, int>::const_iterator found = osmToIndex.find(osmId);
    if (found == osmToIndex.end()) {
        return -1;
    }
    return found->second;
}

bool Graph::setEdgeBlocked(int from, int to, bool blocked) {
    if (!validIndex(from) || !validIndex(to)) {
        return false;
    }

    bool found = false;

    EdgeNode* p = adjacency[from]->getHead();
    while (p != nullptr) {
        if (p->data.to == to) {
            p->data.blocked = blocked;
            found = true;
        }
        p = p->next;
    }

    p = adjacency[to]->getHead();
    while (p != nullptr) {
        if (p->data.to == from) {
            p->data.blocked = blocked;
            found = true;
        }
        p = p->next;
    }

    return found;
}
