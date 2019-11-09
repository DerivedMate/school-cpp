#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <chrono>
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

int ui_width = 56;
int max_x_len = 0;

void displayWelcomeScreen()
{
  clearScreen();
  displayLogo(ui_width);

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
    std::cout << center(line, ui_width) << std::endl;

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
  std::string l0 = "PRESS ENTER TO CONTINUE";
  std::cout << std::endl
            << center(l0, ui_width) << std::endl;
}

void countDown()
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
    displayLogo(ui_width);
    for (int i = 0; i < DIGIT_HEIGHT; i++)
      std::cout << center(dig[i], ui_width) << std::endl;

    wait_std();
    clearScreen();
  }
}

GameMode getGameMode()
{
  clearScreen();
  displayLogo(ui_width);
  char buff;

  // -------- Print the gamemode menu -------- //
  std::string lines[] = {
      "Choose the gamemode:",
      "1. Player vs. Player",
      "2. Player vs. Computer",
  };

  for (std::string &l : lines)
    std::cout << center(l, ui_width) << std::endl;
  std::cout << std::flush;

  while (!(buff == '1' || buff == '2'))
    buff = std::cin.get();

  return gamemode_of_int(buff - '0' - 1);
}

void displayConfig(std::vector<int> &types, int *dim)
{
  clearScreen();
  displayLogo(ui_width);

  int n;

  std::string l0[] = {
      "Enter the dimensions of the board",
      "(i.e.: 10 10):"};

  std::string l1 = "How many types of ships do you want?";

  // -------- Configure the dimensions -------- //
  for (std::string &l : l0)
    std::cout << center(l, ui_width) << std::endl;

  std::cin >> dim[0] >> dim[1];
  max_x_len = len_of_int(dim[1]);

  ui_width = dim[0] * 6;

  // -------- Configure the ships -------- //
  bool allLegal = true;
  // for (std::string &l : l1)
  //   std::cout << center(l, ui_width) << std::endl;

  do
  {
    clearScreen();
    displayLogo(ui_width);

    std::cout << center(l1, ui_width) << std::endl;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
      int buff;
      std::cout << "What's the size of the [" << i + 1 << "/" << n << "] ship?\n:>";
      std::cin >> buff;

      if (buff > dim[0] || buff > dim[1])
      {
        std::cout << buff << " is a bit too big. Try a new config!" << std::endl;

        types = {};
        allLegal = false;
        break;
      }
      else if (mult_vec(types) > dim[0] * dim[1])
      {
        std::cout << "Ya ain't gonna fit that in!\nLet's start from the beginning!" << std::endl;
        types = {};
        allLegal = false;
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
    std::string letter = syx_of_int(y);
    if (letter.size() < 2)
      line += ' ';
    else
      letter[0] -= 1;
    line += letter;
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

      // std::cout << "[" << x << " : " << y << "]" << ": ";
      // for(const bool& b : {isShip, isTrie, wasHitByEnemy}) {
      //   std::cout << (b ? "YES, " : "NO, ");
      // }

      if (wasHitByEnemy)
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
  displayLogo(ui_width);

  std::string l00 = "What's your name?";
  std::cout << center(l00, ui_width) << "\n> ";
  std::cin >> player->name;

  std::string l0[] = {
      "Player " + player->name + ",",
      "It's high time you place your ships!",
      "Imma need it's x 'n y coords and the direction.",
      "(i.e.: [4]> 3 2 South)",
      "",
      "PRESS ENTER TO CONTINUE"};

  std::string l1 = "Choose your placement " + player->name + "\n";
  std::string l2 = "Are you satisfied with your placement? [y/n] ";

  center(l1, ui_width);
  center(l2, ui_width);

  clearScreen();
  displayLogo(ui_width);

  for (std::string &l : l0)
    std::cout << center(l, ui_width) << std::endl;

  std::cin.get();
  std::cin.get();

  bool satisfied = false;
  char satBuff;

  while (!satisfied)
  {
    std::string dir;
    player->ships = {};

    for (int &sz : types)
    {
    RCSTART:
      clearScreen();
      displayLogo(ui_width);
      std::cout << l1;
      displayBoard(player, other, dim);
      bool added = false;

      while (!added)
      {
        Point coord = read_coords(max_x_len, ui_width, sz);
        if (coord.x == -99 && coord.y == -99)
        {
          displayCoordsHelp(ui_width);
          goto RCSTART;
        }

        std::cin >> dir;
        Direction d = direction_of_string(dir);

        Ship ship = Ship(coord.x, coord.y, d, sz);
        added = player->addShip(ship, dim);
        if (!added)
        {
          std::cout << "Failed to add due to a collision / getting out of the boundries.\nTry a new position (pun not intended)!" << std::endl;
        }
      }
    }

    clearScreen();
    displayLogo(ui_width);
    displayBoard(player, other, dim);

    std::cout << l2;
    std::cin >> satBuff;
    if (satBuff == 'y' || satBuff == 'Y')
      satisfied = true;
  }
}

void initPC(Player *pc, std::vector<int> &types, int *dim)
{
  pc->isAI = true;
  for (int i = 0; i < types.size(); i++)
  {
    bool placed = false;

    while (!placed)
    {
      int x = rand(0, dim[0]);
      int y = rand(0, dim[1]);
      Direction dir = direction_of_int(rand(0, 3));

      Ship s = Ship(x, y, dir, types[i]);
      placed = pc->addShip(s, dim);
    }
  }
}

void gameon(Player *main, Player *other, int *dim)
{
  if (main->isAI)
    main->attack_rand(other, dim[0], dim[1]);
  else
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
    displayLogo(ui_width);
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

    clearScreen();
    displayLogo(ui_width);

    if (didHit)
      for (std::string &l : lHit)
        std::cout << l << std::endl;
    else
      for (std::string &l : lMiss)
        std::cout << l << std::endl;

    std::cout << "Current Score" << std::endl
              << main->name << ": " << main->score(other) << " / " << other->score(main) << " :" << other->name << std::endl;

    wait_std();
  }
}

int main()
{

  std::vector<int> shipsTypes;
  int dim[2] = {0, 0};
  GameMode mode;
  clearScreen();
  countDown();

  displayWelcomeScreen();
  mode = getGameMode();
  displayConfig(shipsTypes, dim);

  Player *a = new Player(), *b = new Player();

  initPlayer(a, shipsTypes, dim, b);
  if (mode == PVP)
    initPlayer(b, shipsTypes, dim, b);
  else
    initPC(b, shipsTypes, dim);

  while (!(a->isDead() || b->isDead()))
  {
    gameon(a, b, dim);
    std::swap(a, b);

    pause(ui_width);
  }

  if (a->isDead())
    std::swap(a, b);

  std::string l = a->name + " WON!";
  std::cout << center(l, ui_width) << std::endl;

  std::string buff;
  while (std::cin >> buff && true)
    std::cout << int_of_string(buff) << std::endl;

  return 0;
}