#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include "Level.h"
#include <iomanip>
#include <list>
#include <sstream>
#include <string>

using namespace std;

GameWorld *createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath), m_level_complete(false), m_game_complete(false), m_on_last_level(false)
{
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}
void StudentWorld::bonkAllCollisions(Actor *bonker, bool must_be_solid)
{
    for (auto bonked : m_actors)
    {
        if (must_be_solid && !bonked->isSolid())
        {
            continue;
        }
        if (bonked != bonker && bonked->isCollidingWith(bonker))
        {
            bonked->bonk(bonker);
        }
    }
}
void StudentWorld::damageAllCollisions(Actor *damager, bool exclude_peach, bool die_on_impact)
{
    for (auto damaged : m_actors)
    {
        if (!damaged->isAlive())
        {
            continue;
        }
        if (exclude_peach && (damaged == m_peach))
        {
            continue;
        }
        if (damaged != damager && damaged->isCollidingWith(damager))
        {
            damager->kill();
            damaged->damage();
            return;
        }
    }
}
Actor *StudentWorld::willCollide(Actor *actor, bool is_solid, Direction dir, int dist)
{
    int dx = dir == LEFT ? -dist : (dir == RIGHT ? dist : 0);
    int dy = dir == UP ? dist : (dir == DOWN ? -dist : 0);
    int x = actor->getX() + dx;
    int y = actor->getY() + dy;
    for (auto collider : m_actors)
    {
        if (!collider->isAlive())
        {
            continue;
        }
        if (collider != actor && collider->isCollidingWith(x, y))
        {
            if (is_solid == collider->isSolid())
            { // TODO check
                return collider;
            }
        }
    }
    return nullptr;
}
Actor *StudentWorld::willCollide(Actor *actor, Direction dir, int dist)
{
    Actor *collision = willCollide(actor, false, dir, dist);
    if (collision == nullptr)
    {
        collision = willCollide(actor, true, dir, dist);
    }
    return collision;
}
void StudentWorld::setGameStatus()
{
    std::ostringstream status;
    status << "Lives: " << getLives() << "  Level: " << getLevel() << "  Points: " << getScore() << " ";
    if (m_peach->hasStar())
    {
        status << "Star Power! ";
    }
    if (m_peach->hasShoot())
    {
        status << "Shoot Power! ";
    }
    if (m_peach->hasJump())
    {
        status << "Jump Power! ";
    }
    setGameStatText(status.str());
}

int StudentWorld::init()
{
    Level level(assetPath());
    std::ostringstream level_name;
    level_name.fill('0');
    level_name << "level" << std::setw(2) << getLevel() << ".txt";

    Level::LoadResult result = level.loadLevel(level_name.str());
    if (result == Level::load_fail_bad_format)
    {
        std::cerr << "ERROR: bad level format (" << level_name.str() << ")" << std::endl;
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_fail_file_not_found)
    {
        std::cerr << "ERROR: level file doesn't exist (" << level_name.str() << ")" << std::endl;
        return GWSTATUS_LEVEL_ERROR;
    }

    for (int row = 0; row < GRID_HEIGHT; row++)
    {
        for (int col = 0; col < GRID_WIDTH; col++)
        {
            Level::GridEntry ge = level.getContentsOf(col, row);
            int x = col * SPRITE_WIDTH;
            int y = row * SPRITE_HEIGHT;
            switch (ge)
            {

            case Level::peach:
                m_peach = new Peach(x, y, this);
                m_actors.push_back(m_peach);
                break;
            case Level::block:
                m_actors.push_back(new Block(x, y, Block::NONE, this));
                break;
            case Level::mushroom_goodie_block:
                m_actors.push_back(new Block(x, y, Block::MUSHROOM, this));
                break;
            case Level::flower_goodie_block:
                m_actors.push_back(new Block(x, y, Block::FLOWER, this));
                break;
            case Level::star_goodie_block:
                m_actors.push_back(new Block(x, y, Block::STAR, this));
                break;
            case Level::pipe:
                m_actors.push_back(new Block(x, y, Block::PIPE, this));
                break;
            case Level::flag:
                m_actors.push_back(new Flag(x, y, false, this));
                break;
            case Level::mario:
                m_on_last_level = true;
                m_actors.push_back(new Flag(x, y, true, this));
                break;
            case Level::goomba:
                m_actors.push_back(new Goomba(x, y, this));
                break;
            case Level::koopa:
                m_actors.push_back(new Koopa(x, y, this));
                break;
            case Level::piranha:
                m_actors.push_back(new Piranha(x, y, this));
                break;
            }
        }
    }

    return GWSTATUS_CONTINUE_GAME;
}
int StudentWorld::move()
{

    for (auto actor : m_actors)
    {
        if (actor->isAlive())
        {
            actor->doSomething(); // TODO peach check for dead actors (page 21 paragraph 2)
        }
    }
    if (!m_peach->isAlive())
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    for (auto it = m_actors.begin(); it != m_actors.end(); it++)
    {
        if (!(*it)->isAlive())
        {
            delete (*it);
            it = m_actors.erase(it);
        }
    }
    setGameStatus();

    if (m_game_complete)
    {
        return GWSTATUS_PLAYER_WON;
    }
    if (m_level_complete)
    {
        m_level_complete = false;
        return GWSTATUS_FINISHED_LEVEL;
    }

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (auto actor : m_actors)
    {
        delete actor;
    }
    m_actors.clear(); // TODO check if needed
}
