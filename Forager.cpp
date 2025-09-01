#include "Forager.h"
#include "World.h"
#include "Nest.h"
#include "Utils.h"
#include "Config.h"
#include "raylib.h"

Forager::Forager(Vector2 pos)
    : Entity(pos,
        Config::ForagerRadius,
        BROWN,
        Config::ForagerHP,
        Config::ForagerAttack,
        Config::ForagerSpeed),
    state(ForagerState::Searching),
    carryingFood(false) {
}

void Forager::Update(World& world) {
    if (!IsAlive()) return;

    float dt = GetFrameTime();

    if (state == ForagerState::Searching) {
        Resource* food = world.FindClosestResource(pos, ResourceType::Food);
        Resource* water = world.FindClosestResource(pos, ResourceType::Water);

        Resource* target = nullptr;
        float distFood = (food) ? DistanceSq(pos, food->GetPos()) : 1e9f;
        float distWater = (water) ? DistanceSq(pos, water->GetPos()) : 1e9f;

        if (distFood < distWater) target = food;
        else target = water;

        if (target && Distance(pos, target->GetPos()) < radius + 4) {
            target->Collect();
            carryingFood = true;
            state = ForagerState::Returning;
        }
        else if (target) {
            Vector2 dir = DirectionTo(pos, target->GetPos());
            pos.x += dir.x * speed * dt;
            pos.y += dir.y * speed * dt;
        }
    }
    else if (state == ForagerState::Returning) {
        Nest* nest = world.GetNest();
        if (!nest) return;

        Vector2 dir = DirectionTo(pos, nest->GetPos());
        pos.x += dir.x * speed * dt;
        pos.y += dir.y * speed * dt;

        if (CheckCollisionCircles(pos, radius, nest->GetPos(), nest->GetRadius())) {
            world.AddFoodToNest(1);
            carryingFood = false;
            state = ForagerState::Searching;
        }
    }
}
