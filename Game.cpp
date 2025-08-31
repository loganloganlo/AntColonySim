#include "Game.h"
#include "Nest.h"
#include "Forager.h"
#include "Worker.h"
#include "Predator.h"

Game::Game(int screenWidth, int screenHeight, const char* title, int targetFPS)
    : screenWidth(screenWidth), screenHeight(screenHeight), title(title), targetFPS(targetFPS),
    world(2000, 2000) {
}

void Game::Run() {
    Init();
    while (!WindowShouldClose()) {
        world.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        world.Draw();
        EndMode2D();

        EndDrawing();
    }
    Shutdown();
}

void Game::Init() {
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(targetFPS);

    camera.target = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Spawn world entities
    world.AddEntity(new Nest({ 200, 200 }));
    world.AddEntity(new Forager({ 400, 300 }));
    world.AddEntity(new Worker({ 450, 350 }));
    world.AddEntity(new Predator({ 1000, 800 }));

    world.SpawnFood(30);
}

void Game::Shutdown() {
    CloseWindow();
}
