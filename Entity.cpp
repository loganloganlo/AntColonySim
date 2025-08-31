#include "Entity.h"
#include "raylib.h"

void Entity::Draw() const {
    if (!alive) return;
    DrawCircleV(pos, radius, color);
    DrawText(TextFormat("HP:%d", hp), (int)(pos.x + radius + 4), (int)(pos.y - 10), 12, RED);
    if (attack > 0) {
        DrawText(TextFormat("ATK:%d", attack), (int)(pos.x + radius + 4), (int)(pos.y + 4), 10, DARKGRAY);
    }
}
