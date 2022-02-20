#ifndef STUDENT_WORLD_H
#define STUDENT_WORLD_H

#include "Actor.h"
#include "GameWorld.h"
#include "Level.h"
#include <list>
#include <string>

enum Direction
{
  LEFT,
  RIGHT,
  UP,
  DOWN
};
class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);

  virtual int init();
  virtual int move();
  virtual void cleanUp();

  void addActor(Actor *actor) { m_actors.push_back(actor); }
  void levelComplete() { m_level_complete = true; }
  void gameComplete() { m_game_complete = true; }
  bool isPeach(Actor *actor) { return actor == m_peach; }

  void bonkAllCollisions(Actor *bonker, bool must_be_solid);
  void damageAllCollisions(Actor *damager, bool exclude_peach, bool die_on_impact);
  Actor *willCollide(Actor *actor, bool is_solid, Direction dir, int dist);
  Actor *willCollide(Actor *actor, Direction dir, int dist);
  bool isCollidingWithPeach(Actor *actor) { return actor->isCollidingWith(m_peach); }
  void bonkPeach(Actor *bonker) { m_peach->bonk(bonker); }
  void givePeachPower(Goodie::GoodieType goodie_type) { m_peach->givePower(goodie_type); }
  void setPeachHP(int hp) { m_peach->setHP(hp); }

private:
  void setGameStatus();
  std::list<Actor *> m_actors;
  Peach *m_peach;
  bool m_level_complete;
  bool m_game_complete;
  bool m_on_last_level;
};

#endif // STUDENT_WORLD_H
