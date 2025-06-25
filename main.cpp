#include <iostream>
#include <raylib.h>
#include "player.hpp"

int main(){
    char velocityText[64];
    const int width = 900;
    const int height = 700;
    InitWindow(width, height, "Gravity Simulation");
    SetTargetFPS(60);

    Player player;
    while(!WindowShouldClose()){
        float dt = GetFrameTime();

        player.Update(dt);

        BeginDrawing();
        ClearBackground(BLACK);
        snprintf(velocityText, sizeof(velocityText), "Velocity: %.2f", player.velocity);
        DrawText(velocityText, 10, 10, 20, GREEN);
        player.Draw();
        EndDrawing();
    }


    std::cout << "Window has been Closed!" << std::endl;
    CloseWindow();
    return 0;
}
