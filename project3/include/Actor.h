#ifndef ACTOR_H
#define ACTOR_H

#include "GameConstants.h"
#include "GraphObject.h"

class StudentWorld;

#pragma region Actor
class Actor : public GraphObject
{
public:
    Actor(int image_id, int x, int y, int dir, int depth, int size, StudentWorld *world);
    virtual void doSomething() = 0;
    virtual void bonk(Actor *bonker) = 0;
    virtual void damage() = 0;
    virtual bool isBonkable() { return true; }
    virtual bool isSolid() { return false; }
    virtual bool isDamageable() { return false; }

    void kill() { m_alive = false; }

    bool isAlive() { return m_alive; }
    StudentWorld *getWorld() { return m_world; }

    void relativeMove(int dx, int dy);

    bool isCollidingWith(double x, double y);
    bool isCollidingWith(Actor *a);

private:
    StudentWorld *m_world;
    bool m_alive;
};
#pragma endregion Actor

#pragma region Goodie
class Goodie : public Actor
{
public:
    enum GoodieType
    {
        FLOWER,
        MUSHROOM,
        STAR
    };
    Goodie(int x, int y, GoodieType goodie_type, StudentWorld *world);
    virtual void doSomething();
    virtual void bonk(Actor *bonker) {}
    virtual void damage() {}

private:
    GoodieType m_goodie_type;
    int m_point_value;
};
#pragma endregion Goodie

#pragma region Peach
class Peach : public Actor
{
public:
    Peach(int x_start, int y_start, StudentWorld *world);

    virtual void doSomething();
    virtual void bonk(Actor *bonker);
    virtual void damage();

    bool isInvincible() { return m_invincible; }
    bool isRecharghing() { return m_recharging; }

    void setHP(int hp) { m_hp = hp; }
    void givePower(Goodie::GoodieType goodie);

    bool hasShoot() { return m_powers[0]; }
    bool hasJump() { return m_powers[1]; }
    bool hasStar() { return m_powers[2]; }

private:
    int m_hp;
    bool m_invincible;
    int m_invincibility_ticks;
    bool m_recharging;
    int m_recharge_ticks;
    bool m_powers[3]; // shoot, jump, star
    int m_remaining_jump_distance;
};
#pragma endregion Peach

#pragma region Block
class Block : public Actor
{
public:
    enum BlockType
    {
        NONE,
        STAR,
        MUSHROOM,
        FLOWER,
        PIPE
    };
    Block(int x, int y, BlockType block_type, StudentWorld *world);
    virtual void doSomething() {}
    virtual void bonk(Actor *bonker);
    virtual void damage() {}

    virtual bool isSolid() { return true; }

private:
    BlockType m_block_type;
    bool m_released_goodie;
};
#pragma endregion Block

#pragma region Flag
class Flag : public Actor
{
public:
    Flag(int x, int y, bool is_final, StudentWorld *world);
    virtual void doSomething();
    virtual void bonk(Actor *bonker) {}
    virtual void damage() {}

private:
    bool m_is_final;
};
#pragma endregion Flag

#pragma region Projectile
class Projectile : public Actor
{
public:
    Projectile(int x, int y, int dir, int id, StudentWorld *world);
    virtual void doSomething();
    virtual void bonk(Actor *bonker) {}
    virtual void damage() {}

private:
};

class PeachFireball : public Projectile
{

public:
    PeachFireball(int x, int y, int dir, StudentWorld *world) : Projectile(x, y, dir, IID_PEACH_FIRE, world) {}
    virtual void doSomething();
};

class Shell : public Projectile
{

public:
    Shell(int x, int y, int dir, StudentWorld *world) : Projectile(x, y, dir, IID_SHELL, world) {}
    virtual void doSomething();
};

class PiranhaFireball : public Projectile
{

public:
    PiranhaFireball(int x, int y, int dir, StudentWorld *world) : Projectile(x, y, dir, IID_PIRANHA_FIRE, world) {}
    virtual void doSomething();
};
#pragma endregion Projectile

#pragma region Goomba
class MovingEnemy : public Actor
{
public:
    MovingEnemy(int x, int y, int id, StudentWorld *world) : Actor(id, x, y, randInt(0, 1) * 180, 0, 1, world) {}

    virtual void doSomething();
    virtual void bonk(Actor *bonker);
    virtual void damage();
    virtual bool isDamageable() { return true; }
};
class Goomba : public MovingEnemy
{
public:
    Goomba(int x, int y, StudentWorld *world) : MovingEnemy(x, y, IID_GOOMBA, world) {}
};

#pragma endregion Goomba

#pragma region Koopa
class Koopa : public MovingEnemy
{
public:
    Koopa(int x, int y, StudentWorld *world) : MovingEnemy(x, y, IID_KOOPA, world) {}

    virtual void bonk(Actor *bonker);
    virtual void damage();
};

class Piranha : public Actor
{
public:
    Piranha(int x, int y, StudentWorld *world) : Actor(IID_PIRANHA, x, y, randInt(0, 1) * 180, 0, 1, world) {}

    virtual void doSomething();
    virtual void bonk(Actor *bonker);
    virtual void damage();
    virtual bool isDamageable() { return true; }

private:
    int m_firing_delay;
};
#pragma endregion Koopa

#endif // ACTOR_H
