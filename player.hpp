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
    Vector2 position;
    bool onGround;
  private:
    float circleRad;
    float gravity;
    float vx;
    float acceleration;
    float fraction;
    float maxspeed;
    float thrust;
    

    //The Values for the hitbox
    float width;
    float height;
    
};
