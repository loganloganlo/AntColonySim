#pragma once
#include "Entity.h"
#include "Config.h"

class Nest : public Entity {
public:
    Nest(Vector2 pos)
        : Entity(pos,
            Config::NestRadius,
            BLACK,
            Config::NestHP,
            0,
            0.0f),
        larvaReleased(false),
        storedLarva(5) {
    }

    void Update(World& world) override;
    void Draw() const override;

    const char* GetType() const override { return "Nest"; }

    int GetStoredLarva() const { return storedLarva; }

private:
    bool larvaReleased;
    int storedLarva;
};
