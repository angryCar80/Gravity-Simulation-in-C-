#pragma once
#include<raylib.h>

class Player{
  public:
    Player();
    // ~Player();
    void Draw();
    void Update(float dt);
    void Move(float dt);
    void setY(float y) { position.y = y; };
    float getHeight() const  {return height;}
  // Must have for checking the collision
    void DrawHitbox(bool isColliding);
    Rectangle GetRec();
  // setting values
    float velocity;
    bool onGround;
  private:
    float circleRad;
    float gravity;
    float vx;
    float acceleration;
    float fraction;
    float maxspeed;
    float thrust;
    Vector2 position;

    //The Values for the hitbox
    float width;
    float height;
    
};
