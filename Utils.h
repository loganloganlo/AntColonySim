#pragma once
#include "raylib.h"

// Compute squared distance between two positions
float DistanceSq(const Vector2& a, const Vector2& b);

// Compute actual distance (uses sqrtf)
float Distance(const Vector2& a, const Vector2& b);

// Clamp a position inside the screen
Vector2 ClampToScreen(const Vector2& pos, int screenWidth, int screenHeight, float radius);

// Get a random direction (-1, 0, or 1 for each axis)
Vector2 RandomDirection();

// Get a normalized direction vector from a to b
Vector2 DirectionTo(const Vector2& from, const Vector2& to);
