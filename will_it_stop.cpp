#include <iostream>
#include <cmath>
#define LOG(x) std::cout << x << std::endl

int main()
{
  long long i;
  std::cin >> i;
  while (i % 2ll == 0ll)
  {
    i /= 2;
  }

  if (i == 1ll)
    LOG("TAK");
  else
    LOG("NIE");

  return 0;
}