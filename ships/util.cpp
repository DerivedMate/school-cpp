#include <iostream>
#include <random>

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
      // "                                                          ",

  };

  for (std::string &line : art)
  {
    std::cout << line << std::endl;
  }
}