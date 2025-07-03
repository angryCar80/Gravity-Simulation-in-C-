#include <cmath>
#include <vector>

#include "raylib.h"

struct Body {
  Vector2 pos;
  Vector2 vel;
  float mass;
  Color tint;
};

int main(int argc, char *argv[]) {
  int width = 400;
  int height = 400;
  InitWindow(width, height, "Gravity Simulation");
  SetTargetFPS(60);

  std::vector<Body> bodies = {
      {{100, 100}, {0, 0}, 10000, GREEN},
      {{300, 300}, {0, 0}, 20000, LIGHTGRAY},
      {{200, 200}, {0, 0}, 50000, YELLOW},
  };

  while (!WindowShouldClose()) {
    BeginDrawing();
    for (auto &b : bodies) {
      DrawCircleV(b.pos, 4 + logf(b.mass), b.tint);
    }

    EndDrawing();
  }
  return 0;
}
