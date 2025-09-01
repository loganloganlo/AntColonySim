#include "Nest.h"
#include "World.h"
#include "Config.h"
#include "raylib.h"

void Nest::Update(World& world) {
    // Nest has no special logic yet (handled in Game/World)
}

void Nest::Draw() const {
    // Nest circle
    DrawCircleV(pos, radius, Fade(color, 0.3f));
    DrawCircleLines((int)pos.x, (int)pos.y, radius, DARKGRAY);

    // HP bar
    float hpPercent = (float)hp / (float)Config::NestHP;
    DrawRectangle(pos.x - 30, pos.y - radius - 20, 60, 8, DARKGRAY);
    DrawRectangle(pos.x - 30, pos.y - radius - 20, (int)(60 * hpPercent), 8, RED);
}
