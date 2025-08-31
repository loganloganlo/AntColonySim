#pragma once
#include "Entity.h"

class Nest : public Entity {
public:
    Nest(Vector2 pos) : Entity(pos, 60.0f, BLACK, 100, 0, 0.0f), larvaReleased(false), storedLarva(5) {}

    void Update(World& world) override;
    const char* GetType() const override { return "Nest"; }

    int GetStoredLarva() const { return storedLarva; }

private:
    bool larvaReleased;
    int storedLarva;
};
