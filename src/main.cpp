#include "dijkstra.h"
#include "raylib.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <string>

#include "graph.h"

using namespace std;
using namespace graph;

struct Node {
  Arc<int> arc;
  float x;
  float y;
};

std::ostream &operator<<(std::ostream &os, const Node &node) {
  cout << "Node<"
    << node.arc
    << " ("
    << node.x
    << ", "
    << node.y
    << ")"
    << ">";
  return os;
}

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type>
    dist0_100(0, 100);

auto arc2node(Arc<int> const &arc) {
  auto [a, b, w] = arc;
  return Node {
    Arc<int>{a, b, w},
    static_cast<float>(dist0_100(rng)),
    static_cast<float>(dist0_100(rng)),
    };
}


int main(int argc, char **argv) {
  string program = argv[0];
  if (argc < 2) {
    cout << "usage: " << program << " <graph-file>" << endl;
    return 1;
  }
  auto graph = lines2graph<int>(readFileLines(argv[1]));
  auto [path, distance] = dijkstra_path("S", "F", graph);
  
  vector<Node> nodes;
  transform(graph.begin(), graph.end(), back_inserter(nodes), arc2node);

  const int screenWidth = 800;
  const int screenHeight = 450;
  
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  
  SetTargetFPS(60);
  
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();
    
    ClearBackground(RAYWHITE);

    for_each(nodes.begin(), nodes.end(), [](Node const &node) {
      auto [arc, x, y] = node;
      DrawCircle(x, y, 10.0, RED);
    });
    
    EndDrawing();
  }
  
  CloseWindow(); // Close window and OpenGL context
  
  return 0;
}