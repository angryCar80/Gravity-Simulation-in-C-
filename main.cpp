#include <vector>
#include "raylib.h"

struct Body{
  Vector2 pos;
  float vel;
  float mass;
  float tint;
};

int main (int argc, char *argv[]) {
  int width = 800;
  int height = 800;
  InitWindow(width, height, "Gravity Simulation");
  SetTargetFPS(60);

  std::vector<Body> bodies = {

  };

  while(!WindowShouldClose()){
    BeginDrawing();

    EndDrawing();
  }
  return 0;
}
