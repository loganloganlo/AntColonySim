// Resource.h
#pragma once
#include "raylib.h"
#include "ResourceType.h"

class Resource {
public:
    Resource(ResourceType type, Vector2 position, float size = 8.0f)
        : type(type), pos(position), size(size), alive(true) {
    }

    void Update() {
        // Later: could add decay, respawn, regrowth logic
    }

    void Draw() const {
        if (!alive) return;
        Color c = (type == ResourceType::Food) ? GREEN : BLUE;
        DrawRectangleV(pos, { size, size }, c);
    }

    Vector2 GetPos() const { return pos; }
    bool IsAlive() const { return alive; }
    void Collect() { alive = false; }
    ResourceType GetType() const { return type; }

private:
    ResourceType type;
    Vector2 pos;
    float size;
    bool alive;
};
