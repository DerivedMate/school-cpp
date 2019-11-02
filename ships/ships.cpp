#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <algorithm>
#include <thread>
#include <vector>
#include "player.cpp"
#include "gamemode.cpp"

#ifdef _WIN32
#define CLEAR "CLS"
#endif

#ifdef linux
#define CLEAR "CLEAR"
#endif

const int ui_width = 56;

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

#ifdef _WIN32
#include <windows.h>

void wait(int milliseconds)
{
  Sleep(milliseconds);
}
#else
void wait(int ms)
{
  std::this_thread::sleep_for(std::chrono::microseconds(ms * 1000));
}
#endif

void wait_std()
{
  wait(900);
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
  bool allLegal = true;
  for (std::string &l : l1)
    std::cout << center(l, width) << std::endl;

  do
  {
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
      int buff;
      std::cin >> buff;

      if (buff > dim[0] || buff > dim[1])
      {
        std::cout << buff << " is a bit too big. Try a new config!" << std::endl;

        types = {};
        allLegal = false;
        break;
      }
      else
        allLegal = true;

      types.push_back(buff);
    }
  } while (!allLegal);
}

std::string string_of_int(int x)
{
  std::string l;
  if (x <= 9)
  {
    l += ' ';
    l += char(x + '0');
  }
  else
  {
    int a = x % 10;
    int b = (x % 100 - a) / 10;
    l += b + '0';
    l += a + '0';
  }

  return l;
}

void displayTopCoords(int *dim)
{
  std::cout << std::flush;
  std::string l = "  |";
  for (int x = 0; x < dim[0]; x++)
  {
    l += string_of_int(x);
    l += "|";
  }
  std::cout << center(l, ui_width) << std::endl;
}

void displayBoard(Player *main, Player *other, int *dim)
{
  std::string lHit = "XX|";
  std::string lAttacked = "**|";
  std::string lFail = "OO|";
  std::string lShip = "##|";
  std::string lWater = "  |";

  displayTopCoords(dim);

  for (int y = 0; y < dim[1]; y++)
  {
    std::string line = "";
    line += string_of_int(y);
    line += "|";

    for (int x = 0; x < dim[0]; x++)
    {
      bool isShip = std::find_if(main->ships.begin(), main->ships.end(), [x, y](Ship &s) {
                      return s.wouldHit(x, y);
                    }) != main->ships.end();

      auto trie = std::find_if(main->hits.begin(), main->hits.end(), [x, y](Point &p) {
        return p.x == x && p.y == y;
      });
      bool isTrie = trie != main->hits.end();

      bool isHit = false;
      if (isTrie)
      {
        isHit = std::find_if(other->ships.begin(), other->ships.end(), [trie](Ship &s) {
                  return s.wasHitBy(&*trie);
                }) != other->ships.end();
      }

      bool wasHitByEnemy = std::find_if(other->hits.begin(), other->hits.end(), [x, y](Point &p) {
                             return p.x == x && p.y == y;
                           }) != other->hits.end();

      if (isShip && wasHitByEnemy)
        line += lAttacked;
      else if (isShip)
        line += lShip;
      else if (isHit)
        line += lHit;
      else if (isTrie)
        line += lFail;
      else
        line += lWater;
    }

    std::cout << center(line, ui_width) << std::endl;
  }
}

void initPlayer(Player *player, std::vector<int> &types, int *dim, Player *other)
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
  std::string l2 = "Are you satisfied with your placement? [y/n] ";

  center(l1, ui_width);
  center(l2, ui_width);

  clearScreen();
  displayLogo();

  for (std::string &l : l0)
    std::cout << center(l, ui_width) << std::endl;

  std::cin.get();
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
      displayBoard(player, other, dim);
      bool added = false;

      while (!added)
      {
        std::cout << "[" << sz << "]> ";
        std::cin >> x >> y >> dir;
        Direction d = direction_of_string(dir);

        Ship ship = Ship(x, y, d, sz);
        // x, y, d, sz, dim
        bool canAdd = Ship::can_be_built(&ship, dim, player->ships);
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
    displayBoard(player, other, dim);

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

void gameon(Player *main, Player *other, int *dim)
{
  std::string lHit[] = {
      " _   _ ___ _____ _ ",
      "| | | |_ _|_   _| |",
      "| |_| || |  | | | |",
      "|  _  || |  | | |_|",
      "|_| |_|___| |_| (_)"};

  std::string lMiss[] = {
      " __  __ ___ ____ ____  _ ",
      "|  \\\/  |_ _/ ___/ ___|| |",
      "| |\\\/| || |\\___ \\___ \\| |",
      "| |  | || | ___) ___) |_|",
      "|_|  |_|___|____|____/(_)"};

  for (std::string &l : lHit)
    center(l, ui_width);
  for (std::string &l : lMiss)
    center(l, ui_width);

  clearScreen();
  displayLogo();

  if (main->isAI)
    main->attack_rand(other, dim[0], dim[1]);
  else
  {
    std::string l0[] = {
        "It's your round " + main->name + "!",
        "Score: " + main->hits.size() + '0',
        "Enter your guess below.",
        "(i.e.: 3 2)"};

    for (std::string &l : l0)
      std::cout << center(l, ui_width) << std::endl;

    int x, y;
    displayBoard(main, other, dim);
    std::cout << "\n\n> ";
    std::cin >> x >> y;

    bool didHit = main->attack(other, x, y);
    if (didHit)
      for (std::string &l : lHit)
        std::cout << l << std::endl;
    else
      for (std::string &l : lMiss)
        std::cout << l << std::endl;

    wait_std();
  }
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

  initPlayer(a, shipsTypes, dim, b);
  if (mode == PVP)
    initPlayer(b, shipsTypes, dim, b);
  else
    initPC(b, shipsTypes);

  while (!(a->isDead() || b->isDead()))
  {
    gameon(a, b, dim);
    std::swap(a, b);
  }

  return 0;
}