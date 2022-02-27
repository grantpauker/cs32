#ifndef STUDENT_WORLD_H
#define STUDENT_WORLD_H

#include "Actor.h"
#include "GameWorld.h"
#include "Level.h"
#include <list>
#include <string>

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  ~StudentWorld();

  virtual int init();
  virtual int move();
  virtual void cleanUp();

  void addActor(Actor *actor) { m_actors.push_back(actor); }
  void levelComplete() { m_level_complete = true; }
  void gameComplete() { m_game_complete = true; }

  bool isPeach(Actor *actor) { return actor == m_peach; }
  bool isPeachHaveStar() { return m_peach->hasStar(); }
  void getPeachPosition(int *x, int *y)
  {
    *x = m_peach->getX();
    *y = m_peach->getY();
  }
  bool isCollidingWithPeach(Actor *actor) { return actor->isCollidingWith(m_peach); }
  bool isHangingOverEdge(Actor *actor);
  bool isNearPeach(Actor *actor) { return abs(actor->getY() - m_peach->getY()) <= 1.5 * SPRITE_WIDTH; }
  Actor *willCollide(Actor *actor, int dx, int dy);

  void bonkPeach(Actor *bonker) { m_peach->bonk(bonker); }
  void damagePeach() { m_peach->damage(); }
  void bonkAllCollisions(Actor *bonker);
  void damageAllCollisions(Actor *damager, bool exclude_peach, bool die_on_impact);

  void setPeachHP(int hp) { m_peach->setHP(hp); }
  void givePeachPower(Goodie::GoodieType goodie_type) { m_peach->givePower(goodie_type); }

private:
  void setGameStatus();

  std::list<Actor *> m_actors;
  Peach *m_peach;

  bool m_level_complete;
  bool m_game_complete;
};

#endif // STUDENT_WORLD_H
