#pragma once
#include <string>
#include "Graph.h"
using namespace std;

class OSMParser {
private:
    string getAttribute(const string& line, const string& name) const;

public:
    int loadNodes(const string& filename, Graph& graph);
};
