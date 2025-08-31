#include "Predator.h"
#include "World.h"
#include "Utils.h"
#include "raylib.h"

void Predator::Update(World& world) {
    if (!IsAlive()) return;

    Entity* prey = world.FindClosestAnt(pos);
    if (prey && Distance(pos, prey->GetPos()) < 150) {
        state = PredatorState::Chasing;
    }
    else {
        state = PredatorState::Wandering;
    }

    if (state == PredatorState::Chasing && prey) {
        Vector2 dir = DirectionTo(pos, prey->GetPos());
        pos.x += dir.x * speed;
        pos.y += dir.y * speed;

        if (CheckCollisionCircles(pos, radius, prey->GetPos(), prey->GetRadius())) {
            prey->TakeDamage(attack);
            if (prey->IsAlive() && prey->GetAttack() > 0) {
                TakeDamage(prey->GetAttack()); // workers fight back
            }
        }
    }
    else if (state == PredatorState::Wandering) {
        if (GetRandomValue(0, 100) < 2) {
            Vector2 dir = RandomDirection();
            pos.x += dir.x * speed;
            pos.y += dir.y * speed;
        }
    }
}
