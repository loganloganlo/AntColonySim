#include "Worker.h"
#include "World.h"
#include "Nest.h"
#include "Utils.h"
#include "Config.h"
#include "raylib.h"

Worker::Worker(Vector2 pos)
    : Entity(pos,
        Config::WorkerRadius,
        DARKGREEN,
        Config::WorkerHP,
        Config::WorkerAttack,
        Config::WorkerSpeed),
    hasPatrolTarget(false) {
}

void Worker::Update(World& world) {
    if (!IsAlive()) return;

    float dt = GetFrameTime();

    Nest* nest = world.GetNest();
    Entity* predator = world.FindClosestPredator(pos);

    if (predator && Distance(pos, predator->GetPos()) < 250) {
        Vector2 dir = DirectionTo(pos, predator->GetPos());
        pos.x += dir.x * speed * dt;
        pos.y += dir.y * speed * dt;

        if (CheckCollisionCircles(pos, radius, predator->GetPos(), predator->GetRadius())) {
            predator->TakeDamage(attack);
            if (predator->IsAlive()) {
                TakeDamage(predator->GetAttack());
            }
        }
        return;
    }

    if (nest) {
        if (!hasPatrolTarget || Distance(pos, patrolTarget) < 10) {
            float angle = GetRandomValue(0, 360) * DEG2RAD;
            float dist = (float)GetRandomValue(200, 600);
            patrolTarget = {
                nest->GetPos().x + cosf(angle) * dist,
                nest->GetPos().y + sinf(angle) * dist
            };

            if (patrolTarget.x < 0) patrolTarget.x = 0;
            if (patrolTarget.y < 0) patrolTarget.y = 0;
            if (patrolTarget.x > world.GetWidth()) patrolTarget.x = (float)world.GetWidth();
            if (patrolTarget.y > world.GetHeight()) patrolTarget.y = (float)world.GetHeight();

            hasPatrolTarget = true;
        }

        Vector2 dir = DirectionTo(pos, patrolTarget);
        pos.x += dir.x * speed * dt;
        pos.y += dir.y * speed * dt;
    }
}
