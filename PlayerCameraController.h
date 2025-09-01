#pragma once
#include "raylib.h"
#include <string>

class PlayerCameraController {
public:
    PlayerCameraController(int screenWidth, int screenHeight);

    void Update();
    void Begin() const;
    void End() const;

    // Returns which button was clicked: "Forager", "Worker", "Soldier", or ""
    std::string DrawHUD(int foodStored, int larvaCount) const;

private:
    Camera2D camera;
    float moveSpeed;   // units per second
    float zoomSpeed;
};
