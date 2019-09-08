#include <iostream>
#define LOG(x) std::cout << x << std::endl

int *aggrInput(int n)
{
  int i = 0, b;
  int *acc = new int[n];
  while (std::cin >> b && i < n)
  {
    acc[i++] = b;
    if (i == n)
      break;
  }
  return acc;
}

int main()
{
  int n, x;
  std::cin >> n >> x;
  int *entries = aggrInput(n);

  int a = 0;
  for (; a < n; a++)
  {
    if (entries[a] == x)
      break;
    else if (a == n - 1)
    {
      a = -2;
      break;
    }
  }

  int b = n - 1;
  for (; b > a; b--)
  {
    if (entries[b] == x)
      break;
    else if (b == 1)
    {
      b = -2;
      break;
    }
  }

  LOG(++a << " " << ++b);

  return 0;
}