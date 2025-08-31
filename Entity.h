#pragma once
#include "raylib.h"

class World; // forward declare

class Entity {
public:
    Entity(Vector2 pos, float radius, Color color, int hp, int attack, float speed)
        : pos(pos), radius(radius), color(color), hp(hp), attack(attack), speed(speed), alive(true) {
    }

    virtual ~Entity() = default;

    virtual void Update(World& world) = 0;
    virtual void Draw() const;

    // Add this for type checking
    virtual const char* GetType() const = 0;

    bool IsAlive() const { return alive; }
    Vector2 GetPos() const { return pos; }
    float GetRadius() const { return radius; }
    int GetHP() const { return hp; }
    int GetAttack() const { return attack; }
    void TakeDamage(int dmg) { hp -= dmg; if (hp <= 0) alive = false; }

protected:
    Vector2 pos;
    float radius;
    Color color;
    int hp;
    int attack;
    float speed;
    bool alive;
};
