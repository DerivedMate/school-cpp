#include <iostream>
#include <random>
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

  };

  for (std::string &line : art)
  {
    std::cout << line << std::endl;
  }
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