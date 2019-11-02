#include "point.cpp"
#include <vector>
#include <algorithm>

struct Ship
{
  Point bow;
  Point stern;
  Direction dir;

  int total_lifes = 1;
  std::vector<Point> hits = {};

  Ship(int x0, int y0, Direction dir, int size)
  {
    this->total_lifes = size;
    this->stern = Point(x0, y0);
    this->bow = stern;
    this->dir = dir;
    this->hits = {};

    this->bow.add(dir, size - 1);
  }

  ~Ship() {}

  int lifes()
  {
    return this->total_lifes - this->hits.size();
  }

  bool wasHitBy(Point *p)
  {
    return std::find_if(this->hits.begin(), this->hits.end(), [p](Point &h) {
             return (*p) == h;
           }) != this->hits.end();
  }

  bool wouldHit(int x, int y)
  {
    bool possible;
    switch (this->dir)
    {
    case North:
      possible = x == this->bow.x && y >= this->bow.y && y <= this->stern.y;
      break;
    case South:
      possible = x == this->bow.x && y <= this->bow.y && y >= this->stern.y;
      break;
    case East:
    {
      bool py = y == this->bow.y;
      bool px = x >= this->stern.x && x <= this->bow.x;
      possible = py && px;
    }
    break;
    case West:
      possible = y == this->bow.y && x <= this->stern.x && x >= this->bow.x;
      break;
    default:
    {
      possible = true;
      std::cout << "[DEBUG]> Unknown Direction of a ship" << std::endl;
    };
    break;
    }

    if (!possible)
      return possible;

    bool wasHit = false;
    Point c = Point(x, y);

    for (auto p = this->hits.begin(); p != this->hits.end() && !wasHit; p++)
      wasHit = *(p) == c;

    return !wasHit;
  }

  static bool can_be_built(Ship *ship, int *dim, std::vector<Ship> &others)
  {
    auto collison = std::find_if(others.begin(), others.end(), [ship](Ship &s) {
      return ship->intersect(s);
    });
    return (ship->bow.x >= 0 && ship->bow.x <= dim[0]) && (ship->bow.y >= 0 && ship->bow.y <= dim[1]) && (ship->dir == North || ship->dir == South || ship->dir == East || ship->dir == West);
  }

  static bool intersect(Ship &a, Ship &b)
  {
    int x1 = a.bow.x;
    int y1 = a.bow.y;

    int x2 = a.stern.x;
    int y2 = a.stern.y;

    int x3 = b.bow.x;
    int y3 = b.bow.y;

    int x4 = b.stern.x;
    int y4 = b.stern.y;

    bool sameLineX = (x4 <= x1 && x4 >= x2) || (x3 <= x1 && x3 >= x2);
    bool sameLineY = (y4 <= y1 && y4 >= y2) || (y3 <= y1 && y3 >= y2);
    bool overlapping = sameLineX || sameLineY;

    return overlapping || (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4) != 0;
  }

  bool intersect(Ship &other)
  {
    return Ship::intersect(*this, other);
  }
};