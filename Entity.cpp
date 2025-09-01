#include "Entity.h"
#include "raylib.h"

void Entity::Draw() const {
    // Default: generic circle
    DrawCircleV(pos, radius, color);

    // Default: HP/ATK text (good for ants/predators)
    DrawText(TextFormat("HP:%d", hp), pos.x - 20, pos.y - (radius + 20), 10, RED);
    DrawText(TextFormat("ATK:%d", attack), pos.x - 20, pos.y - (radius + 10), 10, DARKGRAY);
}
