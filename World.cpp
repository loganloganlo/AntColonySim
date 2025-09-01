#include "World.h"
#include "Nest.h"
#include "Forager.h"
#include "Worker.h"
#include "Predator.h"
#include "Larva.h"
#include "Utils.h"
#include "raylib.h"
#include <algorithm>
#include <cstring> // for strcmp

World::World(int width, int height)
    : width(width), height(height),
    nest(nullptr),
    nestResources(0),
    nestLarvaCount(0),
    larvaTimer(0.0f),
    spawner(width, height) {
}

void World::Update() {
    // Update all entities
    for (auto* e : entities) {
        if (e->IsAlive()) {
            e->Update(*this);
        }
    }

    // Update resources
    for (auto& r : resources) {
        r.Update();
    }

    // Respawn resources if below min/max thresholds
    spawner.Update(resources);

    // Passive larva generation: every 10 seconds, 2 food -> 1 larva
    larvaTimer += GetFrameTime();
    if (larvaTimer >= 10.0f) {
        larvaTimer = 0.0f;
        if (nestResources >= 2) {
            nestResources -= 2;
            nestLarvaCount += 1;
        }
    }

    // Cleanup: remove dead entities
    entities.erase(std::remove_if(entities.begin(), entities.end(),
        [](Entity* e) { return !e->IsAlive(); }),
        entities.end());

    // Cleanup: remove collected resources
    resources.erase(std::remove_if(resources.begin(), resources.end(),
        [](const Resource& r) { return !r.IsAlive(); }),
        resources.end());
}

void World::Draw() {
    DrawRectangleLines(0, 0, width, height, LIGHTGRAY);

    // Draw resources
    for (auto& r : resources) {
        r.Draw();
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

bool World::TryBuyAnt(const std::string& type) {
    if (!nest) return false;

    Vector2 spawnPos = { nest->GetPos().x + GetRandomValue(-50, 50),
                         nest->GetPos().y + GetRandomValue(-50, 50) };

    if (type == "Forager" && nestLarvaCount >= 1) {
        nestLarvaCount -= 1;
        AddEntity(new Forager(spawnPos));
        return true;
    }
    else if (type == "Worker" && nestLarvaCount >= 2) {
        nestLarvaCount -= 2;
        AddEntity(new Worker(spawnPos));
        return true;
    }
    else if (type == "Soldier" && nestLarvaCount >= 5) {
        nestLarvaCount -= 5;
        // Placeholder until Soldier ant is implemented
        // AddEntity(new Soldier(spawnPos));
        return true;
    }

    return false;
}

Entity* World::FindClosestAnt(Vector2 pos) {
    Entity* closest = nullptr;
    float minDist = 1e9f;
    for (auto* e : entities) {
        if (!e->IsAlive()) continue;
        if (strcmp(e->GetType(), "Predator") == 0) continue;

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
        if (strcmp(e->GetType(), "Predator") == 0) {
            float d = DistanceSq(pos, e->GetPos());
            if (d < minDist) {
                minDist = d;
                closest = e;
            }
        }
    }
    return closest;
}

Resource* World::FindClosestResource(Vector2 pos, ResourceType type) {
    Resource* closest = nullptr;
    float minDist = 1e9f;
    for (auto& r : resources) {
        if (!r.IsAlive()) continue;
        if (r.GetType() != type) continue;

        float d = DistanceSq(pos, r.GetPos());
        if (d < minDist) {
            minDist = d;
            closest = &r;
        }
    }
    return closest;
}

void World::AddEntity(Entity* e) {
    entities.push_back(e);

    // Set nest reference if this is a nest
    if (strcmp(e->GetType(), "Nest") == 0) {
        nest = static_cast<Nest*>(e);
    }
}
