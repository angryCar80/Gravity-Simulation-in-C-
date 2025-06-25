#pragma once
#include <raylib.h>

class Obstacle{
  public:
  Obstacle();
  void Draw();
  void Update();
  Rectangle GetRec();
  private:
  float width;
  float height;
  Vector2 position;
};