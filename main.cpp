#include <raylib.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "obstacle.hpp"
#include "player.hpp"

struct Body {
  Vector2 pos;
  Vector2 vel;
  float mass;
  Color tint;
};

int main() {
  char velocityText[64];
  char onGroundText[20];
  const int width = 900;
  const int height = 700;
  InitWindow(width, height, "Gravity Simulation");
  SetTargetFPS(60);
  Player player;
  Obstacle obstacle;

  if (true) {
    std::cout << "Wiiiw" << std::endl;
  }

  std::vector<Body> bodies = {
      {{400, 600}, {0, 0}, 5000, YELLOW},
      {{200, 300}, {0, -60}, 10, BLUE},
      {{600, 300}, {0, 60}, 10, RED},
  };

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    player.Update(dt);
    player.Move(dt);
    std::vector<Vector2> acc(bodies.size(), Vector2{0, 0});

    bool isColliding = CheckCollisionRecs(player.GetRec(), obstacle.GetRec());

    if (isColliding) {
      player.velocity *= -0.6f;
      Rectangle ground = obstacle.GetRec();
      player.setY(ground.y - player.getHeight() / 2);
      if (fabs(player.velocity) < 5.0f) {
        player.velocity = 0;
        player.onGround = true;
      } else {
        player.onGround = false;
      }
    } else {
      player.onGround = false;
    }

    for (size_t i = 0; i < bodies.size(); ++i) {
    for (size_t j = 0; j < bodies.size(); ++j) {
        if (i == j) continue; // skip self

        Vector2 r = Vector2Subtract(bodies[i].pos, bodies[j].pos);
        float d2 = Vector2LengthSqr(r) + 1e-4f;  // square distance + softening
        float invR3 = 1.0f / (sqrtf(d2) * d2);   // 1 / |r|³

        acc[i] = Vector2Add(acc[i], Vector2Scale(r, -G * bodies[j].mass * invR3));
    }
}
    BeginDrawing();
    ClearBackground(BLACK);
    snprintf(velocityText, sizeof(velocityText), "Velocity: %.2f",
             player.velocity);
    snprintf(onGroundText, sizeof(onGroundText), "On Ground: %s",
             player.onGround ? "true" : "false");
    DrawText(onGroundText, 10, 30, 20, GREEN);
    DrawText(velocityText, 10, 10, 20, GREEN);
    DrawFPS(800, 10);
    player.Draw();
    player.DrawHitbox(false);
    obstacle.Draw();

    EndDrawing();
  }

  std::cout << "Window has been Closed!" << std::endl;
  CloseWindow();
  return 0;
}
