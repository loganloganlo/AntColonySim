#include "Nest.h"
#include "World.h"
#include "Larva.h"
#include "raylib.h"

void Nest::Update(World& world) {
    if (!IsAlive() && !larvaReleased) {
        // When the nest dies, release stored larva into the world
        for (int i = 0; i < storedLarva; i++) {
            Vector2 offset = { (float)GetRandomValue(-40, 40), (float)GetRandomValue(-40, 40) };
            world.AddEntity(new Larva({ pos.x + offset.x, pos.y + offset.y }));
        }
        larvaReleased = true;
    }
}
