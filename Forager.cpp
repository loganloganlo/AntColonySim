#include "Forager.h"
#include "World.h"
#include "Nest.h"
#include "Utils.h"
#include "raylib.h"

void Forager::Update(World& world) {
    if (!IsAlive()) return;

    if (state == ForagerState::Searching) {
        // Look for nearest food and water
        Resource* food = world.FindClosestResource(pos, ResourceType::Food);
        Resource* water = world.FindClosestResource(pos, ResourceType::Water);

        // Pick whichever is closer
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
            pos.x += dir.x * speed;
            pos.y += dir.y * speed;
        }
    }
    else if (state == ForagerState::Returning) {
        Nest* nest = world.GetNest();
        if (!nest) return;

        Vector2 dir = DirectionTo(pos, nest->GetPos());
        pos.x += dir.x * speed;
        pos.y += dir.y * speed;

        if (CheckCollisionCircles(pos, radius, nest->GetPos(), nest->GetRadius())) {
            world.AddFoodToNest(1); // Treat both food & water as resource points for now
            carryingFood = false;
            state = ForagerState::Searching;
        }
    }
}
