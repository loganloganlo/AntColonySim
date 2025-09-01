#include "Worker.h"
#include "World.h"
#include "Utils.h"
#include "Nest.h"
#include "raylib.h"

void Worker::Update(World& world) {
    if (!IsAlive()) return;

    Nest* nest = world.GetNest();
    Entity* predator = world.FindClosestPredator(pos);

    // --- Chase predator if nearby ---
    if (predator && Distance(pos, predator->GetPos()) < 250) {
        Vector2 dir = DirectionTo(pos, predator->GetPos());
        pos.x += dir.x * speed;
        pos.y += dir.y * speed;

        if (CheckCollisionCircles(pos, radius, predator->GetPos(), predator->GetRadius())) {
            predator->TakeDamage(attack);
            if (predator->IsAlive()) {
                TakeDamage(predator->GetAttack());
            }
        }
        return;
    }

    // --- Patrol system ---
    if (nest) {
        if (!hasPatrolTarget || Distance(pos, patrolTarget) < 10) {
            // Pick new patrol target within 600 radius of nest
            float angle = GetRandomValue(0, 360) * DEG2RAD;
            float dist = (float)GetRandomValue(200, 600); // stay at least 200 away
            patrolTarget = {
                nest->GetPos().x + cosf(angle) * dist,
                nest->GetPos().y + sinf(angle) * dist
            };

            // Clamp to world bounds so they don’t leave the map
            if (patrolTarget.x < 0) patrolTarget.x = 0;
            if (patrolTarget.y < 0) patrolTarget.y = 0;
            if (patrolTarget.x > world.GetWidth()) patrolTarget.x = (float)world.GetWidth();
            if (patrolTarget.y > world.GetHeight()) patrolTarget.y = (float)world.GetHeight();

            hasPatrolTarget = true;
        }

        // Move toward patrol target
        Vector2 dir = DirectionTo(pos, patrolTarget);
        pos.x += dir.x * speed;
        pos.y += dir.y * speed;
    }
}
