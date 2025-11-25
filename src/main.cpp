#include "dijkstra.h"
// #include "raylib.h"
// #include "smacof.h"
#include "utils.h"
// #include <algorithm>
#include <iostream>
// #include <iterator>
#include <random>
// #include <string>

#include "graph.h"

using namespace std;
using namespace graph;

random_device dev; 
mt19937 rng(dev());
uniform_int_distribution<int>
    dist0_100(0, 100);

// auto arc2arcXY(Arc<float> const &arc) {
//   auto [a, b, w] = arc;
//   return ArcXY<float> {
//     Arc<float>{a, b, w},
//     static_cast<float>(dist0_100(rng)),
//     static_cast<float>(dist0_100(rng)),
//     };
// }

// bool iterate_arcXYs(vector<ArcXY<float>> &arcXYs) { return graph_algorithm::iterate_smacof(arcXYs); }

int main(int argc, char **argv) {
  string program = argv[0];
  if (argc < 2) {
    cout << "usage: " << program << " <graph-file>" << endl;
    return 1;
  }
  auto graph = lines2graph<float>(readFileLines(argv[1]));
  auto [path, distance] = dijkstra_path("S", "F", graph);
  
  // vector<ArcXY<float>> arcXYs;
  // transform(graph.begin(), graph.end(), back_inserter(arcXYs), arc2arcXY);

  // iterate_arcXYs(arcXYs);

  // const int screenWidth = 800;
  // const int screenHeight = 450;
  
  // InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  
  // SetTargetFPS(60);
  // bool balanced = false;

  // while (!WindowShouldClose()) // Detect window close button or ESC key
  // {
  //   if (!balanced) {
  //     balanced = iterate_arcXYs(arcXYs);
  //   }

  //   BeginDrawing();
    
  //   ClearBackground(RAYWHITE);

  //   for_each(arcXYs.begin(), arcXYs.end(), [](ArcXY<float> const &arcXY) {
  //     auto [arc, x, y] = arcXY;
  //     DrawCircle(10.0 + (x * 8.0), 10.0 + (4.0 * y), 10.0, RED);
  //   });
    
  //   EndDrawing();
  // }
  
  // CloseWindow(); // Close window and OpenGL context
  
  return 0;
}