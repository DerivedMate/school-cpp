#include <iostream>
#include <cmath>

int len(int n)
{
  int m = 0;
  while (n != 0)
  {
    n /= 10;
    m++;
  }
  return m;
}

int main()
{
  int a, i = 0, acc = 0;
  std::cin >> a;
  int n = len(a) - 1;

  while (a != 0)
  {
    acc += (a % 10) * (int)pow(10, n - (i++));
    a /= 10;
  }

  std::cout << acc << std::endl;

  return 0;
}