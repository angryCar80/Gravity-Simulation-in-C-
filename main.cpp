#include <iostream>
#include <raylib.h>
#include <cmath>
#include "player.hpp"
#include "obstacle.hpp"

int main(){
    char velocityText[64];
    char onGroundText[20];
    const int width = 900;
    const int height = 700;
    InitWindow(width, height, "Gravity Simulation");
    SetTargetFPS(60);

    Player player;
    Obstacle obstacle;
    while(!WindowShouldClose()){
        float dt = GetFrameTime();

        player.Update(dt);
        player.Move(dt);

        bool isColliding = CheckCollisionRecs(player.GetRec() , obstacle.GetRec());
        
        if (isColliding){
            player.velocity *= -0.6f;
            Rectangle ground = obstacle.GetRec();
            player.setY(ground.y - player.getHeight()/2);
            if (fabs(player.velocity) < 5.0f){
                player.velocity = 0;
                player.onGround = true;
            }
            else{
                player.onGround = false;
            }
        }
        else{
            player.onGround = false;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        snprintf(velocityText, sizeof(velocityText), "Velocity: %.2f", player.velocity);
        snprintf(onGroundText, sizeof(onGroundText), "On Ground: %s", player.onGround ? "true" : "false");
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
