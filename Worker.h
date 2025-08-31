#pragma once
#include "Entity.h"

class Worker : public Entity {
public:
    Worker(Vector2 pos) : Entity(pos, 10.0f, DARKGREEN, 18, 10, 1.2f) {}

    void Update(World& world) override;
};
