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

const int ui_width = 52;
int rand(int a, int b)
{
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(a, b);
  return distr(eng);
}

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

Direction direction_of_string(std::string &x)
{
  if (x == "North" || x == "north")
    return North;
  else if (x == "South" || x == "south")
    return South;
  else if (x == "East" || x == "east")
    return East;
  else if (x == "West" || x == "west")
    return West;
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

  static bool can_be_built(Ship &ship, int *dim)
  {
    return (ship.bow.x >= 0 && ship.bow.x <= dim[0]) && (ship.bow.y >= 0 && ship.bow.y <= dim[1]) && (ship.dir == North || ship.dir == South || ship.dir == East || ship.dir == West);
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

void wait(int ms)
{
  std::this_thread::sleep_for(std::chrono::microseconds(ms));
}

void wait_std()
{
  wait(900000);
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

    wait_std();
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

void displayShips(Player *player, int *dim)
{
  const std::string boat = "|[]|";
  const std::string water = "|  |";

  for (int y = 0; y < dim[1]; y++)
  {
    std::string layout = "";
    for (int x = 0; x < dim[0]; x++)
    {
      auto hsip = std::find_if(player->ships.begin(), player->ships.end(), [x, y](Ship &s) {
        return s.wouldHit(x, y);
      });

      if (hsip != player->ships.end())
        layout += boat;
      else
        layout += water;
    }
    std::cout << center(layout, ui_width) << std::endl;
  }

  std::cout << std::endl;
}

void initPlayer(Player *player, std::vector<int> &types, int *dim)
{
  clearScreen();
  displayLogo();

  std::string l00 = "What's your name?";
  std::cout << center(l00, ui_width) << "\n> ";
  std::cin >> player->name;

  std::string l0[] = {
      "Player " + player->name + ",",
      "It's high time you place your ships!",
      "Imma need it's x 'n y coords and the direction.",
      "(i.e.: [4]> 3 2 South)",
      "",
      "PRESS ANY KEY TO CONTINUE"};

  std::string l1 = "Choose your placement " + player->name + "\n";
  std::string l2 = "Are you satisfied with your placement? [y/n]";
  center(l1, ui_width);
  center(l2, ui_width);

  clearScreen();
  displayLogo();

  for (std::string &l : l0)
    std::cout << center(l, ui_width) << std::endl;

  std::cin.get();

  bool satisfied = false;
  char satBuff;

  while (!satisfied)
  {
    int x, y;
    std::string dir;
    player->ships = {};

    for (int &sz : types)
    {
      clearScreen();
      displayLogo();
      std::cout << l1;
      displayShips(player, dim);
      bool added = false;

      while (!added)
      {
        std::cout << "[" << sz << "]> ";
        std::cin >> x >> y >> dir;
        Direction d = direction_of_string(dir);

        Ship ship = Ship(x, y, d, sz);
        // x, y, d, sz, dim
        bool canAdd = Ship::can_be_built(ship, dim);
        if (canAdd)
          added = player->addShip(ship);
        if (!added)
        {
          std::cout << "Failed to add due to a collision / getting out of the boundries.\nTry a new position (pun not intended)!" << std::endl;
        }
      }
    }

    clearScreen();
    displayLogo();
    displayShips(player, dim);

    std::cout << l2;
    std::cin >> satBuff;
    if (satBuff == 'y' || satBuff == 'Y')
      satisfied = true;
  }
}

void initPC(Player *pc, std::vector<int> &types)
{
  pc->isAI = true;
}

void gameon(Player *main, Player *other)
{
  std::cin.ignore();
}

int main()
{
  std::vector<int> shipsTypes;
  int dim[2] = {0, 0};
  GameMode mode;
  clearScreen();
  countDown(ui_width);

  displayWelcomeScreen(ui_width);
  mode = getGameMode(ui_width);
  displayConfig(shipsTypes, dim, ui_width);

  Player *a = new Player(), *b = new Player();

  initPlayer(a, shipsTypes, dim);
  if (mode == PVP)
    initPlayer(b, shipsTypes, dim);
  else
    initPC(b, shipsTypes);

  while (!(a->isDead() || b->isDead()))
  {
    gameon(a, b);
    std::swap(a, b);
  }

  return 0;
}