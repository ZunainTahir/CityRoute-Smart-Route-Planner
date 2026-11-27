#include "OSMParser.h"
#include <fstream>
#include <cstdlib>

string OSMParser::getAttribute(const string& line, const string& name) const {
    string quotes = "\"'";
    for (int q = 0; q < 2; q++) {
        char quote = quotes[q];
        string key = " " + name + "=" + quote;
        size_t start = line.find(key);
        if (start != string::npos) {
            start = start + key.length();
            size_t end = line.find(quote, start);
            if (end != string::npos) {
                return line.substr(start, end - start);
            }
        }
    }
    return "";
}

int OSMParser::loadNodes(const string& filename, Graph& graph) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        return -1;
    }

    int added = 0;
    string line;
    while (getline(file, line)) {
        if (line.find("<node ") == string::npos) {
            continue;
        }

        string idText = getAttribute(line, "id");
        string latText = getAttribute(line, "lat");
        string lonText = getAttribute(line, "lon");
        if (idText == "" || latText == "" || lonText == "") {
            continue;
        }

        long long id = atoll(idText.c_str());
        double lat = atof(latText.c_str());
        double lon = atof(lonText.c_str());
        if (id == 0 || lat < -90 || lat > 90 || lon < -180 || lon > 180) {
            continue;
        }

        int before = graph.getNodeCount();
        graph.addNode(id, lat, lon);
        if (graph.getNodeCount() > before) {
            added++;
        }
    }

    file.close();
    return added;
}
