#pragma once
#include <vector>
#include "Entity.h"
#include "Food.h"

class Nest;

class World {
public:
    World(int width, int height);

    void Update();
    void Draw();

    // Nest management
    Nest* GetNest();
    void AddFoodToNest(int amount);

    // Find helpers
    Entity* FindClosestAnt(Vector2 pos);
    Entity* FindClosestPredator(Vector2 pos);
    Food* FindClosestFood(Vector2 pos);

    // Spawning
    void SpawnFood(int count);
    void AddEntity(Entity* e);

private:
    int width;
    int height;

    std::vector<Entity*> entities;
    std::vector<Food> foodNodes;

    Nest* nest;
    int nestResources;
    int nestLarvaCount;
};
