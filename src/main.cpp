#include "dijkstra.h"
#include "raylib.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>

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

  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}