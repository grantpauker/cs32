#include "Actor.h"
#include "StudentWorld.h"
#include <cstdlib>

#pragma region Actor

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

void Actor::relativeMove(int dx, int dy)
{
    moveTo(getX() + dx, getY() + dy);
}

#pragma endregion Actor

#pragma region Goodie
Goodie::Goodie(int x, int y, int id, StudentWorld *world) : Actor(id, x, y, 0, 1, 1, world) {}
void Goodie::doSomething()
{
    if (getWorld()->isCollidingWithPeach(this))
    {
        getWorld()->increaseScore(getPoints());
        getWorld()->givePeachPower(getType());
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        kill();
        return;
    }
    if (getWorld()->willCollide(this, 0, -2) == nullptr)
    {
        relativeMove(0, -2);
    }
    bool facing_right = getDirection() == 0;
    int dx = facing_right ? 2 : -2;
    int new_dir = facing_right ? 180 : 0;
    if (getWorld()->willCollide(this, dx, 0) != nullptr)
    {
        setDirection(new_dir);
    }
    else
    {
        relativeMove(dx, 0);
    }
}

void Flower::doSomething()
{
    Goodie::doSomething();
    if (getWorld()->isCollidingWithPeach(this))
    {
        getWorld()->setPeachHP(2);
    }
}

void Mushroom::doSomething()
{
    Goodie::doSomething();
    if (getWorld()->isCollidingWithPeach(this))
    {
        getWorld()->setPeachHP(2);
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

    getWorld()->bonkAllCollisions(this);

    if (m_remaining_jump_distance > 0)
    {
        Actor *above = getWorld()->willCollide(this, 0, 4);
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
    else if (getWorld()->willCollide(this, 0, -4) == nullptr)
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
            if (getWorld()->willCollide(this, -4, 0) == nullptr)
            {
                relativeMove(-4, 0);
            }
            break;
        case KEY_PRESS_RIGHT:
            setDirection(0);
            if (getWorld()->willCollide(this, 4, 0) == nullptr)
            {
                relativeMove(4, 0);
            }
            break;
        case KEY_PRESS_UP:
            if (getWorld()->willCollide(this, 0, -1) != nullptr)
            {
                m_remaining_jump_distance = hasJump() ? 12 : 8;
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
                getWorld()->addActor(new PeachProjectile(getX() + dx, getY(), getDirection(), true, getWorld()));
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

void Peach::bonk(Actor *bonker)
{
    if (m_invincible)
    {
        return;
    }
    m_hp--;
    m_invincibility_ticks = 10;
    m_powers[0] = false;
    m_powers[1] = false;
    if (m_hp == 0)
    {
        kill();
        return;
    }
    getWorld()->playSound(SOUND_PLAYER_HURT);
}

void Peach::damage()
{
    bonk(nullptr);
}
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
        if (m_block_type == BlockType::FLOWER)
        {
            getWorld()->addActor(new Flower(getX(), getY() + 8, getWorld()));
        }
        else if (m_block_type == BlockType::MUSHROOM)
        {
            getWorld()->addActor(new Mushroom(getX(), getY() + 8, getWorld()));
        }
        else if (m_block_type == BlockType::STAR)
        {
            getWorld()->addActor(new Star(getX(), getY() + 8, getWorld()));
        }
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
    }
    else
    {
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }
}
#pragma endregion Block

#pragma region Flag
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

#pragma region Projectile
void Projectile::doSomething()
{
    if (getWorld()->willCollide(this, 0, -2) == nullptr)
    {
        relativeMove(0, -2);
    }
    bool facing_right = getDirection() == 0;
    int dx = facing_right ? 2 : -2;
    if (getWorld()->willCollide(this, dx, 0) != nullptr)
    {
        kill();
    }
    else
    {
        relativeMove(dx, 0);
    }
}

void PeachProjectile::doSomething()
{
    getWorld()->damageAllCollisions(this, true, true);
    Projectile::doSomething();
}

void PiranhaFireball::doSomething()
{
    if (getWorld()->isCollidingWithPeach(this))
    {
        getWorld()->damagePeach();
        kill();
        return;
    }
    Projectile::doSomething();
}
#pragma endregion Projectile

#pragma region Enemies
void Enemy::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    if (getWorld()->isCollidingWithPeach(this))
    {
        getWorld()->bonkPeach(this);
    }
}

void Enemy::bonk(Actor *bonker)
{
    if (!getWorld()->isPeach(bonker))
    {
        return;
    }
    if (getWorld()->isPeachHaveStar())
    {
        getWorld()->playSound(SOUND_PLAYER_KICK);
        Enemy::damage();
    }
}

void Enemy::damage()
{
    getWorld()->increaseScore(100);
    kill();
}

void MovingEnemy::doSomething()
{
    Enemy::doSomething();
    if(!isAlive()){
        return;
    }
    bool facing_right = getDirection() == 0;
    int dx = facing_right ? 1 : -1;
    int new_dir = facing_right ? 180 : 0;
    if (getWorld()->isHangingOverEdge(this))
    {
        setDirection(new_dir);
        dx *= -1;
    }
    if (getWorld()->willCollide(this, dx, 0) != nullptr)
    {
        setDirection(new_dir);
    }
    else
    {
        relativeMove(dx, 0);
    }
}

void Koopa::bonk(Actor *bonker)
{
    Enemy::bonk(bonker);
    if (!isAlive())
    {
        getWorld()->addActor(new PeachProjectile(getX(), getY(), getDirection(), false, getWorld()));
    }
}

void Koopa::damage()
{
    MovingEnemy::damage();
    if (!isAlive())
    {
        getWorld()->addActor(new PeachProjectile(getX(), getY(), getDirection(), false, getWorld()));
    }
}

void Piranha::doSomething()
{
    Enemy::doSomething();
    if(!isAlive()){
        return;
    }
    increaseAnimationNumber();
    if (!getWorld()->isNearPeach(this))
    {
        return;
    }
    int distance_to_peach = getWorld()->distanceToPeach(this);
    int dir = distance_to_peach > 0 ? 180 : 0;
    setDirection(dir);
    if (m_firing_delay >= 0)
    {
        m_firing_delay--;
        return;
    }
    if (abs(distance_to_peach) < 8 * SPRITE_WIDTH)
    {
        getWorld()->addActor(new PiranhaFireball(getX(), getY(), getDirection(), getWorld()));
        getWorld()->playSound(SOUND_PIRANHA_FIRE);
        m_firing_delay = 40;
    }
}
#pragma endregion Enemies