#pragma once
#include "Entity.h"

enum class ForagerState {
    Searching,
    Returning
};

class Forager : public Entity {
public:
    Forager(Vector2 pos)
        : Entity(pos, 7.5f, BROWN, 12, 3, 1.0f),
        state(ForagerState::Searching), carryingFood(false) {
    }

    void Update(World& world) override;
    const char* GetType() const override { return "Forager"; }

private:
    ForagerState state;
    bool carryingFood;
};
