#include "dijkstra.h"
#include "raylib.h"
#include "smacof.h"
#include "utils.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <utility>

#include "graph.h"

using namespace std;
using namespace graph;
using namespace graph_algorithm;

random_device dev; 
mt19937 rng(dev());
uniform_int_distribution<int>
    dist0_100(0, 100);

Point randomPoint() {
  return Point{
    static_cast<float>(dist0_100(rng)),
    static_cast<float>(dist0_100(rng)),
  };
}

Point scalePoint(const Point &p) {
  auto [x, y] = p;
  float px = 10.0 + (x * 8.0);
  float py = 10.0 + (4.0 * y);
  return Point{px, py};
}

int main(int argc, char **argv) {
  string program = argv[0];
  if (argc < 2) {
    cout << "usage: " << program << " <graph-file>" << endl;
    return 1;
  }
  auto graph = lines2graph<float>(readFileLines(argv[1]));
  auto [path, distance] = dijkstra_path("S", "F", graph);
  vector<Arc<string, float>> pathArcs;
  string lastNode = path[0];
  for (auto node : path) {
    if (node == lastNode)
      continue;
    pathArcs.push_back(Arc{lastNode, node, graph.weightOf(lastNode, node)});
    lastNode = node;
  }

  std::map<string, Point> pointByNode;
  for (auto node : graph.nodes) {
    pointByNode[node] = randomPoint();
  }

  iterate_smacof(pointByNode, graph);

  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  
  SetTargetFPS(60);
  bool balanced = false;

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();
    
    ClearBackground(RAYWHITE);

    ranges::for_each(graph.arcs, [pointByNode](const Arc<string, float> &arc) {
      auto [a, b, w] = arc;
      auto [ax, ay] = scalePoint(pointByNode.at(a));
      auto [bx, by] = scalePoint(pointByNode.at(b));
      DrawLine(ax, ay, bx, by, BLUE);
    });
    string lastNode = path[0];
    int i = 0;
    ranges::for_each(pathArcs, [pointByNode](auto arc) {
      auto [a, b, w] = arc;
      auto [ax, ay] = scalePoint(pointByNode.at(a));
      auto [bx, by] = scalePoint(pointByNode.at(b));
      DrawLine(ax, ay, bx, by, GREEN);
    });
    ranges::for_each(pointByNode, [](pair<string, Point> const &nodePoint) {
      auto [node, point] = nodePoint;
      auto [x, y] = scalePoint(point);
      auto color = (node == "S" ? GREEN : node == "F" ? RED : BLACK);
      DrawCircle(x, y, 10.0, color);
    });

    EndDrawing();
  }
  
  CloseWindow(); // Close window and OpenGL context
  
  return 0;
}