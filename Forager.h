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

private:
    ForagerState state;
    bool carryingFood;
};
