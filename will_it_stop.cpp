#include <iostream>
#include <map>
#define LOG(x) std::cout << x << std::endl

int f(int x)
{
  return 3 * x + 3;
}

int main()
{
  int i, j;
  std::cin >> i;

  while (i % 2 == 0 && i != 1)
  {
    i /= 2;
  }

  if (i == 1)
    LOG("TAK");
  else
    LOG("NIE");

  return 0;
}