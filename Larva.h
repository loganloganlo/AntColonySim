#pragma once
#include "Entity.h"

class Larva : public Entity {
public:
    Larva(Vector2 pos) : Entity(pos, 4.0f, WHITE, 1, 0, 0.0f) {}

    void Update(World& world) override {
        // Larva do not move or act
    }
};
