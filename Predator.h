#pragma once
#include "Entity.h"

enum class PredatorState {
    Wandering,
    Chasing
};

class Predator : public Entity {
public:
    Predator(Vector2 pos)
        : Entity(pos, 14.0f, RED, 25, 8, 0.4f), state(PredatorState::Wandering) {
    }

    void Update(World& world) override;
    const char* GetType() const override { return "Predator"; }

private:
    PredatorState state;
};
