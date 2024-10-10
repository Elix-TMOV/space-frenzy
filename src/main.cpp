
#include <iostream>
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <vector>
#include <cmath>
#include "game.hpp"

#include <list>

using namespace std;
// settings
const int SCR_WIDTH = GetScreenWidth();
const int SCR_HEIGHT = 800;
const short frameCount = 6;
const float frameTime = 0.1f;

float begreeToRabian(float begrees){
    return begrees * (PI/180);
}

int main() {
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib Example");
    // SetWindowState(FLAG_FULLSCREEN_MODE);
    Game& game = Game::getInstance();
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground({220, 121, 241, 255});
        game.draw();
        game.update();
        // DrawTexture(sentinalBullet, 500, 500, WHITE);
        EndDrawing();
    }
 
    CloseWindow();
    return 0;
}
