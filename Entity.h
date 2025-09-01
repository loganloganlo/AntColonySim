#pragma once
#include "raylib.h"

class World;

class Entity {
public:
    Entity(Vector2 pos, float radius, Color color, int hp, int attack, float speedPerSecond)
        : pos(pos), radius(radius), color(color),
        hp(hp), attack(attack), speed(speedPerSecond),
        alive(true) {
    }

    virtual ~Entity() = default;

    // Logic
    virtual void Update(World& world) = 0;

    // Drawing (subclasses can override)
    virtual void Draw() const;

    // Type
    virtual const char* GetType() const = 0;

    // State helpers
    bool IsAlive() const { return alive; }
    Vector2 GetPos() const { return pos; }
    float GetRadius() const { return radius; }
    int GetHP() const { return hp; }
    int GetAttack() const { return attack; }
    float GetSpeed() const { return speed; }

    void TakeDamage(int dmg) {
        hp -= dmg;
        if (hp <= 0) alive = false;
    }

protected:
    Vector2 pos;
    float radius;
    Color color;
    int hp;
    int attack;
    float speed;  // units per second
    bool alive;
};
