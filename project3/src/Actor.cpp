#include "Actor.h"
#include "StudentWorld.h"
#include <cstdlib>

#pragma region Actor
Actor::Actor(int image_id, int x, int y, int dir, int depth, int size, StudentWorld *world) : GraphObject(image_id, x, y, dir, depth, size), m_world(world), m_alive(true)
{
}

void Actor::relativeMove(int dx, int dy)
{
    moveTo(getX() + dx, getY() + dy);
}

bool Actor::isCollidingWith(double x, double y)
{
    if (getX() + SPRITE_WIDTH - 1 < x || x + SPRITE_WIDTH - 1 < getX())
    {
        return false;
    }
    if (getY() + SPRITE_HEIGHT - 1 < y || y + SPRITE_HEIGHT - 1 < getY())
    {
        return false;
    }
    return true;
}

bool Actor::isCollidingWith(Actor *a)
{
    return isCollidingWith(a->getX(), a->getY());
}

#pragma endregion Actor
#pragma region Goodie
// TODO separate classes
Goodie::Goodie(int x, int y, GoodieType goodie_type, StudentWorld *world) : Actor(goodie_type == FLOWER ? IID_FLOWER : goodie_type == MUSHROOM ? IID_MUSHROOM
                                                                                                                                               : IID_STAR,
                                                                                  x, y, 0, 1, 1, world),
                                                                            m_point_value(goodie_type == FLOWER ? 50 : goodie_type == MUSHROOM ? 75
                                                                                                                                               : 100),
                                                                            m_goodie_type(goodie_type)
{
}
void Goodie::doSomething()
{
    if (getWorld()->isCollidingWithPeach(this))
    {
        getWorld()->increaseScore(50);
        getWorld()->givePeachPower(m_goodie_type);
        if (m_goodie_type != STAR)
        {
            getWorld()->setPeachHP(2);
        }
        kill();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    if (getWorld()->willCollide(this, true, Direction::DOWN, 2) == nullptr)
    {
        relativeMove(0, -2);
    }
    bool facing_right = getDirection() == 0;
    if (facing_right)
    {
        if (getWorld()->willCollide(this, true, Direction::RIGHT, 2) != nullptr)
        {
            setDirection(180);
        }
        else
        {
            relativeMove(2, 0);
        }
    }
    else if (!facing_right)
    {
        if (getWorld()->willCollide(this, true, Direction::LEFT, 2) != nullptr)
        {
            setDirection(0);
        }
        else
        {
            relativeMove(-2, 0);
        }
    }
}
#pragma endregion Goodie

#pragma region Peach
Peach::Peach(int x_start, int y_start, StudentWorld *world) : Actor(IID_PEACH, x_start, y_start, 0, 0, 1, world)
{
    m_hp = 1;
    m_invincible = false;
    m_recharging = false;
    m_invincibility_ticks = 0;
    m_recharge_ticks = 0;
    for (int i = 0; i < 3; i++)
    {
        m_powers[i] = false;
    }
}

void Peach::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    if (isInvincible())
    {
        m_invincibility_ticks--;
        if (m_invincibility_ticks == 0)
        {
            m_invincible = false;
        }
    }
    if (m_recharging)
    {
        m_recharge_ticks--;
        if (m_recharge_ticks == 0)
        {
            m_recharging = false;
        }
    }
    getWorld()->bonkAllCollisions(this, false);
    if (m_remaining_jump_distance > 0)
    {
        Actor *above = getWorld()->willCollide(this, true, Direction::UP, 4);
        if (above != nullptr)
        {
            above->bonk(this);
            m_remaining_jump_distance = 0;
        }
        else
        {
            relativeMove(0, 4);
            m_remaining_jump_distance--;
        }
    }
    Actor *below = getWorld()->willCollide(this, true, Direction::DOWN, 4);
    if (m_remaining_jump_distance == 0 && below == nullptr)
    {
        relativeMove(0, -4);
    }
    int key;
    if (getWorld()->getKey(key))
    {
        switch (key)
        {
        case KEY_PRESS_LEFT:
            setDirection(180);
            if (getWorld()->willCollide(this, true, Direction::LEFT, 4) == nullptr)
            {
                relativeMove(-4, 0);
            }
            break;
        case KEY_PRESS_RIGHT:
            setDirection(0);
            if (getWorld()->willCollide(this, true, Direction::RIGHT, 4) == nullptr)
            {
                relativeMove(4, 0);
            }
            break;
        case KEY_PRESS_UP:
            if (getWorld()->willCollide(this, true, Direction::DOWN, 4) != nullptr)
            {
                if (hasJump())
                {
                    m_remaining_jump_distance = 12;
                }
                else
                {
                    m_remaining_jump_distance = 8;
                }
                getWorld()->playSound(SOUND_PLAYER_JUMP);
            }
            break;
        case KEY_PRESS_SPACE:
            if (hasShoot() && m_recharge_ticks <= 0)
            {
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                m_recharging = true;
                m_recharge_ticks = 8;
                int dx = (getDirection() == 0) ? 4 : -4;
                getWorld()->addActor(new Fireball(getX() + dx, getY(), getDirection(), false, getWorld()));
            }

            break;
        }
    }
}

void Peach::givePower(Goodie::GoodieType goodie)
{
    if (goodie == Goodie::GoodieType::FLOWER)
    {
        m_powers[0] = true;
    }
    else if (goodie == Goodie::MUSHROOM)
    {
        m_powers[1] = true;
    }
    else if (goodie == Goodie::STAR)
    {
        m_powers[2] = true;
        m_invincible = true;
        m_invincibility_ticks = 150;
    }
}

void Peach::bonk(Actor *bonker) {}
void Peach::damage() {}
#pragma endregion Peach

#pragma region Block
Block::Block(int x, int y, BlockType block_type, StudentWorld *world) : Actor(block_type == PIPE ? IID_PIPE : IID_BLOCK, x, y, 0, 2, 1, world), m_block_type(block_type)
{
    m_released_goodie = false;
}
void Block::bonk(Actor *bonker)
{
    if (!m_released_goodie && m_block_type != Block::NONE && m_block_type != Block::PIPE)
    {
        m_released_goodie = true;
        Goodie::GoodieType goodie_type;
        if (m_block_type == BlockType::FLOWER)
        {
            goodie_type = Goodie::GoodieType::FLOWER;
        }
        else if (m_block_type == BlockType::MUSHROOM)
        {
            goodie_type = Goodie::GoodieType::MUSHROOM;
        }
        else if (m_block_type == BlockType::STAR)
        {
            goodie_type = Goodie::GoodieType::STAR;
        }
        getWorld()->addActor(new Goodie(getX(), getY() + 8, goodie_type, getWorld()));
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
    }
    else
    {
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }
}
#pragma endregion Block
#pragma region Flag
Flag::Flag(int x, int y, bool is_final, StudentWorld *world) : Actor(is_final ? IID_MARIO : IID_FLAG, x, y, 0, 1, 1, world), m_is_final(is_final)
{
}

void Flag::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    if (getWorld()->isCollidingWithPeach(this))
    {
        kill();
        getWorld()->increaseScore(1000);
        if (m_is_final)
        {
            getWorld()->gameComplete();
        }
        else
        {
            getWorld()->levelComplete();
        }
    }
}
#pragma endregion Flag

#pragma region Fireball
Fireball::Fireball(int x, int y, int dir, bool is_shell, StudentWorld *world) : Actor(is_shell ? IID_SHELL : IID_PEACH_FIRE, x, y, dir, 1, 1, world)
{
}

void Fireball::doSomething()
{
    getWorld()->damageAllCollisions(this, true, true);
    if (getWorld()->willCollide(this, true, Direction::DOWN, 2) == nullptr)
    {
        relativeMove(0, -2);
    }
    bool facing_right = getDirection() == 0;
    if (facing_right)
    {
        if (getWorld()->willCollide(this, true, Direction::RIGHT, 4) != nullptr)
        {
            kill();
        }
        else
        {
            relativeMove(2, 0);
        }
    }
    else if (!facing_right)
    {
        if (getWorld()->willCollide(this, true, Direction::LEFT, 2) != nullptr)
        {
            kill();
        }
        else
        {
            relativeMove(-2, 0);
        }
    }
}
#pragma endregion Fireball

#pragma region Goomba
Goomba::Goomba(int x, int y, StudentWorld *world) : Actor(IID_GOOMBA, x, y, 0, 0, 1, world) // TODO make dir random
{
}
void Goomba::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    if (getWorld()->isCollidingWithPeach(this))
    {
        getWorld()->bonkPeach(this);
        return;
    }
    bool facing_right = getDirection() == 0;
    // TODO check overhangs
    if (facing_right)
    {
        if (getWorld()->willCollide(this, true, Direction::RIGHT, 1) != nullptr)
        {
            setDirection(180);
        }
        else
        {
            relativeMove(1, 0);
        }
    }
    else if (!facing_right)
    {
        if (getWorld()->willCollide(this, true, Direction::LEFT, 1) != nullptr)
        {
            setDirection(0);
        }
        else
        {
            relativeMove(-1, 0);
        }
    }
}
void Goomba::bonk(Actor *bonker)
{
}
void Goomba::damage() {}
#pragma endregion Goomba