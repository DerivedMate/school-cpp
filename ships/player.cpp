#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "ship.cpp"
#include "util.cpp"

struct Player
{
  // -------- Player's tries -------- //
  std::vector<Point> hits = {};
  std::vector<Ship> ships = {};
  std::string name;
  bool isAI = false;

  Player()
  {
    name = "unknown";
  }

  Player(std::string &name)
  {
    this->name = name;
  }

  ~Player()
  {
  }

  bool isDead()
  {
    return this->ships.size() == 0;
  }

  void removeShip(Point &p)
  {
    auto ptr = std::find_if(this->ships.begin(), this->ships.end(), [p](Ship &s) {
      return s.wouldHit(p.x, p.y);
    });

    if (ptr != this->ships.end())
      delete &*ptr;
  }

  bool addShip(Ship &s)
  {
    bool collision = false;
    for (auto p = this->ships.begin(); p != this->ships.end() && !collision; p++)
    {
      collision = Ship::intersect(s, *p);
    }

    if (!collision)
      this->ships.push_back(s);
    return !collision;
  }

  bool hit(int x, int y)
  {
    Point p = Point(x, y);
    auto boat = std::find_if(this->ships.begin(), this->ships.end(), [x, y](Ship &s) {
      return s.wouldHit(x, y);
    });

    if (boat != this->ships.end())
    {
      this->hits.push_back(p);
      boat->hits.push_back(p);
      if(boat->lifes() == 0) this->removeShip(p);
      return true;
    }
    else
      return false;
  }

  bool attack(Player *player, int x, int y)
  {
    return player->hit(x, y);
  }

  bool attack_rand(Player *player, int max_x, int max_y)
  {
    int x = rand(0, max_x);
    int y = rand(0, max_y);
  }
};