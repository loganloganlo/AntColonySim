#include "Game.h"
#include "Nest.h"
#include "Forager.h"
#include "Worker.h"
#include "Predator.h"
#include "PlayerCameraController.h"

Game::Game(int screenWidth, int screenHeight, const char* title, int targetFPS)
    : screenWidth(screenWidth), screenHeight(screenHeight), title(title), targetFPS(targetFPS),
    world(2000, 2000) {
}

void Game::Run() {
    Init();

    PlayerCameraController camera(screenWidth, screenHeight);

    while (!WindowShouldClose()) {
        // Input: buy ants with number keys
        if (IsKeyPressed(KEY_ONE)) {
            world.TryBuyAnt("Forager");
        }
        if (IsKeyPressed(KEY_TWO)) {
            world.TryBuyAnt("Worker");
        }
        if (IsKeyPressed(KEY_THREE)) {
            world.TryBuyAnt("Soldier");
        }

        camera.Update();
        world.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        camera.Begin();
        world.Draw();
        camera.End();

        camera.DrawHUD(world.GetNestFood(), world.GetNestLarva());
        EndDrawing();
    }

    Shutdown();
}

void Game::Init() {
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(targetFPS);

    // Spawn initial entities
    world.AddEntity(new Nest({ 200, 200 }));
    world.AddEntity(new Forager({ 250, 200 }));
    world.AddEntity(new Forager({ 220, 230 }));
    world.AddEntity(new Worker({ 200, 210 }));

    // Predators will be spawned later by progression logic
}

void Game::Shutdown() {
    CloseWindow();
}
