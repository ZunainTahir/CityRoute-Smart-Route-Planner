#include <iostream>
#include <string>
#include "Graph.h"
#include "OSMParser.h"
using namespace std;

int main(int argc, char* argv[]) {
    string fileName = "data/sample.osm";
    if (argc > 1) {
        fileName = argv[1];
    }

    Graph graph;
    OSMParser parser;
    int loaded = parser.loadNodes(fileName, graph);
    if (loaded < 0) {
        cout << "Could not open " << fileName << endl;
        return 1;
    }

    cout << "CityRoute - Smart Route Planner" << endl;
    cout << "Loaded " << loaded << " nodes from " << fileName << endl;
    return 0;
}
