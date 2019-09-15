#include <iostream>
#define LOG(x) std::cout << x << std::endl

int fact(int n)
{
  if (n <= 1)
    return 1;
  return n * fact(n - 1);
}

int main()
{
  int x;
  std::cin >> x;
  LOG(fact(x));
  return 0;
}