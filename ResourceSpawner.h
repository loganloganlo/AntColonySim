#pragma once
#include <vector>
#include "Resource.h"

class ResourceSpawner {
public:
    ResourceSpawner(int worldWidth, int worldHeight)
        : worldWidth(worldWidth), worldHeight(worldHeight),
        minFood(10), maxFood(30),
        minWater(5), maxWater(15) {
    }

    void Update(std::vector<Resource>& resources) {
        int foodCount = CountType(resources, ResourceType::Food);
        int waterCount = CountType(resources, ResourceType::Water);

        // Respawn food
        while (foodCount < minFood) {
            resources.emplace_back(ResourceType::Food, RandomPos());
            foodCount++;
        }

        // Respawn water
        while (waterCount < minWater) {
            resources.emplace_back(ResourceType::Water, RandomPos());
            waterCount++;
        }

        // (Optional) Clamp to max
        if (foodCount > maxFood) TrimType(resources, ResourceType::Food, maxFood);
        if (waterCount > maxWater) TrimType(resources, ResourceType::Water, maxWater);
    }

    void SetFoodLimits(int minVal, int maxVal) { minFood = minVal; maxFood = maxVal; }
    void SetWaterLimits(int minVal, int maxVal) { minWater = minVal; maxWater = maxVal; }

private:
    int worldWidth, worldHeight;
    int minFood, maxFood;
    int minWater, maxWater;

    Vector2 RandomPos() {
        return { (float)GetRandomValue(0, worldWidth - 10),
                 (float)GetRandomValue(0, worldHeight - 10) };
    }

    int CountType(const std::vector<Resource>& resources, ResourceType type) {
        int count = 0;
        for (auto& r : resources) {
            if (r.IsAlive() && r.GetType() == type) count++;
        }
        return count;
    }

    void TrimType(std::vector<Resource>& resources, ResourceType type, int maxAllowed) {
        int count = 0;
        for (auto& r : resources) {
            if (r.IsAlive() && r.GetType() == type) {
                count++;
                if (count > maxAllowed) r.Collect();
            }
        }
    }
};
