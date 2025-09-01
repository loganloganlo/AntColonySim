#pragma once
#include <vector>
#include <string>
#include "Entity.h"
#include "Resource.h"
#include "ResourceSpawner.h"

class Nest;

class World {
public:
    World(int width, int height);

    void Update();
    void Draw();

    // Nest management
    Nest* GetNest();
    void AddFoodToNest(int amount);

    // Expose stats for HUD
    int GetNestFood() const { return nestResources; }
    int GetNestLarva() const { return nestLarvaCount; }

    // Expose world size for clamping
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    // Buy ants with larva
    bool TryBuyAnt(const std::string& type);

    // Find helpers
    Entity* FindClosestAnt(Vector2 pos);
    Entity* FindClosestPredator(Vector2 pos);
    Resource* FindClosestResource(Vector2 pos, ResourceType type);

    // Spawning
    void AddEntity(Entity* e);

private:
    int width;
    int height;

    std::vector<Entity*> entities;
    std::vector<Resource> resources;
    ResourceSpawner spawner;

    Nest* nest;
    int nestResources;   // Food storage
    int nestLarvaCount;  // Spendable larva

    float larvaTimer;    // Timer for passive larva generation
};
