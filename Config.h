#pragma once

namespace Config {
    // --- Worker ---
    constexpr float WorkerRadius = 10.0f;
    constexpr int   WorkerHP = 18;
    constexpr int   WorkerAttack = 10;
    constexpr float WorkerSpeed = 120.0f;   // units/sec
    constexpr int   WorkerCost = 2;         // larva

    // --- Forager ---
    constexpr float ForagerRadius = 7.5f;
    constexpr int   ForagerHP = 12;
    constexpr int   ForagerAttack = 3;
    constexpr float ForagerSpeed = 100.0f;
    constexpr int   ForagerCost = 1;

    // --- Soldier ---
    constexpr float SoldierRadius = 12.0f;
    constexpr int   SoldierHP = 30;
    constexpr int   SoldierAttack = 15;
    constexpr float SoldierSpeed = 90.0f;
    constexpr int   SoldierCost = 5;

    // --- Predator ---
    constexpr float PredatorRadius = 14.0f;
    constexpr int   PredatorHP = 25;
    constexpr int   PredatorAttack = 8;
    constexpr float PredatorSpeed = 80.0f;

    // --- Nest ---
    constexpr float NestRadius = 60.0f;
    constexpr int   NestHP = 100;
}
