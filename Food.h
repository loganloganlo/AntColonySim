#pragma once
#include "raylib.h"

class Food {
public:
    Food(Vector2 position, float size = 8.0f)
        : pos(position), size(size), alive(true) {
    }

    void Update() {
        // For later: decay, respawn, animation, etc.
    }

    void Draw() const {
        if (alive) {
            DrawRectangleV(pos, { size, size }, GREEN);
        }
    }

    Vector2 GetPos() const { return pos; }
    bool IsAlive() const { return alive; }
    void Collect() { alive = false; }

private:
    Vector2 pos;
    float size;
    bool alive;
};
