#include "direction.cpp"
struct Point
{
  int x;
  int y;

  Point()
  {
  }

  Point(int _x, int _y)
  {
    x = _x;
    y = _y;
  }

  ~Point() {}

  Point add(int _x, int _y)
  {
    this->x += _x;
    this->y += _y;
  }

  Point add(Direction dir, int x)
  {
    switch (dir)
    {
    case North:
      this->add(0, -x);
      break;
    case East:
      this->add(x, 0);
      break;
    case South:
      this->add(0, x);
      break;
    case West:
      this->add(-x, 0);
      break;
    }
  }

  Point &operator+(Point *other)
  {
    Point *out = new Point(this->x, this->y);
    out->x += other->x;
    out->y += other->y;

    return *out;
  }

  bool operator==(Point &other)
  {
    return this->x == other.x && this->y == other.y;
  }
};