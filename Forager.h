#pragma once
#include "Entity.h"

enum class ForagerState {
    Searching,
    Returning
};

class Forager : public Entity {
public:
    Forager(Vector2 pos);

    void Update(World& world) override;
    const char* GetType() const override { return "Forager"; }

private:
    ForagerState state;
    bool carryingFood;
};
