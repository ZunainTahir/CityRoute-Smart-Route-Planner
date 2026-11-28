#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "Graph.h"
#include "OSMParser.h"
using namespace std;

int failures = 0;

void check(bool ok, string name) {
    if (!ok) {
        cout << "FAILED: " << name << endl;
        failures++;
    }
}

void writeSampleFile(string fileName) {
    ofstream out(fileName.c_str());
    out << "<?xml version='1.0' encoding='UTF-8'?>" << endl;
    out << "<osm version=\"0.6\" generator=\"test\">" << endl;
    out << " <bounds minlat=\"33.6\" minlon=\"73.0\" maxlat=\"33.8\" maxlon=\"73.2\"/>" << endl;
    out << " <node id=\"1001\" visible=\"true\" version=\"2\" uid=\"55\" user=\"ali\" lat=\"33.6844\" lon=\"73.0479\"/>" << endl;
    out << " <node id=\"1002\" visible=\"true\" version=\"1\" lat=\"33.7000\" lon=\"73.0600\">" << endl;
    out << "  <tag k=\"name\" v=\"Saddar\"/>" << endl;
    out << " </node>" << endl;
    out << " <node lat=\"33.7100\" lon=\"73.0700\" id=\"1003\"/>" << endl;
    out << " <node id='1004' lat='33.7200' lon='73.0800'/>" << endl;
    out << " <node id=\"1001\" lat=\"1.0\" lon=\"2.0\"/>" << endl;
    out << " <node id=\"1005\" lon=\"73.09\"/>" << endl;
    out << " <node id=\"1006\" lat=\"95.0\" lon=\"73.09\"/>" << endl;
    out << " <way id=\"9001\">" << endl;
    out << "  <nd ref=\"1001\"/>" << endl;
    out << "  <nd ref=\"1002\"/>" << endl;
    out << "  <tag k=\"highway\" v=\"residential\"/>" << endl;
    out << " </way>" << endl;
    out << " <relation id=\"1\"><member type=\"node\" ref=\"1001\" role=\"\"/></relation>" << endl;
    out << "</osm>" << endl;
    out.close();
}

void testSampleFile() {
    writeSampleFile("test_small.osm");

    Graph graph;
    OSMParser parser;
    int loaded = parser.loadNodes("test_small.osm", graph);

    check(loaded == 4, "four valid nodes loaded");
    check(graph.getNodeCount() == 4, "graph has four nodes");
    check(graph.indexOfOsmId(1001) == 0, "1001 is the first node");
    check(graph.indexOfOsmId(1002) == 1, "1002 with a tag inside is loaded");
    check(graph.indexOfOsmId(1003) == 2, "1003 with attributes in another order");
    check(graph.indexOfOsmId(1004) == 3, "1004 with single quotes");
    check(graph.indexOfOsmId(55) == -1, "uid is not read as id");
    check(graph.indexOfOsmId(1005) == -1, "node without lat is skipped");
    check(graph.indexOfOsmId(1006) == -1, "node with a bad latitude is skipped");

    const Node* first = graph.getNode(0);
    check(first->lat > 33.684 && first->lat < 33.685, "latitude of 1001");
    check(first->lon > 73.047 && first->lon < 73.048, "longitude of 1001");
    check(graph.getNode(2)->lat > 33.709 && graph.getNode(2)->lat < 33.711, "latitude of 1003");

    int again = parser.loadNodes("test_small.osm", graph);
    check(again == 0, "loading the same file again adds nothing");
    check(graph.getNodeCount() == 4, "still four nodes");

    remove("test_small.osm");
}

void testMissingAndEmptyFile() {
    Graph graph;
    OSMParser parser;
    check(parser.loadNodes("this_file_is_not_here.osm", graph) == -1, "missing file gives -1");

    ofstream out("test_empty.osm");
    out.close();
    check(parser.loadNodes("test_empty.osm", graph) == 0, "empty file gives 0");
    check(graph.getNodeCount() == 0, "graph stays empty");
    remove("test_empty.osm");
}

void testManyNodes() {
    ofstream out("test_many.osm");
    out << "<osm version=\"0.6\">" << endl;
    for (int i = 0; i < 2500; i++) {
        out << " <node id=\"" << (5000000 + i * 3) << "\" lat=\"" << (33.0 + i * 0.0001)
            << "\" lon=\"" << (73.0 + i * 0.0001) << "\"/>" << endl;
    }
    out << "</osm>" << endl;
    out.close();

    Graph graph;
    OSMParser parser;
    check(parser.loadNodes("test_many.osm", graph) == 2500, "2500 nodes loaded");
    check(graph.getNodeCount() == 2500, "graph grew past its first size");
    check(graph.indexOfOsmId(5000000 + 2499 * 3) == 2499, "last node found by osm id");
    remove("test_many.osm");
}

int main() {
    testSampleFile();
    testMissingAndEmptyFile();
    testManyNodes();

    if (failures == 0) {
        cout << "test_osm_parser: all passed" << endl;
        return 0;
    }
    cout << "test_osm_parser: " << failures << " failed" << endl;
    return 1;
}
