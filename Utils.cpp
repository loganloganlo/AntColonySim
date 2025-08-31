#include "Utils.h"
#include <cmath>

float DistanceSq(const Vector2& a, const Vector2& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return dx * dx + dy * dy;
}

float Distance(const Vector2& a, const Vector2& b) {
    return sqrtf(DistanceSq(a, b));
}

Vector2 ClampToScreen(const Vector2& pos, int screenWidth, int screenHeight, float radius) {
    Vector2 clamped = pos;
    if (clamped.x < radius) clamped.x = radius;
    if (clamped.y < radius) clamped.y = radius;
    if (clamped.x > screenWidth - radius) clamped.x = screenWidth - radius;
    if (clamped.y > screenHeight - radius) clamped.y = screenHeight - radius;
    return clamped;
}

Vector2 RandomDirection() {
    int dx = GetRandomValue(-1, 1);
    int dy = GetRandomValue(-1, 1);
    return Vector2{ (float)dx, (float)dy };
}

Vector2 DirectionTo(const Vector2& from, const Vector2& to) {
    Vector2 dir = { to.x - from.x, to.y - from.y };
    float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
    if (len > 0.001f) {
        dir.x /= len;
        dir.y /= len;
    }
    return dir;
}
