#include "tests.h"
#include "utils.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
  vector<string> input = readFileLines("data/graph2");
  auto pathAndDistance = dijkstra_test("S", "F", input);
  auto path = pathAndDistance.first;
  auto distance = pathAndDistance.second;
  for( auto p = path.begin(); p != path.end(); *p++) {
    cout << *p << " ";
  }
  cout << "= " << distance << endl;
  return 0;
}