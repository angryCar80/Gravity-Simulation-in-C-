#include "obstacle.hpp"

Obstacle::Obstacle(){
  width = 1000;
  height = 200;
  position.x = 0;
  position.y = 600;
}

void Obstacle::Draw(){
  DrawRectangle(position.x, position.y, width, height, LIGHTGRAY);
  DrawRectangleLines(position.x, position.y, width, height, GREEN);
}

Rectangle Obstacle::GetRec(){
  return Rectangle {position.x, position.y, width, height};
}