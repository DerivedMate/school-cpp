#include <iostream>
#define l(x) std::cout << x << std::endl

int f(int b, int n, int p)
{
  if (p == 0)
    return 1;
  else if (p <= 1)
    return n % 10;
  return f(b, (n % 10) * b % 10, p - 1);
}

int main()
{
  int p;
  const int b = 2;
  std::cin >> p;

  switch((p-1) % 4) {
    case 0: l(2); break;
    case 1: l(4); break;
    case 2: l(8); break;
    case 3: l(6); break;
    default:l(1); break;
  }
  return 0;
}