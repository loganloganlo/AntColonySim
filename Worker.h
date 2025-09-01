#pragma once
#include "Entity.h"

class Worker : public Entity {
public:
    Worker(Vector2 pos) : Entity(pos, 10.0f, DARKGREEN, 18, 10, 1.2f),
        hasPatrolTarget(false) {
    }

    void Update(World& world) override;
    const char* GetType() const override { return "Worker"; }

private:
    Vector2 patrolTarget;
    bool hasPatrolTarget;
};
