#include <iostream>
#include <vector>

int nwd(int a, int b)
{
  if (a < b)
    std::swap(a, b);
  if (b <= 0)
    return a;
  return nwd(b, a % b);
}

int main()
{
  int setsN;
  std::cin >> setsN;

  int escapees[setsN];
  for (int setI = 0; setI < setsN; setI++)
  {
    int n, d;
    std::cin >> n >> d;

    int gcd = nwd(n, d);
    escapees[setI] = n / gcd;
  }

  for (int i = 0; i < setsN; i++)
    std::cout << escapees[i] << std::endl;

  return 0;
}