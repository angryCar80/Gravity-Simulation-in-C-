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
}

void Player::Draw(){
  DrawCircle(position.x, position.y, circleRad, WHITE);
}

void Player::Update(float dt){
  velocity += gravity * dt;
  position.y += velocity * dt;

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
}