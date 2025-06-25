#include <iostream>
#include <raylib.h>
#include "player.hpp"
#include "obstacle.hpp"

int main(){
    char velocityText[64];
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
        }

        BeginDrawing();
        ClearBackground(BLACK);
        snprintf(velocityText, sizeof(velocityText), "Velocity: %.2f", player.velocity);
        DrawText(velocityText, 10, 10, 20, GREEN);
        player.Draw();
        player.DrawHitbox(false);
        obstacle.Draw();
        EndDrawing();
    }


    std::cout << "Window has been Closed!" << std::endl;
    CloseWindow();
    return 0;
}
