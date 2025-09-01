#pragma once
#include "Entity.h"

enum class PredatorState {
    Entering,
    Wandering,
    Chasing
};

class Predator : public Entity {
public:
    Predator(Vector2 pos, int worldW, int worldH);

    void Update(World& world) override;
    const char* GetType() const override { return "Predator"; }

private:
    PredatorState state;
    Vector2 targetPoint;
    bool hasTarget;
    int worldWidth, worldHeight;

    void PickNewPatrolPoint();
    void PickBorderEntry();
};
