#include <time.h>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>
#include <algorithm>
#include <thread>
#include <vector>

#ifdef _WIN32
#define CLEAR "CLS"
#endif

#ifdef linux
#define CLEAR "CLEAR"
#endif

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
    return North;
    break;
  case 1:
    return East;
    break;
  case 2:
    return South;
    break;
  case 3:
    return West;
    break;
  default:
    throw "Unrecongized int case at {direction_of_int}";
    break;
  }
}

enum GameMode
{
  PVP,
  PVC
};

GameMode gamemode_of_int(int x)
{
  switch (x)
  {
  case 0:
    return PVP;
    break;
  case 1:
    return PVC;
    break;
  }
}

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
    Point out = *this;
    out.x += other->x;
    out.y += other->y;

    return out;
  }

  bool operator==(Point &other)
  {
    return this->x == other.x && this->y == other.y;
  }
};

struct Ship
{
  Point bow;
  Point stern;
  Direction dir;

  int total_lifes;
  std::vector<Point> hits;

  Ship(int x0, int y0, Direction dir, int size)
  {
    total_lifes = size;
    this->stern = Point(x0, y0);
    this->bow = this->stern;
    this->dir = dir;

    this->bow.add(dir, size);
  }

  ~Ship()
  {
  }

  int lifes()
  {
    return this->total_lifes - this->hits.size();
  }

  bool wouldHit(int x, int y)
  {
    bool possible;
    switch (this->dir)
    {
    case North:
      possible = x == this->bow.x && y <= this->bow.y && y >= this->stern.y;
      break;
    case South:
      possible = x == this->bow.x && y >= this->bow.y && y <= this->stern.y;
      break;
    case East:
      possible = y == this->bow.y && x >= this->bow.x && x <= this->stern.x;
      break;
    case West:
      possible = y == this->bow.y && x <= this->bow.x && x >= this->stern.x;
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

  static bool can_be_built(int x0, int y0, Direction dir, int size, int *dim)
  {
    Point a = Point(x0, y0);
    Point b = a;
    b.add(dir, size);

    bool can = (b.x >= 0 && b.x <= dim[0]) && (b.y >= 0 && b.y <= dim[1]);
    return can;
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

    return (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4) != 0;
  }
};

struct Player
{
  // -------- Player's tries -------- //
  std::vector<Point> hits;
  std::vector<Ship> ships;

  Player() {}
  void addShip(Ship &ship)
  {
    this->ships.push_back(ship);
  }

  void removeShip(Point &p)
  {
    auto ptr = std::find_if(this->ships.begin(), this->ships.end(), [p](Ship &s) {
      return s.wouldHit(p.x, p.y);
    });

    if (ptr != this->ships.end())
      delete &*ptr;
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
      return true;
    }
    else
      return false;
  }

  bool attack(Player* player, int x, int y)
  {
    return player->hit(x, y);
  }
};

void clearScreen()
{
#ifdef _WIN32
  std::system("cls");
#endif
#ifdef linux
  std::system("clear");
#endif
}

std::string center(std::string &text, int width)
{
  int len = text.size();
  int marginSize = (width - len) / 2;

  std::string margin = "";
  for (int i = 0; i < marginSize; i++)
    margin += " ";

  text = margin + text;
  return text;
}

void displayLogo()
{
  std::string art[] = {
      "______       _   _   _      _____ _     _                 ",
      "| ___ \\     | | | | | |    /  ___| |   (_)               ",
      "| |_/ / __ _| |_| |_| | ___\\ `--.| |__  _ _ __  ___      ",
      "| ___ \\/ _` | __| __| |/ _ \\`--. \\ '_ \\| | '_ \\/ __| ",
      "| |_/ / (_| | |_| |_| |  __/\\__/ / | | | | |_) \\__ \\   ",
      "\\____/ \\__,_|\\__|\\__|_|\\___\\____/|_| |_|_| .__/|___/",
      "                                         | |              ",
      "                                         |_|              ",
      "                                                          ",
      // "                                                          ",

  };

  for (std::string &line : art)
  {
    std::cout << line << std::endl;
  }
}

void displayWelcomeScreen(int width)
{
  clearScreen();
  displayLogo();

  std::string menu[] = {
      "Welcome in the game!",
      "Your main objective is to defeat",
      "your enemy!",
      "",
      "We'll quickly walk you throgh",
      "a few configuration-screens on which",
      "you'll be able to set things like:",
      "- The GameMode                 ",
      "- The number and types of ships",
      "- Dimensions of the board      ",
      "",
      "",
      "PRESS ANY KEY TO START"};

  for (std::string &line : menu)
    std::cout << center(line, width) << std::endl;

  std::cout << std::flush;
  std::cin.get();
}

void countDown(int width)
{
  const int DIGIT_HEIGHT = 6;
  std::string digits[3][DIGIT_HEIGHT] = {
      {

          " _____ ",
          "(__  / ",
          "  / /  ",
          " (__ \\ ",
          " ___) )",
          "(____/ ",
      },
      {
          " ____  ",
          "(___ \\ ",
          "  __) )",
          " / __/ ",
          "| |___ ",
          "|_____)",
      },
      {" _ ",
       "/ |",
       "- |",
       "| |",
       "| |",
       "|_|"}};

  for (auto dig : digits)
  {
    displayLogo();
    for (int i = 0; i < DIGIT_HEIGHT; i++)
      std::cout << center(dig[i], width) << std::endl;

    std::this_thread::sleep_for(std::chrono::microseconds(900000));
    clearScreen();
  }
}

GameMode getGameMode(int width)
{
  clearScreen();
  displayLogo();
  char buff;

  // -------- Print the gamemode menu -------- //
  std::string lines[] = {
      "Choose the gamemode:",
      "1. Player vs. Player",
      "2. Player vs. Computer",
  };

  for (std::string &l : lines)
    std::cout << center(l, width) << std::endl;
  std::cout << std::flush;

  while (!(buff == '1' || buff == '2'))
    buff = std::cin.get();

  return gamemode_of_int(buff - '0' - 1);
}

void displayConfig(std::vector<int> &types, int *dim, int width)
{
  clearScreen();
  displayLogo();

  int n;

  std::string l0[] = {
      "Enter the dimensions of the board",
      "(i.e.: 10 10):"};

  std::string l1[] = {
      "Give me the number of ships",
      "followed by their sizes (i.e. 3 2 2 1):"};

  // -------- Configure the dimensions -------- //
  for (std::string &l : l0)
    std::cout << center(l, width) << std::endl;

  std::cin >> dim[0] >> dim[1];

  clearScreen();
  displayLogo();

  // -------- Configure the ships -------- //
  for (std::string &l : l1)
    std::cout << center(l, width) << std::endl;
  std::cin >> n;

  for (int i = 0; i < n; i++)
  {
    int buff;
    std::cin >> buff;
    types.push_back(buff);
  }
}

int main()
{
  int ui_width = 52;
  std::vector<int> shipTypes;
  int dim[2] = {0, 0};
  GameMode mode;
  // Ship a = Ship(1, 3, North, 9);
  // Ship b = Ship(5, 0, North, 10);
  // std::cout << Ship::intersect(a, b);
  clearScreen();
  countDown(ui_width);

  displayWelcomeScreen(ui_width);
  mode = getGameMode(ui_width);
  displayConfig(shipTypes, dim, ui_width);

  Player a, b;

  return 0;
}