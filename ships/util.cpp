#include <iostream>
#include <random>
#include <algorithm>
#include "colors.cpp"
#include "point.cpp"

int rand(int a, int b)
{
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(a, b);
  return distr(eng);
}

void clearScreen()
{
#ifdef _WIN32
  std::system("cls");
#endif
#ifdef linux
  std::system("clear");
#endif
}

void displayLogo(int width)
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

  };

  for (std::string &line : art)
  {
    std::cout << line << std::endl;
  }
}

std::string makeMargin(int n)
{
  std::string margin = "";
  for (int i = 0; i < n; i++)
    margin += " ";

  return margin;
}

std::string center(std::string &text, int width)
{
  int len = text.size();
  int marginSize = (width - len + 1) / 2;

  std::string margin = makeMargin(marginSize);

  text = margin + text;
  return text;
}

int len_of_int(int n)
{
  if (n == 0)
    return 1;

  int i = 0;
  while (n != 0)
  {
    n /= 10;
    i++;
  }

  return i;
}

int mult_vec(std::vector<int> &v)
{
  int o = 1;
  for (int &x : v)
    o *= x;

  return o;
}

// Base:26 numbers
typedef std::string Syx;
const int BASE_SYX = 26;

int int_of_string(std::string &s)
{
  int sum = 0;
  int n = s.size() - 1;
  for (int i = 0; i < s.size(); i++)
    sum += (s[i] - '0') * (int)pow(10.0, double(n - i));

  return sum;
}

Syx syx_of_int(int n)
{
  Syx n_syx;
  int i = 0;
  do
  {
    char l = (n % BASE_SYX) + 'A';
    n_syx = l + n_syx;

    i++;
    n /= BASE_SYX;
  } while (n != 0);

  return n_syx;
}

int int_of_syx(std::string &s)
{
  int len = s.size();
  int out = 0;
  for (int i = 0; i < len; i++)
    out += (s[i] - 'A' + (i != len - 1 ? 1 : 0)) * (int)std::pow((double)BASE_SYX, (double)(len - i - 1));

  return out;
}

bool is_num(std::string &s)
{
  return std::find_if(s.begin(), s.end(), [](char &c) {
           int n = c - '0';
           return n >= 0 && n <= 9;
         }) != s.end();
}

bool is_num(char &s)
{
  int n = s - '0';
  return n >= 0 && n <= 9;
}

void displayCoordsHelp(int ui_width)
{
  clearScreen();
  displayLogo(ui_width);

  std::string l0[] = {
      "1. " + Colors::Green + " How do I enter coordinates?                                       " + Colors::Reset,
      "When you're asked to enter coordinates, you'll be greeted with such a screen:     ",
      "[size_of_the_ship]> <coord_y><coord_x> <direction>                    ",
      "",
      "<coord_y>  : A, B, C, ..., AA, AB, ...                                ",
      "<coord_x>  : 1, 2, 3, ..., 10, 11, ...                                ",
      "<direction>: North, East, South, West                                 ",
      "",
      "Here's an example:                                                    ",
      Colors::Cyan + "[4]> A12 North" + Colors::Reset + makeMargin(47),
      "",
      "PRESS ENTER TO GO BACK",
  };

  for (std::string &l : l0)
    std::cout << center(l, ui_width) << std::endl;

  std::cin.get();
  std::cin.get();
}

Point read_coords(int max_x_length, int ui_width, int shipSize)
{
  std::string buff;
  std::string y_buff, x_buff;
  std::cout << "[" << shipSize << "]> ";
  std::cin >> buff;

  if (buff == "?help")
    return Point(-99, -99);

  for (char &c : buff)
  {
    if (!is_num(c))
      y_buff += c;
    else
      x_buff += c;
  }

  int x = int_of_string(x_buff);
  int y = int_of_syx(y_buff);
  return Point(x, y);
}

void pause(int ui_width, bool with_art = false)
{
  std::string l0[] = {
      " ____   _   _   _ ____  _____ ",
      "|  _ \\ / \\ | | | / ___|| ____|",
      "| |_) / _ \\| | | \\___ \\|  _|  ",
      "|  __/ ___ | |_| |___) | |___ ",
      "|_| /_/   \\_\\___/|____/|_____|",
      "PRESS ENTER TO CONTINUE"};

  if (with_art)
  {
    clearScreen();
    displayLogo(ui_width);
    for (std::string &s : l0)
      std::cout << center(s, ui_width) << std::endl;
  }

  else
    std::cout << center(l0[5], ui_width) << std::endl;

  std::cin.get();
}

bool onSegment(Point p, Point q, Point r)
{
  if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
      q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
    return true;

  return false;
}

int orientation(Point p, Point q, Point r)
{
  int val = (q.y - p.y) * (r.x - q.x) -
            (q.x - p.x) * (r.y - q.y);

  if (val == 0)
    return 0;

  return (val > 0) ? 1 : 2;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
  int o1 = orientation(p1, q1, p2);
  int o2 = orientation(p1, q1, q2);
  int o3 = orientation(p2, q2, p1);
  int o4 = orientation(p2, q2, q1);

  if (o1 != o2 && o3 != o4)
    return true;

  if ((o1 == 0 && onSegment(p1, p2, q1)) ||
      (o2 == 0 && onSegment(p1, q2, q1)) ||
      (o3 == 0 && onSegment(p2, p1, q2)) ||
      (o4 == 0 && onSegment(p2, q1, q2)))
    return true;

  return false;
}