#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "ship.cpp"

struct Player
{
  // -------- Player's tries -------- //
  std::vector<Point> hits = {};
  std::vector<Ship> ships = {};
  std::string name;
  int max_lives = 0;
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

  int score(Player* other) {
    int total_hits_dealt = 0;

    for(Ship& s : other->ships) 
      total_hits_dealt += s.hits.size();

    return other->max_lives - total_hits_dealt;
  }

  void removeShip(Point *p)
  {
    auto ptr = std::find_if(this->ships.begin(), this->ships.end(), [p](Ship &s) {
      return s.wasHitBy(p);
    });

    if (ptr != this->ships.end())
    {
      this->ships.erase(ptr);
    }
  }

  bool addShip(Ship &s, int* dim)
  {
    // -------- Check boundries -------- //
    int min_c = std::min({s.bow.x, s.bow.y, s.stern.x, s.stern.y});
    int max_cx = std::max({s.bow.x, s.stern.x});
    int max_cy = std::max({s.bow.y, s.stern.y});
    if (min_c < 0 || max_cx > dim[0] || max_cy > dim[1])
      return false;

    // -------- Check for a collison -------- //
    bool collision = false;
    for (auto p = this->ships.begin(); p != this->ships.end() && !collision; p++)
    {
      collision = Ship::intersect(s, *p);
    }

    if (!collision) {
      this->ships.push_back(s);
      this->max_lives += s.lifes();
    }
    return !collision;
  }

  // Get hit
  bool hit(Player *attacker, int x, int y)
  {
    Point p = Point(x, y);
    auto boat = std::find_if(this->ships.begin(), this->ships.end(), [x, y](Ship &s) {
      return s.wouldHit(x, y);
    });

    if (boat != this->ships.end())
    {
      attacker->hits.push_back(p);
      boat->hits.push_back(p);
      if (boat->lifes() == 0)
        this->removeShip(&p);
      return true;
    }
    else
      return false;
  }

  bool attack(Player *player, int x, int y)
  {
    return player->hit(this, x, y);
  }

  bool attack_rand(Player *player, int max_x, int max_y)
  {
    bool repeated = true;
    int x, y;

    while (repeated)
    {
      x = rand(0, max_x);
      y = rand(0, max_y);

      repeated = std::find_if(this->hits.begin(), this->hits.end(), [x, y](Point &p) {
                   return p.x == x && p.y == y;
                 }) != this->hits.end();
    }

    return player->hit(this, x, y);
  }
};