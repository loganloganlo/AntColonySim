#include "Predator.h"
#include "World.h"
#include "Nest.h"
#include "Utils.h"
#include "Config.h"
#include "raylib.h"

Predator::Predator(Vector2 pos, int worldW, int worldH)
    : Entity(pos,
        Config::PredatorRadius,
        RED,
        Config::PredatorHP,
        Config::PredatorAttack,
        Config::PredatorSpeed),
    state(PredatorState::Entering),
    hasTarget(false),
    worldWidth(worldW),
    worldHeight(worldH) {
    PickBorderEntry();
}

void Predator::PickBorderEntry() {
    int side = GetRandomValue(0, 3);
    if (side == 0) targetPoint = { 0, (float)GetRandomValue(0, worldHeight) };
    else if (side == 1) targetPoint = { (float)worldWidth, (float)GetRandomValue(0, worldHeight) };
    else if (side == 2) targetPoint = { (float)GetRandomValue(0, worldWidth), 0 };
    else targetPoint = { (float)GetRandomValue(0, worldWidth), (float)worldHeight };
    hasTarget = true;
}

void Predator::PickNewPatrolPoint() {
    targetPoint = {
        (float)GetRandomValue(50, worldWidth - 50),
        (float)GetRandomValue(50, worldHeight - 50)
    };
    hasTarget = true;
}

void Predator::Update(World& world) {
    if (!IsAlive()) return;

    float dt = GetFrameTime();

    // Get nest
    Nest* nest = world.GetNest();
    Entity* prey = world.FindClosestAnt(pos);

    // --- Target nest first ---
    if (nest && nest->IsAlive()) {
        // If near nest, attack it
        if (Distance(pos, nest->GetPos()) < 200) {
            state = PredatorState::Chasing;

            Vector2 dir = DirectionTo(pos, nest->GetPos());
            pos.x += dir.x * speed * dt;
            pos.y += dir.y * speed * dt;

            if (CheckCollisionCircles(pos, radius, nest->GetPos(), nest->GetRadius())) {
                nest->TakeDamage(attack);
            }
            return;
        }
    }

    // --- Otherwise, chase ants if close ---
    if (prey && Distance(pos, prey->GetPos()) < 150) {
        state = PredatorState::Chasing;

        Vector2 dir = DirectionTo(pos, prey->GetPos());
        pos.x += dir.x * speed * dt;
        pos.y += dir.y * speed * dt;

        if (CheckCollisionCircles(pos, radius, prey->GetPos(), prey->GetRadius())) {
            prey->TakeDamage(attack);
            if (prey->IsAlive() && prey->GetAttack() > 0) {
                TakeDamage(prey->GetAttack()); // workers fight back
            }
        }
        return;
    }

    // --- Wander if no nest in range and no prey ---
    state = PredatorState::Wandering;
    if (!hasTarget || Distance(pos, targetPoint) < 8) {
        PickNewPatrolPoint();
    }
    Vector2 dir = DirectionTo(pos, targetPoint);
    pos.x += dir.x * speed * dt;
    pos.y += dir.y * speed * dt;
}
