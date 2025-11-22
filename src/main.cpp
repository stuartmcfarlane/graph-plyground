#include "dijkstra.h"
#include "utils.h"
#include <string>
#include <vector>
#include <iostream>
#include "graph.h"

using namespace std;
using namespace graph;

int main(int argc, char **argv) {
  string program = argv[0];
  if (argc < 2) {
    cout << "usage: " << program << " <graph-file> ..." << endl;
    return 1;
  }
  int argi = 0;
  while (++argi < argc) {
    string inputFile = argv[argi];
    cout << inputFile << endl;
    vector<string> input = readFileLines(inputFile);
    auto graph = lines2graph<int>(input);
    auto pathAndDistance = dijkstra_path("S", "F", graph);
    auto [path, distance] = pathAndDistance;
    for( auto p : path) {
      cout << p << " ";
    }
    cout << "= " << distance << endl;
  }
  return 0;
}