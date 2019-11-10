#include <time.h>
#include <iostream>
#include <stdlib.h>
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

    wait_std(ui_width);
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
  center(l1, ui_width);

  // -------- Configure the dimensions -------- //
  for (std::string &l : l0)
    std::cout << center(l, ui_width) << std::endl;

  for (int i = 0; i < 2; i++)
  {
    bool keep_asking = false;
    do
    {
      if (keep_asking)
        std::cout << "Sorry, it's not a number; try an other one!" << std::endl;
      auto [is_fine, num] = read_int();
      dim[i] = num;

      keep_asking = !is_fine;
    } while (keep_asking);
  }
  max_x_len = len_of_int(dim[1]);

  ui_width = dim[0] * 6;

  // -------- Configure the ships -------- //
  bool allLegal = true;
  // for (std::string &l : l1)
  //   std::cout << center(l, ui_width) << std::endl;

  do
  {
    allLegal = true;
    clearScreen();
    displayLogo(ui_width);

    std::cout << l1 << std::endl;
    auto [fine_n, n_] = read_int();

    if (!fine_n || n_ <= 0)
    {
      allLegal = false;
      continue;
    };

    n = n_;

    for (int i = 0; i < n; i++)
    {
    RES_BUFF_CONF:
      int buff;
      if (!allLegal)
        std::cout << "This ain't right, try a new config!" << std::endl;

      std::cout << "What's the size of the [" << i + 1 << "/" << n << "] ship?\n:> ";
      auto [fine_buff, buff_] = read_int();
      buff = buff_;

      if (!fine_buff || buff > std::max({dim[0], dim[1]}) || buff <= 0) {
        std::cout << "That ain't right chief!" << std::endl;
        goto RES_BUFF_CONF;
      }

      else if (mult_vec(types) > dim[0] * dim[1])
      {
        std::cout << "Ya ain't gonna fit that in!\nLet's start from the beginning!" << std::endl;
        pause(ui_width);
        types = {};
        allLegal = false;
      }
      else
        allLegal = true;

      types.push_back(buff);
    }
  } while (!allLegal);
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
  std::string lHit = Colors::Red + "XX" + Colors::Reset + "|";
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
      "Imma need it's y and x coords and the direction.",
      "(i.e.: [4]> A5 South)",
      "",
      "You can always type " + Colors::Cyan + "?help" + Colors::Reset + " lest you get lost",
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

  RESET_GAMEON:
    clearScreen();
    displayLogo(ui_width);
    std::string l0[] = {
        "It's your round " + main->name + "!",
        "Score: " + main->hits.size() + '0',
        "Enter your guess below.",
        "(i.e.: 3 2)"};

    for (std::string &l : l0)
      std::cout << center(l, ui_width) << std::endl;

    displayBoard(main, other, dim);

    Point p = read_coords(max_x_len, ui_width);
    if (p.x == -99 && p.y == -99)
    {
      displayCoordsHelp(ui_width);
      goto RESET_GAMEON;
    }

    bool didHit = main->attack(other, p.x, p.y);

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

  if (!a->isAI && !b->isAI)
    pause(ui_width, true);

  while (!(a->isDead() || b->isDead()))
  {
    gameon(a, b, dim);
    std::swap(a, b);

    wait(900);
    pause(ui_width, true);
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