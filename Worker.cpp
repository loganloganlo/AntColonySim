#include "World.h"
#include "Nest.h"
#include "Forager.h"
#include "Worker.h"
#include "Predator.h"
#include "Larva.h"
#include "Utils.h"
#include "raylib.h"
#include <algorithm>

World::World(int width, int height)
    : width(width), height(height), nest(nullptr),
    nestResources(0), nestLarvaCount(5) {
}

void World::Update() {
    // Update entities
    for (auto* e : entities) {
        if (e->IsAlive()) {
            e->Update(*this);
        }
    }

    // Update food
    for (auto& f : foodNodes) {
        f.Update();
    }

    // Cleanup dead entities
    entities.erase(std::remove_if(entities.begin(), entities.end(),
        [](Entity* e) { return !e->IsAlive(); }),
        entities.end());

    // Cleanup collected food
    foodNodes.erase(std::remove_if(foodNodes.begin(), foodNodes.end(),
        [](const Food& f) { return !f.IsAlive(); }),
        foodNodes.end());
}

void World::Draw() {
    DrawRectangleLines(0, 0, width, height, LIGHTGRAY);

    // Draw food
    for (auto& f : foodNodes) {
        f.Draw();
    }

    // Draw entities
    for (auto* e : entities) {
        e->Draw();
    }
}

Nest* World::GetNest() {
    return nest;
}

void World::AddFoodToNest(int amount) {
    nestResources += amount;
}

Entity* World::FindClosestAnt(Vector2 pos) {
    Entity* closest = nullptr;
    float minDist = 1e9f;
    for (auto* e : entities) {
        if (!e->IsAlive()) continue;
        // Ants are anything that is NOT a Predator
        if (dynamic_cast<Predator*>(e)) continue;

        float d = DistanceSq(pos, e->GetPos());
        if (d < minDist) {
            minDist = d;
            closest = e;
        }
    }
    return closest;
}

Entity* World::FindClosestPredator(Vector2 pos) {
    Entity* closest = nullptr;
    float minDist = 1e9f;
    for (auto* e : entities) {
        if (!e->IsAlive()) continue;
        if (dynamic_cast<Predator*>(e)) {
            float d = DistanceSq(pos, e->GetPos());
            if (d < minDist) {
                minDist = d;
                closest = e;
            }
        }
    }
    return closest;
}

Food* World::FindClosestFood(Vector2 pos) {
    Food* closest = nullptr;
    float minDist = 1e9f;
    for (auto& f : foodNodes) {
        if (!f.IsAlive()) continue;
        float d = DistanceSq(pos, f.GetPos());
        if (d < minDist) {
            minDist = d;
            closest = &f;
        }
    }
    return closest;
}

void World::SpawnFood(int count) {
    for (int i = 0; i < count; i++) {
        Vector2 pos = { (float)GetRandomValue(0, width - 10),
                        (float)GetRandomValue(0, height - 10) };
        foodNodes.emplace_back(pos, 8.0f);
    }
}

void World::AddEntity(Entity* e) {
    entities.push_back(e);
    if (Nest* n = dynamic_cast<Nest*>(e)) {
        nest = n;
    }
}
