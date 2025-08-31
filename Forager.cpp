#include "Forager.h"
#include "World.h"
#include "Nest.h"
#include "Utils.h"
#include "raylib.h"

void Forager::Update(World& world) {
    if (!IsAlive()) return;

    if (state == ForagerState::Searching) {
        Food* food = world.FindClosestFood(pos);
        if (food && Distance(pos, food->GetPos()) < radius + 4) {
            food->Collect();
            carryingFood = true;
            state = ForagerState::Returning;
        }
        else if (food) {
            Vector2 dir = DirectionTo(pos, food->GetPos());
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
            world.AddFoodToNest(1);
            carryingFood = false;
            state = ForagerState::Searching;
        }
    }
}
