#include "player.hpp"

Player::Player()
{
  position.x = 100;
  position.y = 100;
  velocity = 0;
  circleRad = 40;
  gravity = 980;
  vx = 0;
  acceleration = 800;
  fraction = 750;
  maxspeed = 300;
  thrust = 200;
  // Hitbox values
  width = 90;
  height = 80;
}

void Player::Draw(){
  DrawCircle(position.x, position.y, circleRad, WHITE);
}

void Player::Update(float dt){
  velocity += gravity * dt;
  position.y += velocity * dt;

}
void Player::Move(float dt){
  if (IsKeyDown(KEY_UP)){
    velocity -= thrust;
  }

  if (IsKeyDown(KEY_RIGHT)){
    vx += acceleration * dt;
  }
  else if (IsKeyDown(KEY_LEFT)){
    vx -= acceleration * dt;
  }
  else{
    if( vx > 0 ){
      vx -= fraction * dt;
      if (vx < 0) vx = 0;
    }
    else if (vx < 0){
      vx += fraction * dt;
      if (vx > 0) vx = 0;
    }
  }
  if (vx >= maxspeed) vx = maxspeed;
  if (vx <= -maxspeed) vx = -maxspeed;
  position.x += vx * dt;
}

void Player::DrawHitbox(bool isColliding)
{
  Color outlineColor = isColliding ? RED : GREEN;
  DrawRectangleLines(
    static_cast<int>(position.x - width / 2),
    static_cast<int>(position.y - height / 2),
    width,
    height,
    outlineColor
  );
}

Rectangle Player::GetRec(){
  return Rectangle {(position.x - width / 2), (position.y - height / 2), width, height};
}