#ifndef ACTOR_H
#define ACTOR_H

#include "GameConstants.h"
#include "GraphObject.h"

class StudentWorld;

#pragma region Actor
class Actor : public GraphObject
{
public:
    Actor(int image_id, int x, int y, int dir, int depth, int size, StudentWorld *world) : GraphObject(image_id, x, y, dir, depth, size), m_world(world), m_alive(true) {}

    virtual void doSomething() = 0;
    virtual void bonk(Actor *bonker) {}
    virtual void damage() {}
    virtual bool isSolid() const { return false; }
    virtual bool isDamageable() const { return false; }

    bool isAlive() const { return m_alive; }
    StudentWorld *getWorld() const { return m_world; }

    bool isCollidingWith(double x, double y) const;
    bool isCollidingWith(Actor *a) const;

    void kill() { m_alive = false; }
    void relativeMove(int dx, int dy);

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
    Goodie(int x, int y, int id, StudentWorld *world);

    virtual GoodieType getType() const = 0;
    virtual int getPoints() const = 0;

    virtual void doSomething();
};

class Flower : public Goodie
{
public:
    Flower(int x, int y, StudentWorld *world) : Goodie(x, y, IID_FLOWER, world) {}

    virtual GoodieType getType() const { return FLOWER; }
    virtual int getPoints() const { return 50; }

    virtual void doSomething();
};

class Mushroom : public Goodie
{
public:
    Mushroom(int x, int y, StudentWorld *world) : Goodie(x, y, IID_MUSHROOM, world) {}

    virtual GoodieType getType() const { return MUSHROOM; }
    virtual int getPoints() const { return 75; }

    virtual void doSomething();
};

class Star : public Goodie
{
public:
    Star(int x, int y, StudentWorld *world) : Goodie(x, y, IID_STAR, world) {}

    virtual GoodieType getType() const { return STAR; }
    virtual int getPoints() const { return 100; }
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

    bool isInvincible() const { return m_powers[2] || m_temp_invincibility_ticks > 0; }

    void setHP(int hp) { m_hp = hp; }
    void givePower(Goodie::GoodieType goodie);

    bool hasShoot() const { return m_powers[0]; }
    bool hasJump() const { return m_powers[1]; }
    bool hasStar() const { return m_powers[2]; }

private:
    int m_hp;
    int m_temp_invincibility_ticks;
    int m_star_power_ticks;
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

    virtual bool isSolid() const { return true; }

private:
    BlockType m_block_type;
    bool m_released_goodie;
};
#pragma endregion Block

#pragma region Flag
class Flag : public Actor
{
public:
    Flag(int x, int y, bool is_final, StudentWorld *world) : Actor(is_final ? IID_MARIO : IID_FLAG, x, y, 0, 1, 1, world), m_is_final(is_final) {}
    virtual void doSomething();

private:
    bool m_is_final;
};
#pragma endregion Flag

#pragma region Projectile
class Projectile : public Actor
{
public:
    Projectile(int x, int y, int dir, int id, StudentWorld *world) : Actor(id, x, y, dir, 1, 1, world) {}
    virtual void doSomething();
};

class PeachProjectile : public Projectile
{
public:
    PeachProjectile(int x, int y, int dir, bool is_fireball, StudentWorld *world) : Projectile(x, y, dir, is_fireball ? IID_PEACH_FIRE : IID_SHELL, world) {}
    virtual void doSomething();
};

class PiranhaFireball : public Projectile
{
public:
    PiranhaFireball(int x, int y, int dir, StudentWorld *world) : Projectile(x, y, dir, IID_PIRANHA_FIRE, world) {}
    virtual void doSomething();
};
#pragma endregion Projectile

#pragma region EnemyBase
class Enemy : public Actor
{
public:
    Enemy(int x, int y, int id, StudentWorld *world) : Actor(id, x, y, randInt(0, 1) * 180, 0, 1, world) {}

    virtual void doSomething();
    virtual void bonk(Actor *bonker);
    virtual void damage();
    virtual bool isDamageable() const { return true; }
};

class MovingEnemy : public Enemy
{
public:
    MovingEnemy(int x, int y, int id, StudentWorld *world) : Enemy(x, y, id, world) {}

    virtual void doSomething();
};
#pragma endregion EnemyBase

#pragma region Enemies
class Goomba : public MovingEnemy
{
public:
    Goomba(int x, int y, StudentWorld *world) : MovingEnemy(x, y, IID_GOOMBA, world) {}
};

class Koopa : public MovingEnemy
{
public:
    Koopa(int x, int y, StudentWorld *world) : MovingEnemy(x, y, IID_KOOPA, world) {}

    virtual void bonk(Actor *bonker);
    virtual void damage();
};

class Piranha : public Enemy
{
public:
    Piranha(int x, int y, StudentWorld *world) : Enemy(x, y, IID_PIRANHA, world) , m_firing_delay(0) {}

    virtual void doSomething();

private:
    int m_firing_delay;
};
#pragma endregion Enemies

#endif // ACTOR_H
