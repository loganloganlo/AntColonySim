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

    bool gameOver = false;

    while (!WindowShouldClose()) {
        if (!gameOver) {
            // Input: buy ants with number keys
            if (IsKeyPressed(KEY_ONE)) world.TryBuyAnt("Forager");
            if (IsKeyPressed(KEY_TWO)) world.TryBuyAnt("Worker");
            if (IsKeyPressed(KEY_THREE)) world.TryBuyAnt("Soldier");

            camera.Update();
            world.Update();

            // Check if nest is dead
            if (world.GetNest() && !world.GetNest()->IsAlive()) {
                gameOver = true;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        camera.Begin();
        world.Draw();
        camera.End();

        if (!gameOver) {
            std::string buyType = camera.DrawHUD(world.GetNestFood(), world.GetNestLarva());
            if (!buyType.empty()) world.TryBuyAnt(buyType);
        }
        else {
            // --- Game Over overlay ---
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));
            DrawText("GAME OVER - The Nest has been destroyed!",
                screenWidth / 2 - 250, screenHeight / 2, 30, RED);
        }

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

    // Spawn an initial predator (off-screen)
    world.SpawnPredatorOffScreen();
}

void Game::Shutdown() {
    CloseWindow();
}
