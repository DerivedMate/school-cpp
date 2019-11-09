#include <stdio.h>
#include <iostream>

enum Direction
{
  North,
  East,
  South,
  West
};

Direction direction_of_int(int x)
{
  switch (x)
  {
  case 0:
    return Direction::North;
    break;
  case 1:
    return Direction::East;
    break;
  case 2:
    return Direction::South;
    break;
  case 3:
    return Direction::West;
    break;
  default:
    throw "Unrecongized int case at {direction_of_int}";
    break;
  }
}

Direction direction_of_string(std::string &x)
{
  if (x == "North" || x == "north" || x == "n" || x == "N")
    return Direction::North;
  else if (x == "South" || x == "south" || x == "s" || x == "S")
    return Direction::South;
  else if (x == "East" || x == "east" || x == "e" || x == "E")
    return Direction::East;
  else if (x == "West" || x == "west" || x == "w" || x == "W")
    return Direction::West;
}