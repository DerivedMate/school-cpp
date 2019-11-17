#include <iostream>
#include <random>

int rand(int a, int b)
{
  return rand() % (b - a) + a;
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(a, b);
  return distr(eng);
}

int main()
{
  int last = 0;
  for (int i = 0; i < 1000; i++)
  {
    int nr = rand(5, 50);
    if (true)
    {
      last = nr;
      std::cout << last << std::endl;
    }
  }

  return 0;
}