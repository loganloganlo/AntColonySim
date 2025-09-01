#pragma once
#include "Entity.h"

class Worker : public Entity {
public:
    Worker(Vector2 pos);

    void Update(World& world) override;
    const char* GetType() const override { return "Worker"; }

private:
    Vector2 patrolTarget;
    bool hasPatrolTarget;
};
