#include "PlayerCameraController.h"
#include "raylib.h"

PlayerCameraController::PlayerCameraController(int screenWidth, int screenHeight) {
    camera.target = { (float)screenWidth / 2, (float)screenHeight / 2 };
    camera.offset = { (float)screenWidth / 2, (float)screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    moveSpeed = 5.0f;
    zoomSpeed = 0.1f;
}

void PlayerCameraController::Update() {
    // Camera movement with WASD
    if (IsKeyDown(KEY_A)) camera.target.x -= moveSpeed / camera.zoom;
    if (IsKeyDown(KEY_D)) camera.target.x += moveSpeed / camera.zoom;
    if (IsKeyDown(KEY_W)) camera.target.y -= moveSpeed / camera.zoom;
    if (IsKeyDown(KEY_S)) camera.target.y += moveSpeed / camera.zoom;

    // Zoom with mouse wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f) {
        float prevZoom = camera.zoom;
        camera.zoom += wheel * zoomSpeed;

        if (camera.zoom < 0.25f) camera.zoom = 0.25f;
        if (camera.zoom > 4.0f) camera.zoom = 4.0f;

        // Keep zoom centered on mouse cursor
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        Vector2 diff = { mouseWorldPos.x - camera.target.x, mouseWorldPos.y - camera.target.y };
        camera.target.x += diff.x * (1.0f - prevZoom / camera.zoom);
        camera.target.y += diff.y * (1.0f - prevZoom / camera.zoom);
    }
}

void PlayerCameraController::Begin() const {
    BeginMode2D(camera);
}

void PlayerCameraController::End() const {
    EndMode2D();
}

std::string PlayerCameraController::DrawHUD(int foodStored, int larvaCount) const {
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();

    int buttonWidth = 200;
    int buttonHeight = 40;
    int margin = 10;

    // Top panel: resources
    DrawRectangle(0, 0, 250, 60, Fade(LIGHTGRAY, 0.8f));
    DrawRectangleLines(0, 0, 250, 60, DARKGRAY);
    DrawText(TextFormat("Food stored: %d", foodStored), 10, 10, 20, DARKGREEN);
    DrawText(TextFormat("Larva available: %d", larvaCount), 10, 35, 20, DARKGRAY);

    // Buttons anchored bottom-left
    Rectangle foragerBtn = { 10, (float)screenHeight - (buttonHeight * 3 + margin * 3), (float)buttonWidth, (float)buttonHeight };
    Rectangle workerBtn = { 10, (float)screenHeight - (buttonHeight * 2 + margin * 2), (float)buttonWidth, (float)buttonHeight };
    Rectangle soldierBtn = { 10, (float)screenHeight - (buttonHeight * 1 + margin * 1), (float)buttonWidth, (float)buttonHeight };

    // Forager button
    Color foragerColor = (larvaCount >= 1) ? BROWN : GRAY;
    DrawRectangleRec(foragerBtn, foragerColor);
    DrawRectangleLinesEx(foragerBtn, 2, BLACK);
    DrawText("Buy Forager (1 larva)", foragerBtn.x + 10, foragerBtn.y + 10, 18, WHITE);

    // Worker button
    Color workerColor = (larvaCount >= 2) ? DARKGREEN : GRAY;
    DrawRectangleRec(workerBtn, workerColor);
    DrawRectangleLinesEx(workerBtn, 2, BLACK);
    DrawText("Buy Worker (2 larva)", workerBtn.x + 10, workerBtn.y + 10, 18, WHITE);

    // Soldier button
    Color soldierColor = (larvaCount >= 5) ? RED : GRAY;
    DrawRectangleRec(soldierBtn, soldierColor);
    DrawRectangleLinesEx(soldierBtn, 2, BLACK);
    DrawText("Buy Soldier (5 larva)", soldierBtn.x + 10, soldierBtn.y + 10, 18, WHITE);

    // --- Handle button clicks ---
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, foragerBtn) && larvaCount >= 1) return "Forager";
        if (CheckCollisionPointRec(mouse, workerBtn) && larvaCount >= 2) return "Worker";
        if (CheckCollisionPointRec(mouse, soldierBtn) && larvaCount >= 5) return "Soldier";
    }

    // --- Debug: FPS counter (top-right) ---
    DrawFPS(screenWidth - 90, 10);

    return "";
}
