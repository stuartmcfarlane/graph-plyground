#include "dijkstra.h"
#include "raylib.h"
#include "utils.h"
#include <iostream>
#include <string>

#include "graph.h"

using namespace std;
using namespace graph;

int main(int argc, char **argv) {
  string program = argv[0];
  if (argc < 2) {
    cout << "usage: " << program << " <graph-file>" << endl;
    return 1;
  }
  auto graph = lines2graph<int>(readFileLines(argv[1]));
  auto [path, distance] = dijkstra_path("S", "F", graph);

  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow(); // Close window and OpenGL context

  return 0;
}