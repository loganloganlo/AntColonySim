#pragma once
#include "World.h"
#include "raylib.h"

class Game {
public:
    Game(int screenWidth, int screenHeight, const char* title, int targetFPS);
    void Run();

private:
    int screenWidth;
    int screenHeight;
    const char* title;
    int targetFPS;

    Camera2D camera;
    World world;

    void Init();
    void Shutdown();
};
