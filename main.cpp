#include <cmath>
#include <vector>

#include "raylib.h"   // window + drawing API
#include "raymath.h"  // Vector2Subtract(), Vector2Scale(), etc.

// ---------------------------------------------------
// Tunable simulation constants
// ---------------------------------------------------
const float G = 50.0f;  // \"fake\" gravitational constant (bigger = stronger)
const float DT = 1.0f / 60.0f;  // fixed timestep (60 Hz)
const float EPSILON2 = 1e-4f;   // softening term to avoid division‑by‑zero

// ---------------------------------------------------
// Simple struct to store each celestial body
// ---------------------------------------------------
struct Body {
  Vector2 pos;  // current position (pixels)
  Vector2 vel;  // current velocity (pixels / second)
  float mass;   // arbitrary units – only ratios matter
  Color tint;   // colour when we draw the body
};

int main() {
  // 1. Raylib boilerplate --------------------------------------------------
  InitWindow(800, 600, "2‑D Gravity Simulation (Raylib)");
  SetTargetFPS(60);  // 60 stable physics steps per second

  // 2. Create bodies ONCE (outside the game loop) -------------------------
  std::vector<Body> bodies = {
      {{400, 300}, {0, 0}, 9000, YELLOW},     // big central sun
      {{300, 300}, {0, -60}, 2000, SKYBLUE},  // planet A (counter‑clockwise)
      {{600, 300}, {0, 60}, 4000.0f, RED}        // planet B (clockwise)
  };

  // Temporary array that stores acceleration for each body every frame
  std::vector<Vector2> acc(bodies.size());

  // 3. Main loop -----------------------------------------------------------
  while (!WindowShouldClose()) {
    /* ------------------------------------------------------------------
     * (a) PHYSICS STEP: compute acceleration for each body
     *     We iterate over all pairs i, j (O(N^2)).
     * ----------------------------------------------------------------*/
    for (size_t i = 0; i < bodies.size(); ++i) {
      acc[i] = Vector2Zero();  // reset previous frame's value
      for (size_t j = 0; j < bodies.size(); ++j) {
        if (i == j) continue;  // skip self‑interaction

        // r⃗  = pᵢ − pⱼ  (vector from j → i)
        Vector2 r = Vector2Subtract(bodies[i].pos, bodies[j].pos);

        // d² = |r⃗|²  (distance squared)
        float d2 = Vector2LengthSqr(r) + EPSILON2;  // add softening term

        // invR³ = 1 / |r⃗|³  (for r̂ / r²)
        float invR3 = 1.0f / (std::sqrt(d2) * d2);

        // aᵢ +=  −G · mⱼ · r⃗ / |r⃗|³
        Vector2 term = Vector2Scale(r, -G * bodies[j].mass * invR3);
        acc[i] = Vector2Add(acc[i], term);
      }
    }

    /* ------------------------------------------------------------------
     * (b) INTEGRATION STEP: semi‑implicit Euler
     *     v  ← v + a·dt
     *     p  ← p + v·dt   (using the new v)
     * ----------------------------------------------------------------*/
    for (size_t i = 0; i < bodies.size(); ++i) {
      bodies[i].vel = Vector2Add(bodies[i].vel, Vector2Scale(acc[i], DT));
      bodies[i].pos =
          Vector2Add(bodies[i].pos, Vector2Scale(bodies[i].vel, DT));
    }

    /* ------------------------------------------------------------------
     * (c) DRAW STEP
     * ----------------------------------------------------------------*/
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw each body – radius grows with log(mass) so the sun looks bigger
    for (const Body &b : bodies) {
      float radius = 4.0f + std::logf(b.mass);
      DrawCircleV(b.pos, radius, b.tint);
    }

    DrawFPS(10, 10);
    DrawText("Press ESC to quit", 580, 570, 10, GRAY);
    EndDrawing();
  }

  // 4. Clean up ------------------------------------------------------------
  CloseWindow();
  return 0;
}
