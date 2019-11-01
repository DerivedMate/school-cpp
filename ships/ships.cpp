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

const int ui_width = 52;

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